#include "taylor.h"


#include "parameters.h"

int fac = 1;
int event = -1;			// 0 + 3*j
double eventValue = EVENTVALUE;
double T[3*CUTNUMBER];


int main () {

	int i, j, k;

	int nvar = 3;
	int nNeuron = 3;
	double z[nvar];
	double t0 = 0.;
	double tf = 200.0;
	int nt = 1;
	double tol = 1e-12;

	real_t vshift = -0.01886;

	/* ITERATE UNTILL FALL IN THE DUTY-CYCLE */
	for (k=0; k<nvar; k++) z[k] = 0.0;
	taylorS (nvar, z, t0, tf, tol, 0, vshift);


	/*COMPUTE PERIOD FROM POINCARÉ SECTIONS*/
	event = 0;
	double P = taylorS (nvar, z, t0, tf, tol, 1, vshift);

	//printf ("P = %.15le\n", P); 

	
		double phi21 = 0.1;
		double phi31 = 0.21;
		double x[nvar*nNeuron], y[nvar];

		double _phi21, _phi31, err21, err31;
		_phi21 = phi21; _phi31 = phi31;

		//for (i=0; i<8; i++) {
		do {
			for (k=0; k<nvar; k++) x[k] = y[k] = z[k];
			taylorS (nvar, y, t0, (1.0-_phi21)*P, tol, 0, vshift);
			for (k=0; k<nvar; k++) x[k+3] = y[k];

			for (k=0; k<nvar; k++) y[k] = x[k];
			taylorS (nvar, y, t0, (1.0-_phi31)*P, tol, 0, vshift);
			for (k=0; k<nvar; k++) x[k+6] = y[k];

			taylorN (nvar*nNeuron, x, 0, 1000000, tol, 1, vshift, 4);
			
	
			err21 = phi21 - (T[4] - T[0]) / (T[1] - T[0]);
			err31 = phi31 - (T[8] - T[0]) / (T[1] - T[0]);

			/*printf ("T = %f %f %f %f %f %f\n", T[0], T[1], T[4], T[4+1], T[2*4], T[2*4+1])	;
			printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
			printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
					x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
			printf ("P =   %f\n", P);
			printf ("d21 = %.15lf\n", (T[4] - T[0]) / (T[1] - T[0]));
			printf ("d31 = %.15lf\n", (T[2*4] - T[0]) / (T[1] - T[0]));
			printf ("err21 = %.15le\n", err21);
			printf ("err31 = %.15le\n", err31);
			printf ("-------------------------------\n");*/
			_phi21 += err21; _phi31 += err31;
		//}
		} while (fabs (err21) + fabs (err31) > 1.0e-6);	

		for (k=0; k<nvar; k++) x[k] = y[k] = z[k];
		taylorS (nvar, y, t0, (1.0-_phi21)*P, tol, 0, vshift);
		for (k=0; k<nvar; k++) x[k+3] = y[k];

		for (k=0; k<nvar; k++) y[k] = x[k];
		taylorS (nvar, y, t0, (1.0-_phi31)*P, tol, 0, vshift);
		for (k=0; k<nvar; k++) x[k+6] = y[k];



		taylorN (nvar*nNeuron, x, 0, 1000000, tol, 1, vshift, CUTNUMBER);

		for (k=0; k<3*CUTNUMBER; k++) 
			printf ("%.15le  ", T[k]);
		printf ("\n");
		

/*	FILE *fout = fopen ("T.txt", "w");


	for (i=0; i<M; i++) for (j=0; j<N; j++) {
		double phi21 = XMIN + ((XMAX-XMIN)*get_global_id(0))/(M-1);	// DESIRED PHI21
		double phi31 = YMIN + ((YMAX-YMIN)*get_global_id(1))/(N-1);	// DESIRED PHI31



		tf = 5000.0;
		event = 0;
		nt = 1;
		taylor (nvar, x, t0, tf/nt, nt, tol, NULL);

	
		for (k=0; k<cutNumber; k++) 
			fprintf (fout, "%.15le  ", T[k]);
		fprintf (fout, "\n");


	}

	fclose (fout);*/
	return 0;

}

