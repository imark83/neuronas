real_t taylor ( real_t x[NCOL],			// INTEGRATION VARIABLES
		real_t tf,			// END TIME
		char poincareFlag) {		// POINCARE FLAG

	real_t series[NCOL][ORDER+1];		// STORAGE TAYLOR SERIES
	real_t t;				// INTEGRATION TIME
	real_t step;				// STEPSIZE
	

	t = 0.0;				// INTEGRATION TIME	
	char endOfIntegration = 0;		// END OF INTEGRATION FLAG

	// POINCARE VARIABLES
	real_t x_old;
	real_t criterion;			// POINCARE CRITERION
	real_t p_x[NCOL];			// POINCARE VARIABLES
	real_t p_t[2];				// POINCARE TIME
	real_t p_d;				// POINCARE DELTA
	char count = 0;				// 2 CUTS FOR COMPUTING PERIOD


	while (t < TF && !endOfIntegration) {
		// EVALUATE TAYLOR SERIES
		fun (t, x, series);	
	
		// GET STEPSIZE
		step = getStep (series); 	

		// CHECK WHETHER IT IS FINAL STEP
		if (t + step > TF) {		
			step = TF - t;
			endOfIntegration = 1;
		} 

		// POINCARE CHECK
		if (poincareFlag)
			x_old = x[0] - EVENTVALUE;
		// END POINCARE CHECK	

		// HORNER EVALUATION
		horner (NCOL, step, series, x); 

		// POINCARE CKECK
		if (poincareFlag) {
			criterion = x_old * (x[0]-EVENTVALUE);
			if (criterion < 0 && x_old < 0.0) {
				poincare (step, series, 0, p_x, &p_d);
				p_t[count] = t + p_d;
				if (count == 1) return p_t[1] - p_t[0];
				count++;
			}

		}
		// END POINCARE CHECK	

		// UPDATE TIME
		t = t + step;		
		//printf ("%f %f\n", t, x[0]);	
	}
	return 0.0;
}

void poincare (	real_t step,			// STEPSIZE
		real_t series[NCOL][ORDER+1],	// TAYLOR SERIES
		short event, 			// VARIABLE TO CHECK EVENT
		real_t rop[NCOL],		// VARIABLE VALUE AT POINCARE EVENT
		real_t *dt) {			// DELTA TIME FOR POINCARE EVENT (t + dt)

	real_t h_L = 0.0;			// LEFT VALUE FOR DELTA
	real_t h_R = step;			// RIGHT VALUE FOR DELTA
	real_t h_M;				// MID POINT FOR DELTA

	real_t p_L;				// VALUE OF EVENT VARIABLE AT LEFT DELTA
	real_t p_R;				// VALUE OF EVENT VARIABLE AT RIGHT DELTA
	real_t p_M;				// VALUE OF EVENT VARIABLE AT MID POINT DELTA
	real_t x[NCOL];				// VARIABLES TO EVALUATE HORNER


	do {
		// DEFINE MID POINT
		h_M = (h_L + h_R)/2.;			

		// HORNER EVALUATIONS
		horner (NCOL, h_L, series, x);
		p_L = x[event] - EVENTVALUE;
		horner (NCOL, h_R, series, x);
		p_R = x[event] - EVENTVALUE;
		horner (NCOL, h_M, series, x);
		p_M = x[event] - EVENTVALUE;

		// UPDATE POINTS OF BISECTION
		if (p_M * p_L < 0.) 
			h_R = h_M;
		else 
			h_L = h_M;

	} while (fabs (p_M) > 1e-10);

	// OUTPUT VARIABLES
	horner (NCOL, h_M, series, rop);
	*dt = h_M;
}

// COMPUTES STEP-SIZE FROM VARIABLES (NOT VARIATIONALS)
real_t getStep (real_t series[NCOL][ORDER+1]) {	// TAYLOR SERIES

	short k;				// COUNTER FOR VARIABLES
	real_t n1, n2;				// STORE NORM OF TAYLOR ERRORS
	real_t x1[NVAR], x2[NVAR];		// STORE TAYLOR ERRORS (LASTS TERMS)
	real_t h1, h2;				// STORE CANDIDATES FOR STEP SIZE

	// STORE TAYLOR ERRORS IN VARIABLES
	for (k=0; k<NVAR; k++) {
		x1[k] = series[k][ORDER];
		x2[k] = series[k][ORDER-1];
	}

	// COMPUTE NORMS
	n1 = normInf (NVAR, x1); n2 = normInf (NVAR, x2);

	// COMPUTE CANDIDATES FOR STEPSIZE
	h1 = pow ((TOL/n1), (1./ORDER));
	h2 = pow ((TOL/n2), (1./ORDER-1));

	// RETURNS MINIMUM VALUE OF h1 AND h2	
	if (h1 < h2) return h1;
	return h2;
}

// HORNER EVALUATION
void horner (	short n,	 		// NVAR OR NCOL
		real_t h, 			// STEPSIZE
		real_t series[NCOL][ORDER+1],	// TAYLOR SERIES
		real_t *x) {			// OUTPUT 

	short k;				// COUNTER FOR VARIABLES
	short j;				// COUNTER FOR ORDER
	
	// HORNER ALGORITHM
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
