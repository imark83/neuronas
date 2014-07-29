__constant int RANGE_SET[] = {0, 1, 3, 5, 7, 9};
__constant int VI_SET[]    = {0, 0, 1, 0, 2, 0, 3, 0, 4};
__constant int IV_SET[]    = {0, 1, 0, 2, 0, 3, 0, 4, 0};
__constant int COMB_SET[]  = {1, 1, 1, 1, 1, 1, 1, 1, 1};

__constant int RANGE_STAR[] = {0, 1, 2, 3, 4, 5};
__constant int VI_STAR[]    = {0, 0, 0, 0, 0};
__constant int IV_STAR[]    = {0, 1, 2, 3, 4};
__constant int COMB_STAR[]  = {1, 1, 1, 1, 1};

__constant real_t par[14] = {THSYN,ESYN,GSYN,ENA,GNA,EK,GK2,EL,GL,C,TNA,TK2,VSHIFT,IAPP};

void fun (real_t t, real_t *x, real_t series[NCOL][ORDER+1]) {

	int k, i, j;
	
	real_t v[NVAR][NDER+1][ORDER+1];		//para las variables
		for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) 
			v[k][i][0] = x[k+NVAR*i];

	real_t l[141][NDER+1][ORDER+1];
	real_t c[6];


	c[0] = (1000.00000000000) * par[0];
	c[1] = (-1.00000000000000) * par[13];
	c[2] = (1.00000000000000) / par[9];
	c[3] = (1.00000000000000) / par[10];
	c[4] = (-83.0000000000000) * par[12];
	c[5] = (1.00000000000000) / par[11];
	for (j=0; j<ORDER; j++) {
		dp_mlCAD (j, l[0], v[0], -1.00000000000000);
		dp_smCAD (j, l[1], l[0], par[5]);
		dp_mlCAD (j, l[2], l[1], par[6]);
		dp_mulAD (j, l[3], v[2], v[2]);
		dp_mulAD (j, l[4], l[3], l[2]);
		dp_smCAD (j, l[5], l[0], par[1]);
		dp_mlCAD (j, l[6], l[5], par[2]);
		dp_mlCAD (j, l[7], v[3], -1000.00000000000);
		dp_smCAD (j, l[8], l[7], c[0]);
		dp_expAD (j, l[9], l[8]);
		dp_smCAD (j, l[10], l[9], 1.00000000000000);
		dp_invAD (j, l[11], l[10], 1.00000000000000);
		dp_mlCAD (j, l[12], v[6], -1000.00000000000);
		dp_smCAD (j, l[13], l[12], c[0]);
		dp_expAD (j, l[14], l[13]);
		dp_smCAD (j, l[15], l[14], 1.00000000000000);
		dp_invAD (j, l[16], l[15], 1.00000000000000);
		dp_sumAD (j, l[17], l[11], l[16]);
		dp_mulAD (j, l[18], l[17], l[6]);
		dp_sumAD (j, l[19], l[4], l[18]);
		dp_smCAD (j, l[20], l[0], par[7]);
		dp_mlCAD (j, l[21], l[20], par[8]);
		dp_sumAD (j, l[22], l[19], l[21]);
		dp_smCAD (j, l[23], l[22], c[1]);
		dp_smCAD (j, l[24], l[0], par[3]);
		dp_mlCAD (j, l[25], l[24], par[4]);
		dp_mulAD (j, l[26], v[1], l[25]);
		dp_mlCAD (j, l[27], v[0], -150.000000000000);
		dp_smCAD (j, l[28], l[27], -4.57500000000000);
		dp_expAD (j, l[29], l[28]);
		dp_smCAD (j, l[30], l[29], 1.00000000000000);
		dp_powAD (j, l[31], l[30], -3.00000000000000);
		dp_mulAD (j, l[32], l[31], l[26]);
		dp_sumAD (j, l[33], l[23], l[32]);
		dp_mlCAD (j, l[34], l[33], c[2]);
		dp_mlCAD (j, l[35], v[0], 500.000000000000);
		dp_smCAD (j, l[36], l[35], 16.2500000000000);
		dp_expAD (j, l[37], l[36]);
		dp_smCAD (j, l[38], l[37], 1.00000000000000);
		dp_invAD (j, l[39], l[38], -1.00000000000000);
		dp_sumAD (j, l[40], v[1], l[39]);
		dp_mlCAD (j, l[41], l[40], -1.00000000000000);
		dp_mlCAD (j, l[42], l[41], c[3]);
		dp_mlCAD (j, l[43], v[0], -83.0000000000000);
		dp_smCAD (j, l[44], l[43], c[4]);
		dp_smCAD (j, l[45], l[44], -1.49400000000000);
		dp_expAD (j, l[46], l[45]);
		dp_smCAD (j, l[47], l[46], 1.00000000000000);
		dp_invAD (j, l[48], l[47], -1.00000000000000);
		dp_sumAD (j, l[49], v[2], l[48]);
		dp_mlCAD (j, l[50], l[49], -1.00000000000000);
		dp_mlCAD (j, l[51], l[50], c[5]);
		dp_mlCAD (j, l[52], v[3], -1.00000000000000);
		dp_smCAD (j, l[53], l[52], par[5]);
		dp_mlCAD (j, l[54], l[53], par[6]);
		dp_mulAD (j, l[55], v[5], v[5]);
		dp_mulAD (j, l[56], l[55], l[54]);
		dp_smCAD (j, l[57], l[52], par[1]);
		dp_mlCAD (j, l[58], l[57], par[2]);
		dp_mlCAD (j, l[59], v[0], -1000.00000000000);
		dp_smCAD (j, l[60], l[59], c[0]);
		dp_expAD (j, l[61], l[60]);
		dp_smCAD (j, l[62], l[61], 1.00000000000000);
		dp_invAD (j, l[63], l[62], 1.00000000000000);
		dp_sumAD (j, l[64], l[63], l[16]);
		dp_mulAD (j, l[65], l[64], l[58]);
		dp_sumAD (j, l[66], l[56], l[65]);
		dp_smCAD (j, l[67], l[52], par[7]);
		dp_mlCAD (j, l[68], l[67], par[8]);
		dp_sumAD (j, l[69], l[66], l[68]);
		dp_smCAD (j, l[70], l[69], c[1]);
		dp_smCAD (j, l[71], l[52], par[3]);
		dp_mlCAD (j, l[72], l[71], par[4]);
		dp_mulAD (j, l[73], v[4], l[72]);
		dp_mlCAD (j, l[74], v[3], -150.000000000000);
		dp_smCAD (j, l[75], l[74], -4.57500000000000);
		dp_expAD (j, l[76], l[75]);
		dp_smCAD (j, l[77], l[76], 1.00000000000000);
		dp_powAD (j, l[78], l[77], -3.00000000000000);
		dp_mulAD (j, l[79], l[78], l[73]);
		dp_sumAD (j, l[80], l[70], l[79]);
		dp_mlCAD (j, l[81], l[80], c[2]);
		dp_mlCAD (j, l[82], v[3], 500.000000000000);
		dp_smCAD (j, l[83], l[82], 16.2500000000000);
		dp_expAD (j, l[84], l[83]);
		dp_smCAD (j, l[85], l[84], 1.00000000000000);
		dp_invAD (j, l[86], l[85], -1.00000000000000);
		dp_sumAD (j, l[87], v[4], l[86]);
		dp_mlCAD (j, l[88], l[87], -1.00000000000000);
		dp_mlCAD (j, l[89], l[88], c[3]);
		dp_mlCAD (j, l[90], v[3], -83.0000000000000);
		dp_smCAD (j, l[91], l[90], c[4]);
		dp_smCAD (j, l[92], l[91], -1.49400000000000);
		dp_expAD (j, l[93], l[92]);
		dp_smCAD (j, l[94], l[93], 1.00000000000000);
		dp_invAD (j, l[95], l[94], -1.00000000000000);
		dp_sumAD (j, l[96], v[5], l[95]);
		dp_mlCAD (j, l[97], l[96], -1.00000000000000);
		dp_mlCAD (j, l[98], l[97], c[5]);
		dp_mlCAD (j, l[99], v[6], -1.00000000000000);
		dp_smCAD (j, l[100], l[99], par[5]);
		dp_mlCAD (j, l[101], l[100], par[6]);
		dp_mulAD (j, l[102], v[8], v[8]);
		dp_mulAD (j, l[103], l[102], l[101]);
		dp_smCAD (j, l[104], l[99], par[1]);
		dp_mlCAD (j, l[105], l[104], par[2]);
		dp_sumAD (j, l[106], l[63], l[11]);
		dp_mulAD (j, l[107], l[106], l[105]);
		dp_sumAD (j, l[108], l[103], l[107]);
		dp_smCAD (j, l[109], l[99], par[7]);
		dp_mlCAD (j, l[110], l[109], par[8]);
		dp_sumAD (j, l[111], l[108], l[110]);
		dp_smCAD (j, l[112], l[111], c[1]);
		dp_smCAD (j, l[113], l[99], par[3]);
		dp_mlCAD (j, l[114], l[113], par[4]);
		dp_mulAD (j, l[115], v[7], l[114]);
		dp_mlCAD (j, l[116], v[6], -150.000000000000);
		dp_smCAD (j, l[117], l[116], -4.57500000000000);
		dp_expAD (j, l[118], l[117]);
		dp_smCAD (j, l[119], l[118], 1.00000000000000);
		dp_powAD (j, l[120], l[119], -3.00000000000000);
		dp_mulAD (j, l[121], l[120], l[115]);
		dp_sumAD (j, l[122], l[112], l[121]);
		dp_mlCAD (j, l[123], l[122], c[2]);
		dp_mlCAD (j, l[124], v[6], 500.000000000000);
		dp_smCAD (j, l[125], l[124], 16.2500000000000);
		dp_expAD (j, l[126], l[125]);
		dp_smCAD (j, l[127], l[126], 1.00000000000000);
		dp_invAD (j, l[128], l[127], -1.00000000000000);
		dp_sumAD (j, l[129], v[7], l[128]);
		dp_mlCAD (j, l[130], l[129], -1.00000000000000);
		dp_mlCAD (j, l[131], l[130], c[3]);
		dp_mlCAD (j, l[132], v[6], -83.0000000000000);
		dp_smCAD (j, l[133], l[132], c[4]);
		dp_smCAD (j, l[134], l[133], -1.49400000000000);
		dp_expAD (j, l[135], l[134]);
		dp_smCAD (j, l[136], l[135], 1.00000000000000);
		dp_invAD (j, l[137], l[136], -1.00000000000000);
		dp_sumAD (j, l[138], v[8], l[137]);
		dp_mlCAD (j, l[139], l[138], -1.00000000000000);
		dp_mlCAD (j, l[140], l[139], c[5]);


		for (i=0; i<=NDER; i++) {
			v[0][i][j+1] = l[34][i][j] / (j+1.0);
			v[1][i][j+1] = l[42][i][j] / (j+1.0);
			v[2][i][j+1] = l[51][i][j] / (j+1.0);
			v[3][i][j+1] = l[81][i][j] / (j+1.0);
			v[4][i][j+1] = l[89][i][j] / (j+1.0);
			v[5][i][j+1] = l[98][i][j] / (j+1.0);
			v[6][i][j+1] = l[123][i][j] / (j+1.0);
			v[7][i][j+1] = l[131][i][j] / (j+1.0);
			v[8][i][j+1] = l[140][i][j] / (j+1.0);
		}

	}

	for (k=0; k<NVAR; k++) for (i=0; i<=NDER; i++) for (j=0; j<=ORDER; j++)
		series[k+i*NVAR][j] = v[k][i][j];

}






