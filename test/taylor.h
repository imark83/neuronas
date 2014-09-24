
inline real_t taylor2 (real_t x[NVAR2], real_t tf, int event, real_t VSHIFT) {

	real_t series[NVAR2][ORDER+1];	// STORAGE TAYLOR SERIES

	real_t t;			// INTEGRATION TIME
	real_t step;			// STEPSIZE
	
	int i, j;


	real_t P[2];			// PERIOD OF THE TRAJECTORY
	int endOfIntegrate = 0;

	t = 0.0;
	while (t < tf && !endOfIntegrate) {
		fun2 (x, series, VSHIFT);

		step = getStep2 (series);
		if (t + step > tf) {
			step = tf - t;
			endOfIntegrate = 1;
		} 


		
		horner2 (step, series, x); 

		printf ("t = %f\n", t);
		t = t + step;
		printf ("x = %f %f %f\n", x[0], x[1], x[2]);
	}
	return 0.0;
}



void poincare2 (real_t step, real_t series[NVAR2][ORDER+1], int event, 
		real_t rop[NVAR2], real_t *dt) {
	real_t h_L = 0., h_R = step, h_M;
	real_t p_L, p_R, p_M, x[NVAR2];
	real_t error; 
	horner2 (h_R, series, x);
	do {
		horner2 (h_L, series, x); 
		p_L = x[event] - EVENTVALUE;
		horner2 (h_R, series, x); 
		p_R = x[event] - EVENTVALUE;
		h_M = (h_L + h_R)/2.;
		horner2 (h_M, series, x); 
		p_M = x[event] - EVENTVALUE;
		if (p_M * p_L < 0.) 
			h_R = h_M;
		else 
			h_L = h_M;
		error = p_M;
	} while (fabs (p_M) > 1e-14);
	horner2 (h_M, series, rop);
	*dt = h_M;
}


real_t getStep2 (real_t series[NVAR2][ORDER+1]) {

	real_t n1, n2;
	real_t x1[NVAR2], x2[NVAR2];
	unsigned short i;
	for (i=0; i<NVAR2; i++) {
		x1[i] = series[i][ORDER];
		x2[i] = series[i][ORDER-1];
	}
	n1 = normInf2 (x1); n2 = normInf2 (x2);
	real_t h1, h2;

	h1 = powr ((TOL/n1), (1.0/ORDER));
	h2 = powr ((TOL/n2), (1.0/(ORDER-1.0)));

	if (h1 < h2) return h1;
	return h2;
}





void horner2 (real_t h, real_t series[NVAR2][ORDER+1],
		real_t x[NVAR2]) {
	short i, j;
	
	for (i=0; i<NVAR2; i++) x[i] = series[i][ORDER]; 
	for (i=ORDER-1; i>=0; i--)
		for (j=0; j<NVAR2; j++) 
			x[j] = x[j]*h + series[j][i];
}


real_t normInf2 (real_t x[NVAR2]) {
	real_t rop = 0.0;
	unsigned short i;
	for (i=0; i<NVAR2; i++) 
		if (fabs (x[i]) > rop) rop = fabs (x[i]);
	return rop;

}
