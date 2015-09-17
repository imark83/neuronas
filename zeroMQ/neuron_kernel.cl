#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"


#define ENDPOINT	endPoint[get_global_id(0)]

__kernel void neuron (__global int *endPoint) {
	if (ENDPOINT < 0) {return;}
	//printf ("data = %hhu\n", endPoint[get_global_id (0)]);
	int indexI = ENDPOINT / N;
	int indexJ = ENDPOINT % N;


	real_t x[NVAR_N] = {-4.012140e-02, 9.882284e-01, 2.065631e-02, -4.464825e-02, 9.977207e-01, 2.602615e-02, 1.232392e-02, 9.272169e-02, 2.966174e-01};
	real_t P = 1.045580e+01;
	real_t d21, d31;

	real_t pulse1Len = (indexI * P) / (M-1.0);
	real_t pulse2Len = (indexJ * P) / (N-1.0);

	// integrate with two extra pulse
	rkN (x, pulse1Len, (real_t *) 0, 0, 0);
	rkN (x, 0.09*P, (real_t *) 0, 0, 1);
	rkN (x, pulse2Len, (real_t *) 0, 0, 0);
	rkN (x, 0.09*P, (real_t *) 0, 0, 2);

	// ITERATE UNTIL REACH STABLE POINT
	rkN (x, 2000, (real_t *) 0, 0, 0);


	// COMPUTE POINCARE SECTIONS
	real_t T[3*CUTNUMBER];
	rkN (x, 100000, T, CUTNUMBER, 0);


	P = T[1] - T[0];
	d21 = T[CUTNUMBER]-T[0];
		if (d21 < 0.0) d21 = T[CUTNUMBER+1]-T[0];
	d31 = T[2*CUTNUMBER]-T[0];
		if (d31 < 0.0) d31 = T[2*CUTNUMBER+1]-T[0];
	real_t f21 = d21/P;
	real_t f31 = d31/P;
	if (f21>=1) f21 -= 1.0;
	if (f31>=1) f31 -= 1.0;


	//printf ("Final state = (%.4f %.4f) ---- > ", f21, f31);
	if (fabs (f21 - 0.541002) + fabs (f31) < 0.2 || fabs (d21 - 0.541002) + fabs (f31 -1.0) < 0.2) {
	//	printf ("0\n");
		ENDPOINT = 0.0;
	}
	else if (fabs (f21) + fabs (f31 - 0.541002) < 0.2 || fabs (f21 - 1.0) + fabs (f31 - 0.541002) < 0.2) {
	//	printf ("1\n");
		ENDPOINT = 1.0;
	}
	else if (fabs (f21 - 0.458981) + fabs (f31 - 0.458981) < 0.2) {
	//	printf ("2\n");
		ENDPOINT = 2.0;
	}
	else if (fabs (f21 - 0.33) + fabs (f31 - 0.66) < 0.2) {
	//	printf ("3\n");
		ENDPOINT = 3.0;
	}
	else if (fabs (f21 - 0.66) + fabs (f31 - 0.33) < 0.2) {
	//	printf ("4\n");
		ENDPOINT = 4.0;
	}
	else  {
	//	printf ("????\n");
		ENDPOINT = -2.0;
	}


	return;

}


