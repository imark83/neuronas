#include <stdio.h>
#include <omp.h>


#include "taylor.h"
#include "parameters.h"

int numThreads = 4;

int main () {

	int i;

	FILE *fout[numThreads];
	for (i=0; i<numThreads; i++) {
		char fname[40];
		sprintf (fname, "T%02i.txt", i);
		fout[i] = fopen (fname, "w");
	}
		


	int nvar = 3;
	int nNeuron = 3;
	double z[nvar];
	double t0 = 0.;
	double tf = 200.0;
	int nt = 1;
	double tol = 1e-12;

	double vshift = -0.01886;
	double P;

	/* ITERATE UNTILL FALL IN THE DUTY-CYCLE */
	for (i=0; i<nvar; i++) z[i] = 0.0;
	taylorS (nvar, z, t0, tf, tol, 0, vshift);


	/*COMPUTE PERIOD FROM POINCARÉ SECTIONS*/
	P = taylorS (nvar, z, t0, tf, tol, 1, vshift);


	printf ("global P = %.15le\n", P); 

#pragma omp parallel for num_threads(numThreads)
for (i=0; i<M; i++) {
	int j, k;
	for (j=0; j<N; j++){
		double phi21 = XMIN + ((XMAX-XMIN)*i)/(M-1);
		double phi31 = YMIN + ((YMAX-YMIN)*j)/(N-1);
		double x[nvar*nNeuron], y[nvar];
		double T[3*CUTNUMBER];
		int event = -1;	

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

			taylorN (nvar*nNeuron, x, 0, 1000000, tol, 1, vshift, 4, T);
			
	
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



		taylorN (nvar*nNeuron, x, 0, 1000000, tol, 1, vshift, CUTNUMBER, T);

		for (k=0; k<3*CUTNUMBER; k++) 
			fprintf (fout[omp_get_thread_num()], "%.15le  ", T[k]);
		fprintf (fout[omp_get_thread_num()], "\n");
	}

}	


	for (i=0; i<numThreads; i++) {
		fclose (fout[i]);
	}


	char command[50] = "cat T00.txt > T.txt";
	system (command);
	for (i=0; i<numThreads; i++) {
		sprintf (command, "cat T%02i.txt >> T.txt", i);
		printf ("%s\n", command);
		system (command);
	}
	sprintf (command, "rm T??.txt");
	system (command);
	
	return 0;

}

