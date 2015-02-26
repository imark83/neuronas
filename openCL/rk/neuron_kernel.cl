#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rk.h"




__kernel void neuron () {
	real_t x[NVAR_S] = {0.0, 0.0, 0.0};

	rkS (x, 50, 0); 
	real_t P = rkS (x, 50, 1);

	printf ("Period = %e\n", P);


}
