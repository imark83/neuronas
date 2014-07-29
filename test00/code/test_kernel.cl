// PARAMETERS
#include "parameters.h"
 

// HEADERS AND MACROS FOR VARIABLES
#include "openCL_var_names.h"

// GLOBAL VARIABLES
#define FLI	fli[N*get_global_id(1) + get_global_id(0)]

__kernel void test (__global real_t *fli) {

	short k;
	real_t z[3], y[3], x[18];

	x[0] = -3.984730341527971e-02;
	x[1] = 5.750624937966343e-01;
	x[2] = 3.173568608828366e-01;
	x[3] = -3.984730341527971e-02;
	x[4] = 5.750624937966343e-01;
	x[5] = 3.173568608828366e-01;
	x[6] = -3.984730341527971e-02;
	x[7] = 5.750624937966343e-01;
	x[8] = 3.173568608828366e-01;

	for (k=9; k<18; k++) x[k] = 1.0;

	real_t P;
	P = taylor (x, 5000.0, 1);

	printf ("P = %.15le\n", P);


	/*real_t phi21 =  OX + (0.5/M + get_global_id(0)/((real_t) M)) * RADIUS;
	real_t phi31 =  OY + (0.5/N + get_global_id(1)/((real_t) N)) * RADIUS;

	for (k=0; k<3; k++) x[k] = y[k] = z[k];
	rk2 (y, (1.0-phi21)*P, 0);
	for (k=0; k<3; k++) x[k+3] = y[k];
	
	for (k=0; k<3; k++) y[k] = z[k];
	rk2 (y, (1.0-phi31)*P, 0);
	for (k=0; k<3; k++) x[k+6] = y[k];




	taylor (x);


	real_t r = sqrt (x[0]*x[0] + x[1]*x[1]);
	real_t v = sqrt (x[2]*x[2] + x[3]*x[3]);

	FLI = log ((x[4]*x[4] + x[5]*x[5])/r + (x[6]*x[6] + x[7]*x[7])/v);*/


}

#include "fun.h"

#include "taylor.h"
#include "taylorAD.h"
