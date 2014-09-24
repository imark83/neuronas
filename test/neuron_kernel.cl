
// PARAMETERS OF THE PROBLEM
#include "parameters.h"

// MACROS FOR VARIABLE NAMES
#include "openCL_var_names.h"


__kernel void neuron() {
	int k;
	int i;
	int j;
	real_t T[3*CUTNUMBER];
	real_t z[NVAR2], y[NVAR2], x[NVAR];


	// ITERATE SINGLE UNTILL FALL IN THE DUTY-CYCLE 
	for (k=0; k<NVAR2; k++) z[k] = 0.0;
	//printf ("NVAR2 = %i\n", NVAR2);
	//taylor2 (z, 100, -1, *VSHIFT);
	taylor2 (z, 100, -1, -0.01871);
	return;
	
}



#include "fun.h"
#include "taylor.h"
#include "taylorAD.h"
