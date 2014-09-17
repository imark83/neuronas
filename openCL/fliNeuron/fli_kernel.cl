// GLOBAL VARIABLES
#define FLI	fli[N*get_global_id(1) + get_global_id(0)]          
   
// PARAMETERS OF THE PROBLEM
#include "parameters.h"

// MACROS FOR VARIABLE NAMES
#include "openCL_var_names.h"
#include "openCL_var_names_partials.h"


__kernel void fli (__global real_t *fli,
		   __global int *counter) {
	if (get_global_id (0) + get_global_id(1) == 0) *counter = 0;

	// FASE 1. CORRECT INITIAL CONDITIONS. SINGLE NEURON AND NETWORK INTEGRATION. SIMPLE TAYLOR METHOD

	int k;
	int i;
	int j;
	real_t T[3*CUTNUMBER];
	real_t z[NVAR2], y[NVAR2], x[NCOL];


	// ITERATE SINGLE UNTILL FALL IN THE DUTY-CYCLE 
	for (k=0; k<NVAR2; k++) z[k] = 0.0;

	taylor2 (z, 100, -1);

	// COMPUTE PERIOD FROM POINCARÉ SECTIONS
	real_t P = taylor2 (z, 500, 0);
			
	real_t phi21 =  XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1);	// DESIRED PHI21
	real_t phi31 =  YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);	// DESIRED PHI31

	real_t _phi21, _phi31, err21, err31;
	_phi21 = phi21; _phi31 = phi31;

	// COMPUTE LAG FOR OTHER NEURONS

	for (j=0; j<8; j++) {
		for (k=0; k<3; k++) x[k] = y[k] = z[k];
		taylor2 (y, (1.0-_phi21)*P, -1);
		for (k=0; k<3; k++) x[k+3] = y[k];
	
		for (k=0; k<3; k++) y[k] = x[k];
		taylor2 (y, (1.0-_phi31)*P, -1);
		for (k=0; k<3; k++) x[k+6] = y[k];
	

		taylor (x, 100000.0, T, 3);

		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);

		/*if (get_global_id(0) + get_global_id(1) == 2) {
			printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
			printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
					x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
			printf ("T =   %f\n", P);
			printf ("d21 = %.15lf\n", (T[CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("d31 = %.15lf\n", (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("err21 = %.15le\n", err21);
			printf ("err31 = %.15le\n", err31);
			printf ("-------------------------------\n");
		}*/
		_phi21 += err21; _phi31 += err31;
	}	

	for (k=0; k<3; k++) x[k] = y[k] = z[k];
	taylor2 (y, (1.0-_phi21)*P, -1);
	for (k=0; k<3; k++) x[k+3] = y[k];
	
	for (k=0; k<3; k++) y[k] = x[k];
	taylor2 (y, (1.0-_phi31)*P, -1);
	for (k=0; k<3; k++) x[k+6] = y[k];


	// INITIALIZE PARTIAL DERIVATIVES
	for (k=9; k<18; k++) x[k] = 1.0;



	taylor_partials(x);
	

	/*char i;
	real_t x[NVAR];

	x[0] = 0.0;
	x[1] = yMIN + ((yMAX-yMIN)*get_global_id(0))/(M-1);
	x[3] = YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);
	x[2] = 2.0*H - x[3]*x[3] - x[1]*x[1] + 2.0/3.0*x[1]*x[1]*x[1];

	if (x[2] < 0.0) {
		FLI = -5.0;
		return;
	}

	x[2] = sqrt (x[2]);
	for (i=4; i<NVAR1; i++) x[i] = 0.0;
	x[4] = x[9] = x[14] = x[19] = 1.0;*/




	real_t r = (x[0]*x[0] + x[1]*x[1] + x[2]*x[2] + x[3]*x[3] + x[4]*x[4] + x[5]*x[5] + x[6]*x[6] + x[7]*x[7] + x[8]*x[8]);

	FLI = 0.5 * log ((x[9]*x[9] + x[10]*x[10] + x[11]*x[11] + x[12]*x[12] + x[13]*x[13] + x[14]*x[14] + x[15]*x[15] + x[16]*x[16] + x[17]*x[17]) / r);


	printf ("%i / %i\n", (*counter) = (*counter) + 1, 512*512);
}


#include "fun.h"
#include "taylor.h"
#include "taylorAD.h"


#include "fun_partials.h"
#include "taylor_partials.h"
#include "taylorAD_partials.h"



