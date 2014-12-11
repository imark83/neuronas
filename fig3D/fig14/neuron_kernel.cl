#include "parameters.h"

#define DELAY(k)	delay[M*N*(k) + M*get_global_id(1) + get_global_id(0)]

#include "openCL_headers.h"



__kernel void neuron (  __global const real_t *VSHIFT,
			__global       real_t *delay) {
	int i, j;

	// DESIRED DELAYS FOR FIRST POINT
	real_t phi21 = 0.334; //XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1);	// DESIRED PHI21
	real_t phi31 = 0.666; //YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);	// DESIRED PHI31


	real_t z[3] = {0.0, 0.0, 0.0};
	real_t y[3];
	real_t x[9];
	real_t P;
	real_t T[3*CUTNUMBER];	

	// FALL INTO DUTY CYCLE
	taylor1 (z, 500.0, 0, *VSHIFT);
	// COMPUTE PERIOD FOR SINGLE NEURON
	P = taylor1 (z, 1000.0, 1, *VSHIFT); 


	real_t _phi21, _phi31, err21, err31;
	_phi21 = phi21; _phi31 = phi31;

	// COMPUTE LAG FOR OTHER NEURONS

	do {
		for (i=0; i<3; i++) x[i] = y[i] = z[i];
		taylor1 (y, (1.0-_phi21)*P, 0, *VSHIFT);
		for (i=0; i<3; i++) x[i+3] = y[i];
	
		for (i=0; i<3; i++) y[i] = x[i];
		taylor1 (y, (1.0-_phi31)*P, 0, *VSHIFT);
		for (i=0; i<3; i++) x[i+6] = y[i];
	

		taylor (x, 100000.0, T, *VSHIFT, 4);

		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);

		/*if (get_global_id(0) + get_global_id(1) == 0) {
			printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
			printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
					x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
			printf ("T =   %f\n", P);
			printf ("d21 = %.15lf\n", (T[CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("d31 = %.15lf\n", (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("err21 = %.15le\n", err21);
			printf ("err31 = %.15le\n", err31);
			printf ("-------------------------------\n");
		}*/
		_phi21 += err21; _phi31 += err31;

	} while (fabs (err21) + fabs (err31) > 1.0e-10);	

	for (i=0; i<3; i++) x[i] = y[i] = z[i];
	taylor1 (y, (1.0-_phi21)*P, 0, *VSHIFT);
	for (i=0; i<3; i++) x[i+3] = y[i];
	
	for (i=0; i<3; i++) y[i] = x[i];
	taylor1 (y, (1.0-_phi31)*P, 0, *VSHIFT);
	for (i=0; i<3; i++) x[i+6] = y[i];


	// INTEGRATE CPG
	taylor (x, 100000.0, T, *VSHIFT, CUTNUMBER);

	for (i=0; i<3*CUTNUMBER; i++) DELAY(i) = T[i];
	


}

#include "taylor1.h"
#include "taylor.h"
#include "taylorAD.h"
#include "fun.h"




