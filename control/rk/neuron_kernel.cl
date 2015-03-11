#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"


//#define DELAY(k)	delay[M*N*(k) + M*get_global_id(1) + get_global_id(0)]


__kernel void neuron (__global       real_t *delay) {
	int i;
	// DESIRED DELAYS FOR FIRST POINT
	//real_t pulse1 = 0.0; //XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1);	// length of first pulse [0,1]
	//real_t pulse2 = 0.0; //YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);	// length of second pulse [0,1]



	real_t T[3*CUTNUMBER];	
	real_t z[3] = {0.0, 0.0, 0.0};
	real_t y[3];
	real_t x[9];
	real_t P;

	// FALL INTO DUTY CYCLE
	rkS (z, 500.0, 0);
	// COMPUTE PERIOD FOR SINGLE NEURON
	P = rkS (z, 1000.0, 1);
	printf ("%zu / %i\n", M*get_global_id(1)+get_global_id(0), M*N);

	real_t phi21 = 0.33333;
	real_t phi31 = 0.66666;
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
	

		rkN (x, 100000.0, T, CUTNUMBER, 0);
		
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
	} while (fabs (err21) + fabs (err31) > 1.0e-4 && count++ < 5000);	

	for (i=0; i<3; i++) x[i] = y[i] = z[i];
	rkS (y, (1.0-_phi21)*P, 0);
	for (i=0; i<3; i++) x[i+3] = y[i];
	
	for (i=0; i<3; i++) y[i] = x[i];
	rkS (y, (1.0-_phi31)*P, 0);
	for (i=0; i<3; i++) x[i+6] = y[i];




	// INTEGRATE CPG
	/*rkN (x, pulse1*P, (real_t *) 0, 0, 0);
	rkN (x, 0.05*P, (real_t *) 0, 0, 1);
	rkN (x, pulse2*P, (real_t *) 0, 0, 0);
	rkN (x, 0.05*P, (real_t *) 0, 0, 2);*/


	
	rkN (x, 500, (real_t *) 0, 0, 0);
	rkN (x, 5000, T, CUTNUMBER, 0);

	printf (" %e %e %e\n %e %e %e\n %e %e %e \n", 
			T[0], T[1], T[2], T[3], T[4], T[5], T[6], T[7], T[8]);

	real_t d21, d31;
	P = T[1] - T[0];
	printf ("new P = %e\n", P);
	d21 = T[3]-T[0];
		if (d21 < 0.0) d21 = T[4]-T[0];
	d31 = T[6]-T[0];
		if (d31 < 0.0) d31 = T[7]-T[0];
	printf ("d = (%e,%e)\n", d21, d31);

	printf ("Final state = (%f %f) ---- > ", d21/P, d31/P);
	if (fabs (d21/P - 0.63) + fabs (d31/P) < 0.2 || fabs (d21/P - 0.63) + fabs (d31/P -1.0) < 0.2) {
		printf ("0\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = 0.0;
	}
	else if (fabs (d21/P) + fabs (d31/P - 0.5) < 0.2 || fabs (d21/P - 1.0) + fabs (d31/P - 0.5) < 0.2) {
		printf ("1\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = 1.0;
	}
	else if (fabs (d21/P - 0.4) + fabs (d31/P - 0.4) < 0.2) {
		printf ("2\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = 2.0;
	}
	else if (fabs (d21/P - 0.33) + fabs (d31/P - 0.66) < 0.2) {
		printf ("3\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = 3.0;
	}
	else if (fabs (d21/P - 0.66) + fabs (d31/P - 0.33) < 0.2) {
		printf ("4\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = 4.0;
	}
	else  {
		printf ("????\n");
		//endPoint[M*get_global_id(1) + get_global_id(0)] = -2.0;
	}



}
