
real_t getStep1 (real_t series[NVAR1][ORDER+1]) {
	real_t h1 = fabs (series[0][ORDER]);
	real_t h2 = fabs (series[0][ORDER-1]);
	int i;
	for (i=1; i<NVAR1; i++) {
		if (fabs (series[i][ORDER]) > h1) h1 = fabs (series[i][ORDER]);
		if (fabs (series[i][ORDER-1]) > h2) h2 = fabs (series[i][ORDER-1]);
	}
	h1 = TOL / h1; h2 = TOL / h2;
	h1 = powr (h1, 1.0/ORDER);
	h2 = powr (h2, 1.0/(ORDER-1.0));
	if (h1 < h2) return h1;
	return h2;
	

} 

void horner1 (real_t x[NVAR1], real_t series[NVAR1][ORDER+1], real_t stepsize) {
	int i;			// counter for variable
	int j;			// counter for order
	for (i=0; i<NVAR1; i++) x[i] = series[i][ORDER];
	for (j=ORDER-1; j>=0; j--) for (i=0; i<NVAR1; i++)
		x[i] = stepsize * x[i] + series[i][j];

}

void poincare1 (real_t *dt, real_t series[NVAR1][ORDER+1], real_t stepsize) {
	real_t h_L, h_M, h_R;			// to store refinements of dt
	real_t p_L, p_M, p_R, x[NVAR1];		// to store refinaments of variables
	h_L = 0.0;
	h_R = stepsize;
	h_M = stepsize / 2.0;

	horner1 (x, series, h_L); p_L = x[0] - EVENTVALUE;
	horner1 (x, series, h_M); p_M = x[0] - EVENTVALUE;
	horner1 (x, series, h_R); p_R = x[0] - EVENTVALUE;

	do {
		if (p_M < 0.0)
			h_L = h_M;
		else
			h_R = h_M;
	
		h_M = (h_R + h_L) / 2.0;
		horner1 (x, series, h_L); p_L = x[0] - EVENTVALUE;
		horner1 (x, series, h_M); p_M = x[0] - EVENTVALUE;
		horner1 (x, series, h_R); p_R = x[0] - EVENTVALUE;
	} while (fabs (p_M) > 1.0e-12);

	*dt = h_M;

}

real_t taylor1 (real_t x[NVAR1], real_t tf, int event, real_t VSHIFT) {

	real_t series[NVAR1][ORDER+1];			// TAYLOR SERIES
	real_t t = 0.0;					// INTEGRATION TIME
	real_t stepsize;				// STEP SIZE FOR INTEGRATION

	// POINCARE VARIABLES
	real_t dt;
	real_t criterion;				// TEST POINCARE CROSS
	real_t x_old[NVAR1];				// STORE PREVIOUS POSITION
	real_t P[2];					// TO COMPUTE PERIOD
	int count = 0;					// COUNTER (STOP AT 2)

	int i;
	int endOfIntegration = 0;
	while (t<tf && !endOfIntegration) {
		fun1 (x, series, VSHIFT);
		stepsize = getStep1 (series);
		if (t+stepsize > tf) {
			stepsize = tf - t;
			endOfIntegration = 1;
		}


		// poincare block
		if (event) for (i=0; i<NVAR1; i++) x_old[i] = x[i];
		// end of poincare block

		horner1 (x, series, stepsize);

		// poincare block 
		if (event) {
			criterion = (x[0] - EVENTVALUE) * (x_old[0] - EVENTVALUE);
			if ((criterion < 0.0) && (x_old[0] < EVENTVALUE)) {		// enter refinement process
				poincare1 (&dt, series, stepsize);
				P[count] = t + dt;
				count++;
				if (count == 2) {
					// return to position previous to Poincare section
					for (i=0; i<NVAR1; i++) x[i] = x_old[i];
					return P[1] - P[0];			// returns PERIOD
				}
			
			}
		}
		// end of poincare block


		t = t + stepsize;
		/*printf ("%.15le", t);
		for (i=0; i<3; i++) printf ("  %.15le", x[i]);
		printf ("\n");*/
		

	}


	return 0.0;
}





