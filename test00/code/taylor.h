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
		real_t series[NCOL][ORDER+1],	// TAYLOR SERIES
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
