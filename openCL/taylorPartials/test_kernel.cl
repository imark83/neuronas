// PARAMETERS
#include "parameters.h"
 

// HEADERS AND MACROS FOR VARIABLES
#include "openCL_var_names.h"

// GLOBAL VARIABLES
#define FLI	fli[N*get_global_id(1) + get_global_id(0)]

__kernel void test (__global real_t *fli) {

	short k;
	real_t x[NCOL];

	x[0] = 0.0;
	x[1] = yMIN + ((yMAX-yMIN)*get_global_id(0))/(M-1);
	x[3] = YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);
	x[2] = 2.0*H - x[3]*x[3] - x[1]*x[1] + 2.0/3.0*x[1]*x[1]*x[1];

	if (x[2] < 0.0) {
		FLI = -5.0;
		return;
	}
	
	/*x[0] = 0.0;
	x[1] = 0.548463957942453;
	x[2] = sqrt (2.0*(0.12) - x[1]*x[1] + 2.0/3.0*x[1]*x[1]*x[1]);
	x[3] = 0.0;*/

	x[2] = sqrt (x[2]);
	x[4] = x[5] = x[6] = x[7] = 1.0;

	/*for (k=4; k<20; k++) x[k] = 0.0;
	x[4] = 1.0;
	x[9] = 1.0;
	x[14] = 1.0;
	x[19] = 1.0;*/

	taylor (x);

	/*real_t r, v;
	r = v;
	r = sqrt (x[0]*x[0] + x[1]*x[1]);
	v = sqrt (x[2]*x[2] + x[3]*x[3]);
	
	real_t vx, vy, vX, vY;
	vx = log ((x[4]*x[4] + x[5]*x[5])/r + (x[6]*x[6] + x[7]*x[7])/v)/2.0;
	vy = log ((x[8]*x[8] + x[9]*x[9])/r + (x[10]*x[10] + x[11]*x[11])/v)/2.0;
	vX = log ((x[12]*x[12] + x[13]*x[13])/r + (x[14]*x[14] + x[15]*x[15])/v)/2.0;
	vY = log ((x[16]*x[16] + x[17]*x[17])/r + (x[18]*x[18] + x[19]*x[19])/v)/2.0;

	FLI = vx;
	FLI = MAX (FLI,vy);
	FLI = MAX (FLI,vX);
	FLI = MAX (FLI,vY);*/

	real_t r = sqrt (x[0]*x[0] + x[1]*x[1]);
	real_t v = sqrt (x[2]*x[2] + x[3]*x[3]);

	FLI = log ((x[4]*x[4] + x[5]*x[5])/r + (x[6]*x[6] + x[7]*x[7])/v);


}

#include "fun.h"

#include "taylor.h"
#include "taylorAD.h"
