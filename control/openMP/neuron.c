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

	double vshift = -0.022;
	double P;

	/* ITERATE UNTILL FALL IN THE DUTY-CYCLE */
	for (i=0; i<nvar; i++) z[i] = 0.0;
	taylorS (nvar, z, t0, tf, tol, 0, vshift);


	/*COMPUTE PERIOD FROM POINCARÉ SECTIONS*/
	P = taylorS (nvar, z, t0, tf, tol, 1, vshift);


	printf ("global P = %.15le\n", P); 
	double phi21 = 0.3333;
	double phi31 = 0.6666;
	double x[nvar*nNeuron], y[nvar];
	double T[3*CUTNUMBER];

	// START AT 0.33,0.66 EQUILIBRIUM POINT

	int j,k;
	double _phi21, _phi31, err21, err31;
	_phi21 = phi21; _phi31 = phi31;
	do {
		for (k=0; k<nvar; k++) x[k] = y[k] = z[k];
		taylorS (nvar, y, t0, (1.0-_phi21)*P, tol, 0, vshift);
		for (k=0; k<nvar; k++) x[k+3] = y[k];

		for (k=0; k<nvar; k++) y[k] = x[k];
		taylorS (nvar, y, t0, (1.0-_phi31)*P, tol, 0, vshift);
		for (k=0; k<nvar; k++) x[k+6] = y[k];

		taylorN (nvar*nNeuron, x, 0, 1000000, tol, 1, vshift, 4, T, 0.0);
			
	
		err21 = phi21 - (T[4] - T[0]) / (T[1] - T[0]);
		err31 = phi31 - (T[8] - T[0]) / (T[1] - T[0]);

		printf ("T = %f %f %f %f %f %f\n", T[0], T[1], T[4], T[4+1], T[2*4], T[2*4+1])	;
		printf ("desired phi21 = %.15lf\ndesired phi31 = %.15lf\n", phi21, phi31);
		printf ("x = [ %f, %f, %f, %f, %f, %f, %f, %f, %f]\n", 
				x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]);
		printf ("P =   %f\n", P);
		printf ("d21 = %.15lf\n", (T[4] - T[0]) / (T[1] - T[0]));
		printf ("d31 = %.15lf\n", (T[2*4] - T[0]) / (T[1] - T[0]));
		printf ("err21 = %.15le\n", err21);
		printf ("err31 = %.15le\n", err31);
		printf ("-------------------------------\n");
		_phi21 += err21; _phi31 += err31;
	} while (fabs (err21) + fabs (err31) > 1.0e-3);	

	for (k=0; k<nvar; k++) x[k] = y[k] = z[k];
	taylorS (nvar, y, t0, (1.0-_phi21)*P, tol, 0, vshift);
	for (k=0; k<nvar; k++) x[k+3] = y[k];

	for (k=0; k<nvar; k++) y[k] = x[k];
	taylorS (nvar, y, t0, (1.0-_phi31)*P, tol, 0, vshift);
	for (k=0; k<nvar; k++) x[k+6] = y[k];

	

int count = 0;
printf ("local P = %f\n", P); 

#pragma omp parallel for num_threads(numThreads) schedule(dynamic) private (j, k)
for (i=0; i<M; i++) {
	for (j=0; j<N; j++) {

		double pulse1Len = i * P/M;
		double pulse2Len = j * P/N;

		double localX[nvar*nNeuron];
		double localT[3*CUTNUMBER];
		for (k=0; k<nvar*nNeuron; k++) localX[k] = x[k];
		//printf ("(%f, %f)\n", pulse1Len, pulse2Len);

		double externPulse = 0.0;
		taylorN (nvar*nNeuron, localX, 0, pulse1Len*P, tol, 0, vshift, CUTNUMBER, localT, externPulse);
		externPulse = 0.02;
		taylorN (nvar*nNeuron, localX, 0, 0.1*P, tol, 0, vshift, CUTNUMBER, localT, externPulse);
		externPulse = 0.0;
		taylorN (nvar*nNeuron, localX, 0, pulse2Len*P, tol, 0, vshift, CUTNUMBER, localT, externPulse);
		externPulse = 0.02;		
		taylorN (nvar*nNeuron, localX, 0, 0.1*P, tol, 0, vshift, CUTNUMBER, localT, externPulse);
		

		externPulse = 0.00;		
		// transient till stabilize
		taylorN (nvar*nNeuron, localX, 0, 5000, tol, 0, vshift, CUTNUMBER, localT, externPulse);

		// compute Poincare sections
		taylorN (nvar*nNeuron, localX, 0, 50000, tol, 1, vshift, CUTNUMBER, localT, externPulse);

		
		// get color
		double localP = localT[1] - localT[0];
		
		double d21 = localT[4]-localT[0];
			if (d21 < 0.0) d21 = localT[5]-localT[0];
		double d31 = localT[8]-localT[0];
		if (d31 < 0.0) d31 = localT[9]-localT[0];

		//printf ("d21 = %f   d31 = %f\n", d21, d31);
		printf ("Final state = (%f %f) ---- > ", d21/localP, d31/localP);

		if (fabs (d21/P - 0.63) + fabs (d31/P) < 0.2 || fabs (d21/P - 0.63) + fabs (d31/P -1.0) < 0.2) {
			printf ("0\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = 0.0;
		}
		else if (fabs (d21/P) + fabs (d31/P - 0.5) < 0.2 || fabs (d21/P - 1.0) + fabs (d31/P - 0.5) < 0.2) {
			printf ("1\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = 1.0;
		}
		else if (fabs (d21/P - 0.4) + fabs (d31/P - 0.4) < 0.2) {
			printf ("2\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = 2.0;
		}
		else if (fabs (d21/P - 0.33) + fabs (d31/P - 0.66) < 0.2) {
			printf ("3\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = 3.0;
		}
		else if (fabs (d21/P - 0.66) + fabs (d31/P - 0.33) < 0.2) {
			printf ("4\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = 4.0;
		}
		else  {
			printf ("????\n");
			//endPoint[M*get_global_id(1) + get_global_id(0)] = -2.0;
		}
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

