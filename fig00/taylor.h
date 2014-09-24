void taylor (real_t *x, real_t tf, real_t *delay, real_t VSHIFT, int cutNumber) {

	real_t series[NVAR][ORDER+1];	// STORAGE TAYLOR SERIES

	real_t t;			// INTEGRATION TIME
	real_t step;			// STEPSIZE
	
	int i, j;


/*******************************************
******* POINCARE*/
	real_t criterion, pCut[NVAR], tCut, y_old[NVAR/3];
	unsigned int count[NVAR/3];
	for (j=0; j<NVAR/3; j++) count[j] = 0;

/******** 
*******************************************/

	t = 0.0;
	while (t < tf) {
		fun (x, series, VSHIFT);
		step = getStep (series); 



	/*******************************************
	******* POINCARE*/
		if (delay != (real_t*) 0) {
			for (j=0; j<NVAR/3; j++)
				y_old[j] = x[3*j] - EVENTVALUE;	
		}
	/******** 
	*******************************************/
		
		horner (step, series, x); 

	/*******************************************
	******* POINCARE*/
		if (delay != (real_t*) 0) {
			for (j=0; j<NVAR/3; j++) {
				criterion = y_old[j] * (x[3*j] - EVENTVALUE);
				if ((criterion < 0) && y_old[j] < 0) {
					if (count[j] == cutNumber) return;
					poincare (step, series, 3*j, pCut, &tCut);
					delay[count[j] + CUTNUMBER*j] = tCut + t;
					count[j]++;
				}
			}
		}
	/******** 
	*******************************************/
		
		t = t + step;
	}

}

real_t taylor2 (real_t *x, real_t tf, int event, real_t VSHIFT) {

	real_t series[NVAR2][ORDER+1];	// STORAGE TAYLOR SERIES

	real_t t;			// INTEGRATION TIME
	real_t step;			// STEPSIZE
	
	int i, j;


	real_t P[2];			// PERIOD OF THE TRAJECTORY
	int endOfIntegrate = 0;
/*******************************************
******* POINCARE*/
	real_t criterion, pCut[NVAR2], tCut, y_old;
	real_t yy[NVAR2];
	int count = 0;

/******** 
*******************************************/

	t = 0.0;
	while (t < tf && !endOfIntegrate) {
		fun2 (x, series, VSHIFT);


		step = getStep2 (series);
		if (t + step > tf) {
			step = tf - t;
			endOfIntegrate = 1;
		} 



	/*******************************************
	******* POINCARE*/
		if (event >= 0)	{
			y_old = x[0] - EVENTVALUE;	
			for (i=0; i<NVAR2; i++) yy[i] = x[i];
		}	
	/******** 
	*******************************************/
		
		horner2 (step, series, x); 

	/*******************************************
	******* POINCARE*/
		if (event >= 0)	{
			criterion = y_old * (x[0] - EVENTVALUE);
			if ((criterion < 0) && (y_old < 0)) {
				poincare2 (step, series, 0, pCut, &tCut);
				P[count] = tCut + t;
				count++;
				if (count == 2) {
					for (i=0; i<NVAR; i++)
						x[i] = yy[i];
					return (P[1] - P[0]);
				}
			}
		
		}
	/******** 
	*******************************************/
		
		t = t + step;
	}
	return 0.0;
}

void poincare (real_t step, real_t series[NVAR][ORDER+1], int event, 
		real_t rop[NVAR], real_t *dt) {
	real_t h_L = 0., h_R = step, h_M;
	real_t p_L, p_R, p_M, x[NVAR];
	real_t error; 
	horner (h_R, series, x);
	do {
		horner (h_L, series, x); 
		p_L = x[event] - EVENTVALUE;
		horner (h_R, series, x); 
		p_R = x[event] - EVENTVALUE;
		h_M = (h_L + h_R)/2.;
		horner (h_M, series, x); 
		p_M = x[event] - EVENTVALUE;
		if (p_M * p_L < 0.) 
			h_R = h_M;
		else 
			h_L = h_M;
		error = p_M;
	} while (fabs (p_M) > 1e-14);
	horner (h_M, series, rop);
	*dt = h_M;
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

real_t getStep (real_t series[NVAR][ORDER+1]) {
	real_t n1, n2;
	real_t x1[NVAR], x2[NVAR];
	__private unsigned short i;
	for (i=0; i<NVAR; i++) {
		x1[i] = series[i][ORDER];
		x2[i] = series[i][ORDER-1];
	}
	n1 = normInf (x1); n2 = normInf (x2);
	real_t h1, h2;

	h1 = pow ((TOL/n1), (1./ORDER));
	h2 = pow ((TOL/n2), (1./ORDER-1));
	
	if (h1 < h2) return h1;
	return h2;
}


real_t getStep2 (real_t series[NVAR2][ORDER+1]) {
	real_t n1, n2;
	real_t x1[NVAR2], x2[NVAR2];
	__private unsigned short i;
	for (i=0; i<NVAR2; i++) {
		x1[i] = series[i][ORDER];
		x2[i] = series[i][ORDER-1];
	}
	n1 = normInf2 (x1); n2 = normInf2 (x2);
	real_t h1, h2;

	h1 = pow ((TOL/n1), (1./ORDER));
	h2 = pow ((TOL/n2), (1./ORDER-1));
	
	if (h1 < h2) return h1;
	return h2;
}


void horner (real_t h, real_t series[NVAR][ORDER+1],
		real_t *x) {
	short i, j;
	
	for (i=0; i<NVAR; i++) x[i] = series[i][ORDER]; 
	for (i=ORDER-1; i>=0; i--)
		for (j=0; j<NVAR; j++) 
			x[j] = x[j]*h + series[j][i];
}



void horner2 (real_t h, real_t series[NVAR2][ORDER+1],
		real_t *x) {
	short i, j;
	
	for (i=0; i<NVAR2; i++) x[i] = series[i][ORDER]; 
	for (i=ORDER-1; i>=0; i--)
		for (j=0; j<NVAR2; j++) 
			x[j] = x[j]*h + series[j][i];
}

real_t normInf (real_t x[NVAR]) {
	real_t rop = 0.;
	unsigned short i;
	for (i=0; i<NVAR; i++) 
		if (fabs (x[i]) > rop) rop = fabs (x[i]);
	return rop;

}

real_t normInf2 (real_t x[NVAR/3]) {
	real_t rop = 0.;
	unsigned short i;
	for (i=0; i<NVAR/3; i++) 
		if (fabs (x[i]) > rop) rop = fabs (x[i]);
	return rop;

}
