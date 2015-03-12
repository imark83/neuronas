#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"


#define ENDPOINT	endPoint[M*get_global_id(1) + get_global_id(0)]

__kernel void neuron (__global char *endPoint) {
	/*int i;
	// DESIRED DELAYS FOR FIRST POINT
	real_t phi21 = 0.3333;	// DESIRED PHI21
	real_t phi31 = 0.6666;	// DESIRED PHI31



	real_t z[3] = {0.0, 0.0, 0.0};
	real_t y[3];
	real_t x[9];
	real_t P;
	real_t T[3*CUTNUMBER];	

	// FALL INTO DUTY CYCLE
	rkS (z, 500.0, 0);
	// COMPUTE PERIOD FOR SINGLE NEURON
	P = rkS (z, 1000.0, 1);

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

		rkN (x, 100000.0, T, 3, 0);
		
		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);
		_phi21 += err21; _phi31 += err31;
	} while (fabs (err21) + fabs (err31) > 1.0e-2 && count++ < 10);	

	for (i=0; i<3; i++) x[i] = y[i] = z[i];
	rkS (y, (1.0-_phi21)*P, 0);
	for (i=0; i<3; i++) x[i+3] = y[i];
	
	for (i=0; i<3; i++) y[i] = x[i];
	rkS (y, (1.0-_phi31)*P, 0);
	for (i=0; i<3; i++) x[i+6] = y[i];

	printf ("x0 = {");
	for (i=0; i<NVAR_N; i++) printf ("%e, ", x[i]);
	printf ("}\n"); 
	printf ("P = %e\n", rkS (x, 1000.0, 1));*/


	real_t x[NVAR_N] = {-4.012140e-02, 9.882284e-01, 2.065631e-02, -4.464825e-02, 9.977207e-01, 2.602615e-02, 1.232392e-02, 9.272169e-02, 2.966174e-01};
	real_t P = 1.045580e+01;
	real_t d21, d31;

	real_t pulse1Len = (get_global_id(0) * P) / (M-1.0);
	real_t pulse2Len = (get_global_id(1) * P) / (N-1.0);


	// integrate with two extra pulse
	rkN (x, pulse1Len, (real_t *) 0, 0, 0);
	rkN (x, 0.05*P, (real_t *) 0, 0, 1);
	rkN (x, pulse2Len, (real_t *) 0, 0, 0);
	rkN (x, 0.05*P, (real_t *) 0, 0, 2);

	// ITERATE UNTIL REACH STABLE POINT
	rkN (x, 1000, (real_t *) 0, 0, 0);

	// COMPUTE POINCARE SECTIONS
	real_t T[3*CUTNUMBER];
	rkN (x, 100000, T, CUTNUMBER, 0);


	P = T[1] - T[0];
	d21 = T[CUTNUMBER]-T[0];
		if (d21 < 0.0) d21 = T[CUTNUMBER+1]-T[0];
	d31 = T[2*CUTNUMBER]-T[0];
		if (d31 < 0.0) d31 = T[CUTNUMBER+1]-T[0];

	printf ("P = %e\n", P);
	printf ("d = (%e, %e)\n", d21, d31);

	printf ("Final state = (%f %f) ---- > ", d21/P, d31/P);
	if (fabs (d21/P - 0.541002) + fabs (d31/P) < 0.2 || fabs (d21/P - 0.541002) + fabs (d31/P -1.0) < 0.2) {
		printf ("0\n");
		ENDPOINT = 0.0;
	}
	else if (fabs (d21/P) + fabs (d31/P - 0.541002) < 0.2 || fabs (d21/P - 1.0) + fabs (d31/P - 0.541002) < 0.2) {
		printf ("1\n");
		ENDPOINT = 1.0;
	}
	else if (fabs (d21/P - 0.458981) + fabs (d31/P - 0.458981) < 0.2) {
		printf ("2\n");
		ENDPOINT = 2.0;
	}
	else if (fabs (d21/P - 0.33) + fabs (d31/P - 0.66) < 0.2) {
		printf ("3\n");
		ENDPOINT = 3.0;
	}
	else if (fabs (d21/P - 0.66) + fabs (d31/P - 0.33) < 0.2) {
		printf ("4\n");
		ENDPOINT = 4.0;
	}
	else  {
		printf ("????\n");
		ENDPOINT = -2.0;
	}


	return;




}
