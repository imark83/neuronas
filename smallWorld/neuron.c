#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <unistd.h>



#include "parameters.h"
#include "fun.h"
#include "rk_coef.h"
#include "rkS.h"
#include "rkN.h"



real_t getRand () {
	return ((real_t) rand()) / ((real_t) RAND_MAX);
}

int main  (int argc, char **argv) {

	srand (getpid());

	int i;
	// DESIRED DELAYS FOR FIRST POINT



	real_t z[NVAR_S] = {0.0, 0.0, 0.0};
	real_t x[NVAR_N];

	// FALL INTO DUTY CYCLE
	rkS (z, 500.0, 0);


	int j;
	for (j=0; j<20; j++) {
		rkS (z, (real_t) j + getRand(), 0);
		for (i=0; i<3; i++) x[3*j+i] = z[i];
	}


	// INTEGRATE CPG
	rkN (x, 1500.0, (real_t *) 0, 0);

	system ("beep");

}
