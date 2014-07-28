void taylor (real_t x[NCOL]) {

	real_t series[NCOL][ORDER+1];		// STORAGE TAYLOR SERIES
	real_t t;				// INTEGRATION TIME
	real_t step;				// STEPSIZE
	

	t = 0.0;				// INTEGRATION TIME	
	char endOfIntegration = 0;		// END OF INTEGRATION FLAG

	while (t < TF && !endOfIntegration) {
		fun (t, x, series);		// EVALUATE TAYLOR SERIES

		/*printf ("series = \n");
		int k, j;
		for (k=0; k<NCOL; k++) {
			for (j=0; j<4; j++)
				printf ("%.15le ", series[k][j]);
			printf ("\n");
		}
		printf ("\n");*/
		step = getStep (series); 	// GET STEPSIZE
		//printf ("step = %f\n", step);
		if (t + step > TF) {		// CHECK WHETHER IT IS FINAL STEP
			step = TF - t;
			endOfIntegration = 1;
		} 

		
		horner (NCOL, step, series, x); // HORNER EVALUATION
		t = t + step;			// UPDATE TIME
		//return;
	}
}


// TAYLOR INTEGRATOR FOR SINGLE NEURON
real_t taylor_SN (real_t x[3],			// INTEGRATION VARIABLES
		real_t tf,			// FINAL TIME
		char poincare) {		// POINCARE FLAG

	real_t series[3][ORDER+1];		// STORAGE TAYLOR SERIES
	real_t t;				// INTEGRATION TIME
	real_t step;				// STEPSIZE
	

	t = 0.0;				// INTEGRATION TIME	
	char endOfIntegration = 0;		// END OF INTEGRATION FLAG

	
	// POINCARE VARIABLES
	real_t criterion;			// POINCARE CRITERION
	real_t p_x[3];				// POINCARE VARIABLES
	real_t p_t[2];				// POINCARE TIME
	real_t p_d;				// POINCARE DELTA
	char count = 0;				// 2 CUTS FOR COMPUTING PERIOD

	while (t < TF && !endOfIntegration) {
		fun_SN (t, x, series);		// EVALUATE TAYLOR SERIES

	
		step = getStep (series); 	// GET STEPSIZE
		if (t + step > tf) {		// CHECK WHETHER IT IS FINAL STEP
			step = tf - t;
			endOfIntegration = 1;
		} 


		// POINCARE CHECK
		if (event >= 0)	x_old = x[0];
		// END POINCARE CHECK		

		horner (3, step, series, x); // HORNER EVALUATION

		// POINCARE CKECK
		if (poincare)	{
			criterion = x_old * x[0];
			if (criterion < 0) {
				poincare (3, step, series, 0, p_x, &p_d);
				p_t[count] = t + p_d;
				if (count == 2) return p_t[1] - p_t[0];
				count++;
			}

		}
		// END POINCARE CHECK	

		t = t + step;			// UPDATE TIME
	}
}




void poincare (int nvar, 			// DIMENSION OF THE PROBLEM
		real_t step,			// STEPSIZE
		real_t series[nvar][ORDER+1],	// TAYLOR SERIES
		int event, 			// VARIABLE TO CHECK EVENT
		real_t rop[nvar],		// VARIABLE VALUE AT POINCARE EVENT
		real_t *dt) {			// DELTA TIME FOR POINCARE EVENT (t + dt)

	real_t h_L = 0.0			// LEFT VALUE FOR DELTA
	real_t h_R = step;			// RIGHT VALUE FOR DELTA
	real_t h_M;				// MID POINT FOR DELTA

	real_t p_L;				// VALUE OF EVENT VARIABLE AT LEFT DELTA
	real_t p_R;				// VALUE OF EVENT VARIABLE AT RIGHT DELTA
	real_t p_M;				// VALUE OF EVENT VARIABLE AT MID POINT DELTA
	real_t x[nvar];				// VARIABLES TO EVALUATE HORNER


	do {
		h_M = (h_L + h_R)/2.;			// DEFINE MID POINT

		// HORNER EVALUATIONS
		horner (3, h_L, series, x);
		p_L = x[event];
		horner (3, h_R, series, x);		// HORNER EVALUATION
		p_R = x[event];
		horner (3, h_M, series, x);		// HORNER EVALUATION
		p_M = x[event];

		if (p_M * p_L < 0.) 
			h_R = h_M;
		else 
			h_L = h_M;

	} while (fabs (p_M) > 1e-10);
	horner (3, h_M, series, rop);
	*dt = h_M;
}




// COMPUTES STEP-SIZE FROM VARIABLES (NOT VARIATIONALS)
real_t getStep (real_t series[NCOL][ORDER+1]) {

	short k;
	real_t n1, n2;
	real_t x1[NVAR], x2[NVAR];

	for (k=0; k<NVAR; k++) {
		x1[k] = series[k][ORDER];
		x2[k] = series[k][ORDER-1];
	}

	/*printf ("x1 = \n");
	for (k=0; k<NVAR; k++)
		printf ("%.15le ", x1[k]);
	printf ("\n");*/

	n1 = normInf (NVAR, x1); n2 = normInf (NVAR, x2);

	

	//printf ("n1 = %f, n2 = %f\n", n1, n2);
	real_t h1, h2;

	h1 = pow ((TOL/n1), (1./ORDER));
	h2 = pow ((TOL/n2), (1./ORDER-1));
	//printf ("h1 = %f, h2 = %f\n", h1, h2);
	
	if (h1 < h2) return h1;
	return h2;
}

// HORNER EVALUATION (nvar 
void horner (short n,	 			// NVAR OR NCOL
		real_t h, 			// STEPSIZE
		real_t series[n][ORDER+1],	// TAYLOR SERIES
		real_t *x) {			// OUTPUT 

	short k;				// COUNTER FOR VARIABLES
	short j;				// COUNTER FOR ORDER
	
	for (k=0; k<n; k++) x[k] = series[k][ORDER]; 
	for (j=ORDER-1; j>=0; j--)
		for (k=0; k<n; k++) 
			x[k] = x[k]*h + series[k][j];
}

// COMPUTES INFINITE NORM OF AN ARRAY
real_t normInf (short n,			// NVAR OR NCOL
		real_t *x) {			// ARRAY

	real_t rop = 0.0;			// OUTPUT
	short k;				// COUNTER FOR VARIABLES
	for (k=0; k<n; k++)
		if (fabs (x[k]) > rop) rop = fabs (x[k]);
	return rop;

}
