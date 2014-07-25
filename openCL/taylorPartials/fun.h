__constant int RANGE_SET[] = {0, 1, 3};
__constant int VI_SET[]    = {0, 0, 1};
__constant int IV_SET[]    = {0, 1, 0};
__constant int COMB_SET[]  = {1, 1, 1};

__constant int RANGE_STAR[] = {0, 1, 2};
__constant int VI_STAR[]    = {0, 0};
__constant int IV_STAR[]    = {0, 0};
__constant int COMB_STAR[]  = {1, 1};

void fun (real_t t, real_t *x, real_t series[NCOL][ORDER+1]) {

	int k, i, j;
	
	double v[NVAR][NDER+1][ORDER+1];		//para las variables
		for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) 
			v[k][i][0] = x[k+NVAR*i];

	double l[10][NDER+1][ORDER+1];
	for (j=0; j<ORDER; j++) {
		dp_mulAD (j, l[0], v[1], v[0]);
		dp_mlCAD (j, l[1], l[0], -2.00000000000000);
		dp_mlCAD (j, l[2], v[0], -1.00000000000000);
		dp_sumAD (j, l[3], l[1], l[2]);
		dp_mulAD (j, l[4], v[0], v[0]);
		dp_mlCAD (j, l[5], l[4], -1.00000000000000);
		dp_mulAD (j, l[6], v[1], v[1]);
		dp_sumAD (j, l[7], l[5], l[6]);
		dp_mlCAD (j, l[8], v[1], -1.00000000000000);
		dp_sumAD (j, l[9], l[7], l[8]);


		for (i=0; i<=NDER; i++) {
			v[0][i][j+1] = v[2][i][j] / (j+1.0);
			v[1][i][j+1] = v[3][i][j] / (j+1.0);
			v[2][i][j+1] = l[3][i][j] / (j+1.0);
			v[3][i][j+1] = l[9][i][j] / (j+1.0);
		}

	}

	for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) for (j=0; j<=ORDER; j++)
		series[k+i*NVAR][j] = v[k][i][j];

}

