#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"


#define DELAY(k)	delay[M*N*(k) + M*get_global_id(1) + get_global_id(0)]


__kernel void neuron (__global       real_t *delay) {
	int i;
	// DESIRED DELAYS FOR FIRST POINT
	//real_t phi21 = XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1.0);	// DESIRED PHI21
	//real_t phi31 = YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1.0);	// DESIRED PHI31

	// BLUE
	/*real_t phi21 = 0.114054782218231;
	real_t phi31 = 0.140398143990421;*/

	// RED
	/*real_t phi21 = 0.110911540188595;
	real_t phi31 = 0.880407124681934;*/

	// GREEN
	/*real_t phi21 = 0.107917976350846;
	real_t phi31 = 0.251758718754677;*/

	// BLACK
	real_t phi21 = 0.130220026942075;
	real_t phi31 = 0.201017811704835;


	real_t z[3] = {0.0, 0.0, 0.0};
	real_t y[3];
	real_t x[9];
	real_t P;
	real_t T[3*CUTNUMBER];	

	// FALL INTO DUTY CYCLE
	rkS (z, 500.0, 0);
	// COMPUTE PERIOD FOR SINGLE NEURON
	P = rkS (z, 1000.0, 1);
	printf ("%zu / %i\n", M*get_global_id(1)+get_global_id(0), M*N);

	real_t _phi21, _phi31, err21, err31;
	_phi21 = phi21; _phi31 = phi31;

	// COMPUTE LAG FOR OTHER NEURONS
	int count = 0;
	do {
		for (i=0; i<3; i++) x[i] = y[i] = z[i];
		rkS (y, (1.0-_phi21)*P, 0);
		for (i=0; i<3; i++) x[i+3] = y[i];
	
		for (i=0; i<3; i++) y[i] = x[i];
		rkS (y, (1.0-_phi31)*P, 0);
		for (i=0; i<3; i++) x[i+6] = y[i];
	

		rkN (x, 100000.0, T, 3);
		
		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);

		if (get_global_id(0) + get_global_id(1) == 0) {
			printf ("T = %f %f %f %f %f %f\n", T[0], T[1], T[CUTNUMBER], T[CUTNUMBER+1], T[2*CUTNUMBER], T[2*CUTNUMBER+1]);
			printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
			printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
					x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
			printf ("T =   %f\n", P);
			printf ("d21 = %.15lf\n", (T[CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("d31 = %.15lf\n", (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("err21 = %.15le\n", err21);
			printf ("err31 = %.15le\n", err31);
			printf ("-------------------------------\n");
		}
		_phi21 += err21; _phi31 += err31;
	} while (fabs (err21) + fabs (err31) > 1.0e-2 && count++ < 10);	

	for (i=0; i<3; i++) x[i] = y[i] = z[i];
	rkS (y, (1.0-_phi21)*P, 0);
	for (i=0; i<3; i++) x[i+3] = y[i];
	
	for (i=0; i<3; i++) y[i] = x[i];
	rkS (y, (1.0-_phi31)*P, 0);
	for (i=0; i<3; i++) x[i+6] = y[i];


	printf ("start!\n");
	// INTEGRATE CPG
	rkN (x, 100000.0, T, CUTNUMBER);
	//rkN (x, 1000.0, (real_t*) 0, 0);

	for (i=0; i<3*CUTNUMBER; i++) DELAY(i) = T[i];



}
