

// performs an RK step for a single Neuron. Returns -1 if rejected, 
// otherwise returns FACTOR for next step size
real_t rkStepS (real_t x[NVAR_S], real_t h, real_t fsal[NVAR_S], 
		char eventFlag[1],		// IF NULL INPUT -> NO EVENT SEARCH
						// OUTPUTS EVENT FLAG
		real_t eventVal[1]) {		// OUTPUTS EVENT TIME value

	int j;

	real_t k2[NVAR_S], k3[NVAR_S], k4[NVAR_S], k5[NVAR_S], k6[NVAR_S], k7[NVAR_S];
	real_t *k1 = fsal;			// k1 is given by FSAL stage
	real_t error;				// infinity norm of the estimation of the error
		

	// COMPUTE STAGES OF THE STEP (assume we have an autonomous system)
	// 2
	for (j=0; j<NVAR_S; j++) k2[j] = x[j] + h * (A21*k1[j]);
	fS (k2, k2);
	// 3
	for (j=0; j<NVAR_S; j++) k3[j] = x[j] + h * (A31*k1[j] + A32*k2[j]);
	fS (k3, k3);
	// 4
	for (j=0; j<NVAR_S; j++) k4[j] = x[j] + h * (A41*k1[j] + A42*k2[j] + A43*k3[j]);
	fS (k4, k4);
	// 5
	for (j=0; j<NVAR_S; j++) k5[j] = x[j] + h * (A51*k1[j] + A52*k2[j] + A53*k3[j] + A54*k4[j]);
	fS (k5, k5);
	// 6
	for (j=0; j<NVAR_S; j++) k6[j] = x[j] + h * (A61*k1[j] + A62*k2[j] + A63*k3[j] + A64*k4[j] + A65*k5[j]);
	fS (k6, k6);
	// 7  (A72 = 0)
	for (j=0; j<NVAR_S; j++) k7[j] = x[j] + h * (A71*k1[j] + A73*k3[j] + A74*k4[j] + A75*k5[j] + A76*k6[j]);
	fS (k7, k7);

	// ESTIMATE ERROR (E2 = 0)
	error = 0.0;
	for (j=0; j<NVAR_S; j++) error = error + fabs (E1*k1[j] + E3*k3[j] + E4*k4[j] + E5*k5[j] + E6*k6[j] + E7*k7[j]);
	error = error * h;

	// CHECK TOLERANCE
	if (error > TOL) {
		return -1.0;
	}

	// UP TO HERE, ACCEPTED STEP

	// UPDATE FSAL
	for (j=0; j<NVAR_S; j++) fsal[j] = k7[j];
	
	real_t xNext[NVAR_S];			// next point
	// USE THE 5TH ORDER RK TO GO AHEAD (B2 = B7 = 0)
	for (j=0; j<NVAR_S; j++) xNext[j] = x[j] + h * (B1*k1[j] + B3*k3[j] + B4*k4[j] + B5*k5[j] + B6*k6[j]);


	// CHECK FOR POINCARE EVENTS
	if (eventFlag != (char*) 0) {
		real_t criterion = (x[0] - EVENTVALUE) * (xNext[0] - EVENTVALUE);
		if (criterion < 0 && (xNext[0] > x[0])) {
			eventFlag[0] = 1;
			real_t th_L = 0.0;
			real_t th_R = 1.0;
			real_t th_M = 0.5;
			real_t p_L = DENSE_EVAL(0,th_L) - EVENTVALUE;
			real_t p_R = DENSE_EVAL(0,th_R) - EVENTVALUE;
			real_t p_M = DENSE_EVAL(0,th_M) - EVENTVALUE;
			do {
				if (p_M < 0.0) {
					th_L = th_M;
					th_M = (th_R + th_L) / 2.0;
					p_L = p_M;
					p_M = DENSE_EVAL(0,th_M) - EVENTVALUE;
				} else {
					th_R = th_M;
					th_M = (th_R + th_L) / 2.0;
					p_R = p_M;
					p_M = DENSE_EVAL(0,th_M) - EVENTVALUE;
				}
			} while (fabs (p_M) > 1.0e-6);
			eventVal[0] = th_M * h;
			
		} else {
			eventFlag[0] = 0;
		}
	}


	// ESTIMATE FACTOR FOR NEXT STEP SIZE
	error = 0.9 * pow((1.0/error), 0.2);			// multiplier for next step size
	error = MAX (error, 0.1);			// no smaller than 10%
	error = MIN (error, 1.5);			// no bigger than 150%


	// UPDATE NEXT STEP (OVERWRITE INPUT)
	for (j=0; j<NVAR_S; j++) x[j] = xNext[j];

	// RETURN NEXT STEP SIZE FACTOR
	return error;

}

// IF EVENT, RETURNS PERIOD
real_t rkS (real_t x[NVAR_S], real_t tf, char event) {
	real_t step = INITIAL_STEP;
	real_t fsal[NVAR_S];
	int j;
	for (j=0; j<NVAR_S; j++) fsal[j] = x[j];
	fS(fsal, fsal);
	real_t t = 0.0;
	real_t fac;					// step size correction factor

	// POINCARE VARIABLES
	char _eventFlag[1], *eventFlag;
	real_t _eventVal[1], *eventVal;
	if (event) {
		eventFlag = _eventFlag;
		eventVal = _eventVal;
	} else {
		eventFlag = (char*) 0;
		eventVal = (real_t*) 0;
	}
	real_t P[2];
	char count = 0;
	
	char endOfIntegration = 0;
	while (t<tf && !endOfIntegration) {
		fac = rkStepS (x, step, fsal, eventFlag, eventVal);

		if (fac < 0) {				// rejected step
			step = 0.2 * step;	
		} else {
			if (event) if (eventFlag[0]) {
				P[count] = t + eventVal[0];
				count++;
				if (count == 2) return P[1] - P[0];
			}
			t += step;
			//printf ("%e %e\n", t, x[0]);
			step = fac * step;
			step = MIN (step, tf-t);
			if (tf-t < 1e-10) endOfIntegration = 1;
		}
	}
	return 0.0;

}
