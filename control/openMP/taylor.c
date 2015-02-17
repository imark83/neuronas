#include "taylor.h"
#include "parameters.h"
#include "fun.h"
//extern int kahan;



FILE *fpoinc;
double taylorS (int nvar, double x[nvar], double t0, double tf, double tol, int event, double vshift) {
	int i;
	int order = getOrder (tol); 

	double series[nvar][order+1];	//para guardar la serie de taylro
	double t;			//posicion de la integracion
	double step;			//paso


/*******************************************
******* POINCARE*/
	double criterion;		// TO CHECK POINCARE CONDITION 
	double x_old[nvar];		// TO STORE VARIABLES PRE_POINCARE MINUS EVENT VALUE
	int count = 0;			// TO COMPUTE PERIOD (stop at 2)
	double P[2];			// TO COMPUTE PERIOD
	double dt;			// to refine time for Poincare

/******** 
*******************************************/

	t = t0;

	char endOfIntegration = 0;
	while (t < tf && !endOfIntegration) {
		funS (nvar, order, t, x, series, vshift);
		step = getStep (nvar, order, series, tol);
		if (t+step > tf) {
			step = tf - t;
			endOfIntegration = 1;
		}

	/*******************************************
	******* POINCARE*/
		if (event) for (i=0; i<nvar; i++) x_old[i] = x[i];	
		
	/******** 
	*******************************************/
		
		horner (nvar, order, step, series, x);


	/*******************************************
	******* POINCARE*/
		if (event)	{
			criterion = (x_old[0] - EVENTVALUE) * (x[0] - EVENTVALUE);
			if ((criterion < 0) && x_old[0] < EVENTVALUE) {
				poincare (nvar, order, step, series, 0, &dt);
				P[count] = t+dt;
				count++;
				if (count == 2) {
					// return to position previous to Poincare section
					for (i=0; i<nvar; i++) x[i] = x_old[i];
					return P[1] - P[0];			// returns PERIOD
				}
				
			}
		
		}
	/******** 
	*******************************************/
		
		t = t + step;

	}

}


void taylorN (int nvar, double x[nvar], double t0, double tf, double tol, int event, double vshift, int cutNumber, double *T, double externPulse) {
	int j;
	int order = getOrder (tol); 

	double series[nvar][order+1];	//para guardar la serie de taylro
	double t;			//posicion de la integracion
	double step;			//paso

/*******************************************
******* POINCARE*/
	double criterion;
	double dt;
	double x_old[nvar];
	int count[3] = {0, 0, 0};			// COUNTERS (STOP AT CUTNUMBER)

/******** 
*******************************************/

	t = t0;

	char endOfIntegration = 0;
	while (t < tf && !endOfIntegration) {
		funN (nvar, order, t, x, series, vshift, externPulse);
		step = getStep (nvar, order, series, tol);
		

	/*******************************************
	******* POINCARE*/
		if (event) for (j=0; j<nvar; j++) x_old[j] = x[j];
		
	/******** 
	*******************************************/
		
		horner (nvar, order, step, series, x);


	/*******************************************
	******* POINCARE*/
		if (event) {
			for (j=0; j<3; j++) {
				criterion = (x[3*j] - EVENTVALUE) * (x_old[3*j] - EVENTVALUE);
				if ((criterion < 0.0) && (x_old[3*j] < EVENTVALUE)) {		// enter refinement process
					if (count[j] == cutNumber) return;
					poincare (nvar, order, step, series, 3*j, &dt);
					T[j*cutNumber + count[j]] = t + dt;			// ??????????????
					count[j]++;
				}	
			}

		}
	/******** 
	*******************************************/

		
		t = t + step;

	}

}



void poincare (int nvar, int order, double step, double series[nvar][order+1], 
		int eventVar, double *dt) {
	double h_L = 0.0, h_R = step, h_M;
	double p_L, p_R, p_M, x[nvar];
	double error;
	horner (nvar, order, h_R, series, x);
	do {
		horner (nvar, order, h_L, series, x); 
		p_L = x[eventVar] - EVENTVALUE;
		horner (nvar, order, h_R, series, x); 
		p_R = x[eventVar] - EVENTVALUE;
		h_M = (h_L + h_R)/2.0;
		horner (nvar, order, h_M, series, x); 
		p_M = x[eventVar] - EVENTVALUE;
		if (p_M * p_L < 0.0) 
			h_R = h_M;
		else 
			h_L = h_M;
		error = p_M;
	} while (fabs (p_M) > 1.0e-10);
	*dt = h_M;
//	printf ("x = [%.16le, %.16le, %.16le, %.16le]\n", x[0], x[1], x[2], x[3]);
}



int getOrder (double tol) {
	return ceil (-log(tol)/2.);	
}

double getStep (int nvar, int order, double series[nvar][order+1], 
		double tol) {
	double n1, n2;
	double x1[nvar], x2[nvar];
	int i;
	for (i=0; i<nvar; i++) {
		x1[i] = series[i][order];
		x2[i] = series[i][order-1];
	}
	n1 = normInf (nvar, x1); n2 = normInf (nvar, x2);
	double h1, h2;

	h1 = pow ((tol/n1), 1./order);
	h2 = pow ((tol/n2), 1./(order-1));
	
	if (h1 < h2) return h1;
	return h2;
}

void horner (int nvar, int order, double h, double series[nvar][order+1], 
		double rop[nvar]) {
	int i, j;
	
	for (i=0; i<nvar; i++) rop[i] = series[i][order];
	for (i=order-1; i>=0; i--)
		for (j=0; j<nvar; j++) 
			rop[j] = rop[j]*h + series[j][i];
}

double normInf (int nvar, double x[nvar]) {
	double rop = 0.;
	int i;
	for (i=0; i<nvar; i++) 
		if (fabs (x[i]) > rop) rop = fabs (x[i]);
	return rop;

}
