

// performs an RK step for a single Neuron. Returns -1 if rejected, 
// otherwise returns FACTOR for next step size
real_t rkStepN (real_t xNext[NVAR_N], real_t x[NVAR_N], real_t h, real_t fsal[NVAR_N], 
		char eventFlag[3],		// IF NULL INPUT -> NO EVENT SEARCH
						// OUTPUTS EVENT FLAG
		real_t eventVal[3]) {		// OUTPUTS EVENT TIME value

	int j;

	real_t k2[NVAR_N], k3[NVAR_N], k4[NVAR_N], k5[NVAR_N], k6[NVAR_N], k7[NVAR_N];
	real_t *k1 = fsal;			// k1 is given by FSAL stage
	real_t error;				// infinity norm of the estimation of the error
		

	// COMPUTE STAGES OF THE STEP (assume we have an autonomous system)
	// 2
	for (j=0; j<NVAR_N; j++) k2[j] = x[j] + h * (A21*k1[j]);
	fN (k2, k2);
	// 3
	for (j=0; j<NVAR_N; j++) k3[j] = x[j] + h * (A31*k1[j] + A32*k2[j]);
	fN (k3, k3);
	// 4
	for (j=0; j<NVAR_N; j++) k4[j] = x[j] + h * (A41*k1[j] + A42*k2[j] + A43*k3[j]);
	fN (k4, k4);
	// 5
	for (j=0; j<NVAR_N; j++) k5[j] = x[j] + h * (A51*k1[j] + A52*k2[j] + A53*k3[j] + A54*k4[j]);
	fN (k5, k5);
	// 6
	for (j=0; j<NVAR_N; j++) k6[j] = x[j] + h * (A61*k1[j] + A62*k2[j] + A63*k3[j] + A64*k4[j] + A65*k5[j]);
	fN (k6, k6);
	// 7  (A72 = 0)
	for (j=0; j<NVAR_N; j++) k7[j] = x[j] + h * (A71*k1[j] + A73*k3[j] + A74*k4[j] + A75*k5[j] + A76*k6[j]);
	fN (k7, k7);

	// ESTIMATE ERROR (E2 = 0)
	error = 0.0;
	for (j=0; j<NVAR_N; j++) error = error + fabs(E1*k1[j] + E3*k3[j] + E4*k4[j] + E5*k5[j] + E6*k6[j] + E7*k7[j]);
	error = error * h;

	//printf ("step %e\terror est = %e\n", h, error);

	// compute norm of x
	real_t normX = fabs (x[0]);
	for (j=1; j<NVAR_N; j++) normX += fabs (x[0]);
	// CHECK TOLERANCE
	if (error > TOL) {
		return -1.0;
	}
	if (error > TOL*normX) {
		return -1.0;
	}

	// UP TO HERE, ACCEPTED STEP

	
	// USE THE 5TH ORDER RK TO GO AHEAD (B2 = B7 = 0)
	for (j=0; j<NVAR_N; j++) xNext[j] = x[j] + h * (B1*k1[j] + B3*k3[j] + B4*k4[j] + B5*k5[j] + B6*k6[j]);


	// CHECK FOR POINCARE EVENTS
	int count = 0;
	if (eventFlag != (char*) 0) {
		for (j=0; j<3; j++) {
			real_t criterion = (x[3*j] - EVENTVALUE) * (xNext[3*j] - EVENTVALUE);
			if (criterion < 0.0 && (xNext[3*j] > x[3*j])) {
				eventFlag[j] = 1;
				real_t th_L = 0.0;
				real_t th_R = 1.0;
				real_t th_M = 0.5;
				real_t p_L = DENSE_EVAL(3*j,th_L) - EVENTVALUE;
				real_t p_R = DENSE_EVAL(3*j,th_R) - EVENTVALUE;
				real_t p_M = DENSE_EVAL(3*j,th_M) - EVENTVALUE;
				do {
					if (p_M < 0.0) {
						th_L = th_M;
						th_M = (th_R + th_L) / 2.0;
						p_L = p_M;
						p_M = DENSE_EVAL(3*j,th_M) - EVENTVALUE;
					} else {
						th_R = th_M;
						th_M = (th_R + th_L) / 2.0;
						p_R = p_M;
						p_M = DENSE_EVAL(3*j,th_M) - EVENTVALUE;
					}
				} while (fabs (p_M) > 10.0*TOL);
				eventVal[j] = th_M * h;
			
			} else {
				eventFlag[j] = 0;
			}
		}
	}


	// ESTIMATE FACTOR FOR NEXT STEP SIZE
	error = pow((TOL/error), 0.2);	// multiplier for next step size
	error = MAX (error, 0.1);			// no smaller than 10%
	error = MIN (error, 1.5);			// no bigger than 150%


	// UPDATE NEXT STEP (OVERWRITE INPUT)

	// UPDATE FSAL
	for (j=0; j<NVAR_N; j++) fsal[j] = k7[j];

	// RETURN NEXT STEP SIZE FACTOR
	return 0.9*error;

}

// 
void rkN (real_t x[NVAR_N], real_t tf, real_t delay[3*CUTNUMBER], int cutNumber) {
	real_t step = INITIAL_STEP;
	real_t fsal[NVAR_N];
	real_t xNext[NVAR_N];
	int j;
	for (j=0; j<NVAR_N; j++) fsal[j] = x[j];
	fN(fsal, fsal);
	real_t t = 0.0;
	real_t fac;					// step size correction factor

	// POINCARE VARIABLES
	char _eventFlag[3], *eventFlag;
	real_t _eventVal[3], *eventVal;
	if (delay != (real_t*) 0) {
		eventFlag = _eventFlag;
		eventVal = _eventVal;
	} else {
		eventFlag = (char*) 0;
		eventVal = (real_t*) 0;
	}
	int count[3] = {0, 0, 0};
	
	char endOfIntegration = 0;
	while (t<tf && !endOfIntegration) {
		fac = rkStepN (xNext, x, step, fsal, eventFlag, eventVal);

		if (fac < 0) {				// rejected step
			step = 0.2 * step;
		} else {
			if (delay != (real_t*) 0) for (j=0; j<3; j++) {
				if (eventFlag[j]) {		// enter refinement process
					if (count[j] == cutNumber) return;
					delay[j*CUTNUMBER + count[j]] = t + eventVal[j];
					count[j]++;
				}
			}			
			t += step;
			for (j=0; j<NVAR_N; j++) x[j] = xNext[j];
			//if(t>800); printf ("%e %e %e %e\n", t, x[0], x[3], x[6]);
			step = fac * step;
			step = MIN (step, tf-t);
			if (tf-t < 1e-10) endOfIntegration = 1;
		}
	}

}
