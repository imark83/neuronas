#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"
#include "rkSW.h"


#define DELAY(k)	g_delay[(int) NNEURON*CUTNUMBER*get_global_id(0) + (int) (k)]

#define PHI(i)		randomNumber[8*get_global_id(0) + (i)]

__kernel void neuron (
		// output
		__global real_t *g_delay,
		// input
		__global real_t *randomNumber) {

	int i, j;



	real_t P = 1.055264e+01;
	real_t sw[NVAR_SW]/* = {
		-4.003428e-02,
		9.879639e-01,
		2.066398e-02,
		-4.465347e-02,
		9.977267e-01,
		2.614316e-02,
		-9.251283e-03,
		2.949874e-02,
		3.055615e-01}*/;

	rkSW (sw, 10000, (real_t *) 0, 0);

	// ALL NETWORK
	real_t y[NVAR_SW];	// AUX SMALL WORLD
	real_t x[NVAR_N];

	// POINCARE EVENTS

	//real_t T[CUTNUMBER*NNEURON];

	__global real_t * __private T;

	T = g_delay + NNEURON*CUTNUMBER*get_global_id(0);


	// INITIALIZE REFERENCE BURSTERS OF EACH SMALL WORLD 
	for (i=0; i<NVAR_SW; i++) x[i] = y[i] = sw[i];
	rkSW (y, (1.0 - PHI(6))*P, (real_t *) 0, 0);
	for (i=0; i<NVAR_SW; i++) x[i+NVAR_SW] = y[i];
	
	for (i=0; i<NVAR_SW; i++) y[i] = sw[i];
	rkSW (y, (1.0 - PHI(7))*P, (real_t *) 0, 0);
	for (i=0; i<NVAR_SW; i++) x[i+2*NVAR_SW] = y[i];



//	for (i=0; i<8; i++) printf ("PHI = %f\n", PHI(i));
//	for (i=0; i<9; i++) printf ("\tx[%2i] = %e;\n", i, x[18+i]);



//	rkN (x, 0.01, (__global real_t*) 0, 0);

	// INTEGRATE CPG
	rkN (x, 100000.0, T, CUTNUMBER);

	for (i=0; i<10; i++) printf ("%f  ", T[i]);

//	for (i=0; i<NNEURON*CUTNUMBER; i++) DELAY(i) = T[i];

/*	for (i=0; i<3*CUTNUMBER; ++i) 
		printf ("%e, ", T[CUTNUMBER*NNEURON-3*CUTNUMBER+i]);
	printf ("\n");*/

return;


}
