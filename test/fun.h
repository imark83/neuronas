

void fun2 (real_t x[NVAR2], real_t series[NVAR2][ORDER+1], real_t VSHIFT) {

	int i, j;
	
	double par[14] = {THSYN,ESYN,GSYN,ENA,GNA,EK,GK2,EL,GL,C,TNA,TK2,VSHIFT,IAPP};

	for (i=0; i<NVAR2; i++) series[i][0] = x[i];



	double l[37][ORDER+1];
	double c[5];
	c[0] = (-1.00000000000000) * par[13];
	c[1] = (1.00000000000000) / par[9];
	c[2] = (1.00000000000000) / par[10];
	c[3] = (-83.0000000000000) * par[12];
	c[4] = (1.00000000000000) / par[11];
	for (i=0; i<ORDER; i++) {
		dp_mlCAD (i, l[0], series[0], -1.00000000000000);
		dp_smCAD (i, l[1], l[0], par[5]);
		dp_mlCAD (i, l[2], l[1], par[6]);
		dp_mulAD (i, l[3], series[2], series[2]);
		dp_mulAD (i, l[4], l[3], l[2]);
		dp_smCAD (i, l[5], l[0], par[7]);
		dp_mlCAD (i, l[6], l[5], par[8]);
		dp_sumAD (i, l[7], l[4], l[6]);
		dp_smCAD (i, l[8], l[7], c[0]);
		dp_smCAD (i, l[9], l[0], par[3]);
		dp_mlCAD (i, l[10], l[9], par[4]);
		dp_mulAD (i, l[11], series[1], l[10]);
		dp_mlCAD (i, l[12], series[0], -150.000000000000);
		dp_smCAD (i, l[13], l[12], -4.57500000000000);
		dp_expAD (i, l[14], l[13]);
		dp_smCAD (i, l[15], l[14], 1.00000000000000);
		dp_powAD (i, l[16], l[15], -3.00000000000000);
		dp_mulAD (i, l[17], l[16], l[11]);
		dp_sumAD (i, l[18], l[8], l[17]);
		dp_mlCAD (i, l[19], l[18], c[1]);
		dp_mlCAD (i, l[20], series[0], 500.000000000000);
		dp_smCAD (i, l[21], l[20], 16.2500000000000);
		dp_expAD (i, l[22], l[21]);
		dp_smCAD (i, l[23], l[22], 1.00000000000000);
		dp_invAD (i, l[24], l[23], -1.00000000000000);
		dp_sumAD (i, l[25], series[1], l[24]);
		dp_mlCAD (i, l[26], l[25], -1.00000000000000);
		dp_mlCAD (i, l[27], l[26], c[2]);
		dp_mlCAD (i, l[28], series[0], -83.0000000000000);
		dp_smCAD (i, l[29], l[28], c[3]);
		dp_smCAD (i, l[30], l[29], -1.49400000000000);
		dp_expAD (i, l[31], l[30]);
		dp_smCAD (i, l[32], l[31], 1.00000000000000);
		dp_invAD (i, l[33], l[32], -1.00000000000000);
		dp_sumAD (i, l[34], series[2], l[33]);
		dp_mlCAD (i, l[35], l[34], -1.00000000000000);
		dp_mlCAD (i, l[36], l[35], c[4]);


		series[0][i+1] = l[19][i] / (i+1.0);
		series[1][i+1] = l[27][i] / (i+1.0);
		series[2][i+1] = l[36][i] / (i+1.0);
	}



}
