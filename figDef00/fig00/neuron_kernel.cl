// PARAMETERS OF THE PROBLEM
#include "parameters.h"

// MACROS FOR VARIABLE NAMES
#include "openCL_var_names.h"

 


__kernel void neuron (	__global real_t* delay,
			__global real_t* VSHIFT) {

	int k;
	int i;
	int j;
	real_t T[3*CUTNUMBER];
	real_t z[NVAR2], y[NVAR2], x[NVAR];


	// ITERATE SINGLE UNTILL FALL IN THE DUTY-CYCLE 
	for (k=0; k<NVAR2; k++) z[k] = 0.0;
	//printf ("NVAR2 = %i\n", NVAR2);
	taylor2 (z, 500, -1, *VSHIFT);

	
	// COMPUTE PERIOD FROM POINCARÉ SECTIONS
	real_t P = taylor2 (z, 500, 0, *VSHIFT);

			
	real_t phi21 =  XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1);	// DESIRED PHI21
	real_t phi31 =  YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);	// DESIRED PHI31

	real_t _phi21, _phi31, err21, err31;
	_phi21 = phi21; _phi31 = phi31;

	// COMPUTE LAG FOR OTHER NEURONS

	for (j=0; j<15; j++) {
		for (k=0; k<3; k++) x[k] = y[k] = z[k];
		taylor2 (y, (1.0-_phi21)*P, -1, *VSHIFT);
		for (k=0; k<3; k++) x[k+3] = y[k];
	
		for (k=0; k<3; k++) y[k] = x[k];
		taylor2 (y, (1.0-_phi31)*P, -1, *VSHIFT);
		for (k=0; k<3; k++) x[k+6] = y[k];
	

		taylor (x, 100000.0, T, *VSHIFT, 4);

		err21 = phi21 - (T[CUTNUMBER] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]);

		if (get_global_id(0) + get_global_id(1) == 0) {
			printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
			printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
					x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
			printf ("T =   %f\n", P);
			printf ("d21 = %.15lf\n", (T[CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("d31 = %.15lf\n", (T[2*CUTNUMBER] - T[0]) / (T[1] - T[0]));
			printf ("err21 = %.15le\n", err21);
			printf ("err31 = %.15le\n", err31);
			printf ("-------------------------------\n");
		}
		_phi21 += err21; _phi31 += err31;
	}	

	for (k=0; k<3; k++) x[k] = y[k] = z[k];
	taylor2 (y, (1.0-_phi21)*P, -1, *VSHIFT);
	for (k=0; k<3; k++) x[k+3] = y[k];
	
	for (k=0; k<3; k++) y[k] = x[k];
	taylor2 (y, (1.0-_phi31)*P, -1, *VSHIFT);
	for (k=0; k<3; k++) x[k+6] = y[k];

	taylor (x, 10000000, T, *VSHIFT, CUTNUMBER);	

	for (k=0; k<3*CUTNUMBER; k++) DELAY(k) = T[k];


}




#include "fun.h"
#include "taylor.h"
#include "taylorAD.h"


