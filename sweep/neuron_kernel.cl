#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"


#define DELAY(k)	delay[M*N*(k) + M*get_global_id(1) + get_global_id(0)]


__kernel void neuron (__global       real_t *delay) {
	int i;
	// DESIRED DELAYS FOR FIRST POINT
	real_t phi21 = XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1.0);	// DESIRED PHI21
	real_t phi31 = YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1.0);	// DESIRED PHI31



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
	/*do {
		for (i=0; i<3; i++) x[i] = y[i] = z[i];
		rkS (y, (1.0-_phi21)*P, 0);
		for (i=0; i<3; i++) x[i+3] = y[i];
	
		for (i=0; i<3; i++) y[i] = x[i];
		rkS (y, (1.0-_phi31)*P, 0);
		for (i=0; i<3; i++) x[i+6] = y[i];
	

		rkN (x, 100000.0, T, 3);
		
		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);


		_phi21 += err21; _phi31 += err31;
	} while (fabs (err21) + fabs (err31) > 1.0e-2 && count++ < 2);	*/

	for (i=0; i<3; i++) x[i] = y[i] = z[i];
	rkS (y, (1.0-_phi21)*P, 0);
	for (i=0; i<3; i++) x[i+3] = y[i];
	
	for (i=0; i<3; i++) y[i] = x[i];
	rkS (y, (1.0-_phi31)*P, 0);
	for (i=0; i<3; i++) x[i+6] = y[i];


	// INTEGRATE CPG
	rkN (x, 100000.0, T, CUTNUMBER);
	//rkN (x, 1000.0, (real_t*) 0, 0);

	for (i=0; i<3*CUTNUMBER; i++) DELAY(i) = T[i];



}
