__constant int RANGE_SET[] = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
__constant int VI_SET[]    = {0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9};
__constant int IV_SET[]    = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0};
__constant int COMB_SET[]  = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

__constant int RANGE_STAR[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
__constant int VI_STAR[]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
__constant int IV_STAR[]    = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
__constant int COMB_STAR[]  = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void fun_partials (real_t t, real_t *x, real_t series[NCOL][ORDER+1]) {

	int k, i, j;
	
	real_t v[NVAR][NDER+1][ORDER+1];		//para las variables
		for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) 
			v[k][i][0] = x[k+NVAR*i];




	double par[14] = {THSYN,ESYN,GSYN,ENA,GNA,EK,GK2,EL,GL,C,TNA,TK2,VSHIFT,IAPP};

	double l[144][NDER+1][ORDER+1];
	double c[6];
	c[0] = (1000.00000000000) * par[0];
	c[1] = (-1.00000000000000) * par[13];
	c[2] = (1.00000000000000) / par[9];
	c[3] = (1.00000000000000) / par[10];
	c[4] = (-83.0000000000000) * par[12];
	c[5] = (1.00000000000000) / par[11];
	for (j=0; j<ORDER; j++) {
		dp_mlCAD_partials (j, l[0], v[0], -1.00000000000000);
		dp_smCAD_partials (j, l[1], l[0], par[5]);
		dp_mlCAD_partials (j, l[2], l[1], par[6]);
		dp_mulAD_partials (j, l[3], v[2], v[2]);
		dp_mulAD_partials (j, l[4], l[3], l[2]);
		dp_smCAD_partials (j, l[5], l[0], par[1]);
		dp_mlCAD_partials (j, l[6], l[5], par[2]);
		dp_mlCAD_partials (j, l[7], v[3], -1000.00000000000);
		dp_smCAD_partials (j, l[8], l[7], c[0]);
		dp_expAD_partials (j, l[9], l[8]);
		dp_smCAD_partials (j, l[10], l[9], 1.00000000000000);
		dp_invAD_partials (j, l[11], l[10], 1.00000000000000);
		dp_mlCAD_partials (j, l[12], v[6], -1000.00000000000);
		dp_smCAD_partials (j, l[13], l[12], c[0]);
		dp_expAD_partials (j, l[14], l[13]);
		dp_smCAD_partials (j, l[15], l[14], 1.00000000000000);
		dp_invAD_partials (j, l[16], l[15], 1.00000000000000);
		dp_sumAD_partials (j, l[17], l[11], l[16]);
		dp_mulAD_partials (j, l[18], l[17], l[6]);
		dp_mlCAD_partials (j, l[19], l[18], -1.00000000000000);
		dp_sumAD_partials (j, l[20], l[4], l[19]);
		dp_smCAD_partials (j, l[21], l[0], par[7]);
		dp_mlCAD_partials (j, l[22], l[21], par[8]);
		dp_sumAD_partials (j, l[23], l[20], l[22]);
		dp_smCAD_partials (j, l[24], l[23], c[1]);
		dp_smCAD_partials (j, l[25], l[0], par[3]);
		dp_mlCAD_partials (j, l[26], l[25], par[4]);
		dp_mulAD_partials (j, l[27], v[1], l[26]);
		dp_mlCAD_partials (j, l[28], v[0], -150.000000000000);
		dp_smCAD_partials (j, l[29], l[28], -4.57500000000000);
		dp_expAD_partials (j, l[30], l[29]);
		dp_smCAD_partials (j, l[31], l[30], 1.00000000000000);
		dp_powAD_partials (j, l[32], l[31], -3.00000000000000);
		dp_mulAD_partials (j, l[33], l[32], l[27]);
		dp_sumAD_partials (j, l[34], l[24], l[33]);
		dp_mlCAD_partials (j, l[35], l[34], c[2]);
		dp_mlCAD_partials (j, l[36], v[0], 500.000000000000);
		dp_smCAD_partials (j, l[37], l[36], 16.2500000000000);
		dp_expAD_partials (j, l[38], l[37]);
		dp_smCAD_partials (j, l[39], l[38], 1.00000000000000);
		dp_invAD_partials (j, l[40], l[39], -1.00000000000000);
		dp_sumAD_partials (j, l[41], v[1], l[40]);
		dp_mlCAD_partials (j, l[42], l[41], -1.00000000000000);
		dp_mlCAD_partials (j, l[43], l[42], c[3]);
		dp_mlCAD_partials (j, l[44], v[0], -83.0000000000000);
		dp_smCAD_partials (j, l[45], l[44], c[4]);
		dp_smCAD_partials (j, l[46], l[45], -1.49400000000000);
		dp_expAD_partials (j, l[47], l[46]);
		dp_smCAD_partials (j, l[48], l[47], 1.00000000000000);
		dp_invAD_partials (j, l[49], l[48], -1.00000000000000);
		dp_sumAD_partials (j, l[50], v[2], l[49]);
		dp_mlCAD_partials (j, l[51], l[50], -1.00000000000000);
		dp_mlCAD_partials (j, l[52], l[51], c[5]);
		dp_mlCAD_partials (j, l[53], v[3], -1.00000000000000);
		dp_smCAD_partials (j, l[54], l[53], par[5]);
		dp_mlCAD_partials (j, l[55], l[54], par[6]);
		dp_mulAD_partials (j, l[56], v[5], v[5]);
		dp_mulAD_partials (j, l[57], l[56], l[55]);
		dp_smCAD_partials (j, l[58], l[53], par[1]);
		dp_mlCAD_partials (j, l[59], l[58], par[2]);
		dp_mlCAD_partials (j, l[60], v[0], -1000.00000000000);
		dp_smCAD_partials (j, l[61], l[60], c[0]);
		dp_expAD_partials (j, l[62], l[61]);
		dp_smCAD_partials (j, l[63], l[62], 1.00000000000000);
		dp_invAD_partials (j, l[64], l[63], 1.00000000000000);
		dp_sumAD_partials (j, l[65], l[64], l[16]);
		dp_mulAD_partials (j, l[66], l[65], l[59]);
		dp_mlCAD_partials (j, l[67], l[66], -1.00000000000000);
		dp_sumAD_partials (j, l[68], l[57], l[67]);
		dp_smCAD_partials (j, l[69], l[53], par[7]);
		dp_mlCAD_partials (j, l[70], l[69], par[8]);
		dp_sumAD_partials (j, l[71], l[68], l[70]);
		dp_smCAD_partials (j, l[72], l[71], c[1]);
		dp_smCAD_partials (j, l[73], l[53], par[3]);
		dp_mlCAD_partials (j, l[74], l[73], par[4]);
		dp_mulAD_partials (j, l[75], v[4], l[74]);
		dp_mlCAD_partials (j, l[76], v[3], -150.000000000000);
		dp_smCAD_partials (j, l[77], l[76], -4.57500000000000);
		dp_expAD_partials (j, l[78], l[77]);
		dp_smCAD_partials (j, l[79], l[78], 1.00000000000000);
		dp_powAD_partials (j, l[80], l[79], -3.00000000000000);
		dp_mulAD_partials (j, l[81], l[80], l[75]);
		dp_sumAD_partials (j, l[82], l[72], l[81]);
		dp_mlCAD_partials (j, l[83], l[82], c[2]);
		dp_mlCAD_partials (j, l[84], v[3], 500.000000000000);
		dp_smCAD_partials (j, l[85], l[84], 16.2500000000000);
		dp_expAD_partials (j, l[86], l[85]);
		dp_smCAD_partials (j, l[87], l[86], 1.00000000000000);
		dp_invAD_partials (j, l[88], l[87], -1.00000000000000);
		dp_sumAD_partials (j, l[89], v[4], l[88]);
		dp_mlCAD_partials (j, l[90], l[89], -1.00000000000000);
		dp_mlCAD_partials (j, l[91], l[90], c[3]);
		dp_mlCAD_partials (j, l[92], v[3], -83.0000000000000);
		dp_smCAD_partials (j, l[93], l[92], c[4]);
		dp_smCAD_partials (j, l[94], l[93], -1.49400000000000);
		dp_expAD_partials (j, l[95], l[94]);
		dp_smCAD_partials (j, l[96], l[95], 1.00000000000000);
		dp_invAD_partials (j, l[97], l[96], -1.00000000000000);
		dp_sumAD_partials (j, l[98], v[5], l[97]);
		dp_mlCAD_partials (j, l[99], l[98], -1.00000000000000);
		dp_mlCAD_partials (j, l[100], l[99], c[5]);
		dp_mlCAD_partials (j, l[101], v[6], -1.00000000000000);
		dp_smCAD_partials (j, l[102], l[101], par[5]);
		dp_mlCAD_partials (j, l[103], l[102], par[6]);
		dp_mulAD_partials (j, l[104], v[8], v[8]);
		dp_mulAD_partials (j, l[105], l[104], l[103]);
		dp_smCAD_partials (j, l[106], l[101], par[1]);
		dp_mlCAD_partials (j, l[107], l[106], par[2]);
		dp_sumAD_partials (j, l[108], l[64], l[11]);
		dp_mulAD_partials (j, l[109], l[108], l[107]);
		dp_mlCAD_partials (j, l[110], l[109], -1.00000000000000);
		dp_sumAD_partials (j, l[111], l[105], l[110]);
		dp_smCAD_partials (j, l[112], l[101], par[7]);
		dp_mlCAD_partials (j, l[113], l[112], par[8]);
		dp_sumAD_partials (j, l[114], l[111], l[113]);
		dp_smCAD_partials (j, l[115], l[114], c[1]);
		dp_smCAD_partials (j, l[116], l[101], par[3]);
		dp_mlCAD_partials (j, l[117], l[116], par[4]);
		dp_mulAD_partials (j, l[118], v[7], l[117]);
		dp_mlCAD_partials (j, l[119], v[6], -150.000000000000);
		dp_smCAD_partials (j, l[120], l[119], -4.57500000000000);
		dp_expAD_partials (j, l[121], l[120]);
		dp_smCAD_partials (j, l[122], l[121], 1.00000000000000);
		dp_powAD_partials (j, l[123], l[122], -3.00000000000000);
		dp_mulAD_partials (j, l[124], l[123], l[118]);
		dp_sumAD_partials (j, l[125], l[115], l[124]);
		dp_mlCAD_partials (j, l[126], l[125], c[2]);
		dp_mlCAD_partials (j, l[127], v[6], 500.000000000000);
		dp_smCAD_partials (j, l[128], l[127], 16.2500000000000);
		dp_expAD_partials (j, l[129], l[128]);
		dp_smCAD_partials (j, l[130], l[129], 1.00000000000000);
		dp_invAD_partials (j, l[131], l[130], -1.00000000000000);
		dp_sumAD_partials (j, l[132], v[7], l[131]);
		dp_mlCAD_partials (j, l[133], l[132], -1.00000000000000);
		dp_mlCAD_partials (j, l[134], l[133], c[3]);
		dp_mlCAD_partials (j, l[135], v[6], -83.0000000000000);
		dp_smCAD_partials (j, l[136], l[135], c[4]);
		dp_smCAD_partials (j, l[137], l[136], -1.49400000000000);
		dp_expAD_partials (j, l[138], l[137]);
		dp_smCAD_partials (j, l[139], l[138], 1.00000000000000);
		dp_invAD_partials (j, l[140], l[139], -1.00000000000000);
		dp_sumAD_partials (j, l[141], v[8], l[140]);
		dp_mlCAD_partials (j, l[142], l[141], -1.00000000000000);
		dp_mlCAD_partials (j, l[143], l[142], c[5]);


		for (i=0; i<=NDER; i++) {
			v[0][i][j+1] = l[35][i][j] / (j+1.0);
			v[1][i][j+1] = l[43][i][j] / (j+1.0);
			v[2][i][j+1] = l[52][i][j] / (j+1.0);
			v[3][i][j+1] = l[83][i][j] / (j+1.0);
			v[4][i][j+1] = l[91][i][j] / (j+1.0);
			v[5][i][j+1] = l[100][i][j] / (j+1.0);
			v[6][i][j+1] = l[126][i][j] / (j+1.0);
			v[7][i][j+1] = l[134][i][j] / (j+1.0);
			v[8][i][j+1] = l[143][i][j] / (j+1.0);
		}
	}



	for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) for (j=0; j<=ORDER; j++)
		series[k+i*NVAR][j] = v[k][i][j];

}

