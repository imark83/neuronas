
real_t getStep (real_t series[NVAR][ORDER+1]) {
	real_t h1 = fabs (series[0][ORDER]);
	real_t h2 = fabs (series[0][ORDER-1]);
	int i;
	for (i=1; i<NVAR; i++) {
		if (fabs (series[i][ORDER]) > h1) h1 = fabs (series[i][ORDER]);
		if (fabs (series[i][ORDER-1]) > h2) h2 = fabs (series[i][ORDER-1]);
	}
	h1 = TOL / h1; h2 = TOL / h2;
	h1 = powr (h1, 1.0/ORDER);
	h2 = powr (h2, 1.0/(ORDER-1.0));
	if (h1 < h2) return h1;
	return h2;
	

} 

void horner (real_t x[NVAR], real_t series[NVAR][ORDER+1], real_t stepsize) {
	int i;			// counter for variable
	int j;			// counter for order
	for (i=0; i<NVAR; i++) x[i] = series[i][ORDER];
	for (j=ORDER-1; j>=0; j--) for (i=0; i<NVAR; i++)
		x[i] = stepsize * x[i] + series[i][j];

}

void poincare (real_t *dt, real_t series[NVAR][ORDER+1], real_t stepsize, int neuron) {
	real_t h_L, h_M, h_R;			// to store refinements of dt
	real_t p_L, p_M, p_R, x[NVAR];		// to store refinaments of variables
	h_L = 0.0;
	h_R = stepsize;
	h_M = stepsize / 2.0;

	horner (x, series, h_L); p_L = x[3*neuron] - EVENTVALUE;
	horner (x, series, h_M); p_M = x[3*neuron] - EVENTVALUE;
	horner (x, series, h_R); p_R = x[3*neuron] - EVENTVALUE;

	do {
		if (p_M < 0.0)
			h_L = h_M;
		else
			h_R = h_M;
	
		h_M = (h_R + h_L) / 2.0;
		horner (x, series, h_L); p_L = x[3*neuron] - EVENTVALUE;
		horner (x, series, h_M); p_M = x[3*neuron] - EVENTVALUE;
		horner (x, series, h_R); p_R = x[3*neuron] - EVENTVALUE;
	} while (fabs (p_M) > 1.0e-12);

	*dt = h_M;

}

void taylor (real_t x[NVAR], real_t tf, real_t delay[3*CUTNUMBER], real_t VSHIFT, int cutnumber) {

	real_t series[NVAR][ORDER+1];			// TAYLOR SERIES
	real_t t = 0.0;					// INTEGRATION TIME
	real_t stepsize;				// STEP SIZE FOR INTEGRATION

	// POINCARE VARIABLES
	real_t dt;
	real_t criterion;				// TEST POINCARE CROSS
	real_t x_old[NVAR];				// STORE PREVIOUS POSITION
	int count[3] = {0, 0, 0};			// COUNTERS (STOP AT CUTNUMBER)

	int i, j;
	while (t<tf) {
		fun (x, series, VSHIFT);
		stepsize = getStep (series);


		// poincare block
		if (delay != (real_t*) 0) for (i=0; i<NVAR; i++) x_old[i] = x[i];
		// end of poincare block

		horner (x, series, stepsize);

		// poincare block 
		if (delay != (real_t*) 0) {
			for (j=0; j<3; j++) {
				criterion = (x[3*j] - EVENTVALUE) * (x_old[3*j] - EVENTVALUE);
				if ((criterion < 0.0) && (x_old[3*j] < EVENTVALUE)) {		// enter refinement process
					if (count[j] == cutnumber) return;
					poincare (&dt, series, stepsize, j);
					delay[j*CUTNUMBER + count[j]] = t + dt;
					count[j]++;
				}	
			}
		}
		// end of poincare block


		t = t + stepsize;
		/*printf ("%.15le", t);
		for (i=0; i<9; i++) printf ("  %.15le", x[i]);
		printf ("\n");*/
		

	}


}





