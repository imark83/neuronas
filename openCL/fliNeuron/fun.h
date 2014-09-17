void fun (real_t *x, real_t series[NVAR][ORDER+1]) {

	int i, j;
	
	for (i=0; i<NVAR; i++) series[i][0] = x[i];


	double par[14] = {THSYN,ESYN,GSYN,ENA,GNA,EK,GK2,EL,GL,C,TNA,TK2,VSHIFT,IAPP};

	double l[144][ORDER];
	double c[6];
	c[0] = (1000.00000000000) * par[0];
	c[1] = (-1.00000000000000) * par[13];
	c[2] = (1.00000000000000) / par[9];
	c[3] = (1.00000000000000) / par[10];
	c[4] = (-83.0000000000000) * par[12];
	c[5] = (1.00000000000000) / par[11];
	for (i=0; i<ORDER; i++) {
		dp_mlCAD (i, l[0], series[0], -1.00000000000000);
		dp_smCAD (i, l[1], l[0], par[5]);
		dp_mlCAD (i, l[2], l[1], par[6]);
		dp_mulAD (i, l[3], series[2], series[2]);
		dp_mulAD (i, l[4], l[3], l[2]);
		dp_smCAD (i, l[5], l[0], par[1]);
		dp_mlCAD (i, l[6], l[5], par[2]);
		dp_mlCAD (i, l[7], series[3], -1000.00000000000);
		dp_smCAD (i, l[8], l[7], c[0]);
		dp_expAD (i, l[9], l[8]);
		dp_smCAD (i, l[10], l[9], 1.00000000000000);
		dp_invAD (i, l[11], l[10], 1.00000000000000);
		dp_mlCAD (i, l[12], series[6], -1000.00000000000);
		dp_smCAD (i, l[13], l[12], c[0]);
		dp_expAD (i, l[14], l[13]);
		dp_smCAD (i, l[15], l[14], 1.00000000000000);
		dp_invAD (i, l[16], l[15], 1.00000000000000);
		dp_sumAD (i, l[17], l[11], l[16]);
		dp_mulAD (i, l[18], l[17], l[6]);
		dp_mlCAD (i, l[19], l[18], -1.00000000000000);
		dp_sumAD (i, l[20], l[4], l[19]);
		dp_smCAD (i, l[21], l[0], par[7]);
		dp_mlCAD (i, l[22], l[21], par[8]);
		dp_sumAD (i, l[23], l[20], l[22]);
		dp_smCAD (i, l[24], l[23], c[1]);
		dp_smCAD (i, l[25], l[0], par[3]);
		dp_mlCAD (i, l[26], l[25], par[4]);
		dp_mulAD (i, l[27], series[1], l[26]);
		dp_mlCAD (i, l[28], series[0], -150.000000000000);
		dp_smCAD (i, l[29], l[28], -4.57500000000000);
		dp_expAD (i, l[30], l[29]);
		dp_smCAD (i, l[31], l[30], 1.00000000000000);
		dp_powAD (i, l[32], l[31], -3.00000000000000);
		dp_mulAD (i, l[33], l[32], l[27]);
		dp_sumAD (i, l[34], l[24], l[33]);
		dp_mlCAD (i, l[35], l[34], c[2]);
		dp_mlCAD (i, l[36], series[0], 500.000000000000);
		dp_smCAD (i, l[37], l[36], 16.2500000000000);
		dp_expAD (i, l[38], l[37]);
		dp_smCAD (i, l[39], l[38], 1.00000000000000);
		dp_invAD (i, l[40], l[39], -1.00000000000000);
		dp_sumAD (i, l[41], series[1], l[40]);
		dp_mlCAD (i, l[42], l[41], -1.00000000000000);
		dp_mlCAD (i, l[43], l[42], c[3]);
		dp_mlCAD (i, l[44], series[0], -83.0000000000000);
		dp_smCAD (i, l[45], l[44], c[4]);
		dp_smCAD (i, l[46], l[45], -1.49400000000000);
		dp_expAD (i, l[47], l[46]);
		dp_smCAD (i, l[48], l[47], 1.00000000000000);
		dp_invAD (i, l[49], l[48], -1.00000000000000);
		dp_sumAD (i, l[50], series[2], l[49]);
		dp_mlCAD (i, l[51], l[50], -1.00000000000000);
		dp_mlCAD (i, l[52], l[51], c[5]);
		dp_mlCAD (i, l[53], series[3], -1.00000000000000);
		dp_smCAD (i, l[54], l[53], par[5]);
		dp_mlCAD (i, l[55], l[54], par[6]);
		dp_mulAD (i, l[56], series[5], series[5]);
		dp_mulAD (i, l[57], l[56], l[55]);
		dp_smCAD (i, l[58], l[53], par[1]);
		dp_mlCAD (i, l[59], l[58], par[2]);
		dp_mlCAD (i, l[60], series[0], -1000.00000000000);
		dp_smCAD (i, l[61], l[60], c[0]);
		dp_expAD (i, l[62], l[61]);
		dp_smCAD (i, l[63], l[62], 1.00000000000000);
		dp_invAD (i, l[64], l[63], 1.00000000000000);
		dp_sumAD (i, l[65], l[64], l[16]);
		dp_mulAD (i, l[66], l[65], l[59]);
		dp_mlCAD (i, l[67], l[66], -1.00000000000000);
		dp_sumAD (i, l[68], l[57], l[67]);
		dp_smCAD (i, l[69], l[53], par[7]);
		dp_mlCAD (i, l[70], l[69], par[8]);
		dp_sumAD (i, l[71], l[68], l[70]);
		dp_smCAD (i, l[72], l[71], c[1]);
		dp_smCAD (i, l[73], l[53], par[3]);
		dp_mlCAD (i, l[74], l[73], par[4]);
		dp_mulAD (i, l[75], series[4], l[74]);
		dp_mlCAD (i, l[76], series[3], -150.000000000000);
		dp_smCAD (i, l[77], l[76], -4.57500000000000);
		dp_expAD (i, l[78], l[77]);
		dp_smCAD (i, l[79], l[78], 1.00000000000000);
		dp_powAD (i, l[80], l[79], -3.00000000000000);
		dp_mulAD (i, l[81], l[80], l[75]);
		dp_sumAD (i, l[82], l[72], l[81]);
		dp_mlCAD (i, l[83], l[82], c[2]);
		dp_mlCAD (i, l[84], series[3], 500.000000000000);
		dp_smCAD (i, l[85], l[84], 16.2500000000000);
		dp_expAD (i, l[86], l[85]);
		dp_smCAD (i, l[87], l[86], 1.00000000000000);
		dp_invAD (i, l[88], l[87], -1.00000000000000);
		dp_sumAD (i, l[89], series[4], l[88]);
		dp_mlCAD (i, l[90], l[89], -1.00000000000000);
		dp_mlCAD (i, l[91], l[90], c[3]);
		dp_mlCAD (i, l[92], series[3], -83.0000000000000);
		dp_smCAD (i, l[93], l[92], c[4]);
		dp_smCAD (i, l[94], l[93], -1.49400000000000);
		dp_expAD (i, l[95], l[94]);
		dp_smCAD (i, l[96], l[95], 1.00000000000000);
		dp_invAD (i, l[97], l[96], -1.00000000000000);
		dp_sumAD (i, l[98], series[5], l[97]);
		dp_mlCAD (i, l[99], l[98], -1.00000000000000);
		dp_mlCAD (i, l[100], l[99], c[5]);
		dp_mlCAD (i, l[101], series[6], -1.00000000000000);
		dp_smCAD (i, l[102], l[101], par[5]);
		dp_mlCAD (i, l[103], l[102], par[6]);
		dp_mulAD (i, l[104], series[8], series[8]);
		dp_mulAD (i, l[105], l[104], l[103]);
		dp_smCAD (i, l[106], l[101], par[1]);
		dp_mlCAD (i, l[107], l[106], par[2]);
		dp_sumAD (i, l[108], l[64], l[11]);
		dp_mulAD (i, l[109], l[108], l[107]);
		dp_mlCAD (i, l[110], l[109], -1.00000000000000);
		dp_sumAD (i, l[111], l[105], l[110]);
		dp_smCAD (i, l[112], l[101], par[7]);
		dp_mlCAD (i, l[113], l[112], par[8]);
		dp_sumAD (i, l[114], l[111], l[113]);
		dp_smCAD (i, l[115], l[114], c[1]);
		dp_smCAD (i, l[116], l[101], par[3]);
		dp_mlCAD (i, l[117], l[116], par[4]);
		dp_mulAD (i, l[118], series[7], l[117]);
		dp_mlCAD (i, l[119], series[6], -150.000000000000);
		dp_smCAD (i, l[120], l[119], -4.57500000000000);
		dp_expAD (i, l[121], l[120]);
		dp_smCAD (i, l[122], l[121], 1.00000000000000);
		dp_powAD (i, l[123], l[122], -3.00000000000000);
		dp_mulAD (i, l[124], l[123], l[118]);
		dp_sumAD (i, l[125], l[115], l[124]);
		dp_mlCAD (i, l[126], l[125], c[2]);
		dp_mlCAD (i, l[127], series[6], 500.000000000000);
		dp_smCAD (i, l[128], l[127], 16.2500000000000);
		dp_expAD (i, l[129], l[128]);
		dp_smCAD (i, l[130], l[129], 1.00000000000000);
		dp_invAD (i, l[131], l[130], -1.00000000000000);
		dp_sumAD (i, l[132], series[7], l[131]);
		dp_mlCAD (i, l[133], l[132], -1.00000000000000);
		dp_mlCAD (i, l[134], l[133], c[3]);
		dp_mlCAD (i, l[135], series[6], -83.0000000000000);
		dp_smCAD (i, l[136], l[135], c[4]);
		dp_smCAD (i, l[137], l[136], -1.49400000000000);
		dp_expAD (i, l[138], l[137]);
		dp_smCAD (i, l[139], l[138], 1.00000000000000);
		dp_invAD (i, l[140], l[139], -1.00000000000000);
		dp_sumAD (i, l[141], series[8], l[140]);
		dp_mlCAD (i, l[142], l[141], -1.00000000000000);
		dp_mlCAD (i, l[143], l[142], c[5]);


		series[0][i+1] = l[35][i] / (i+1.0);
		series[1][i+1] = l[43][i] / (i+1.0);
		series[2][i+1] = l[52][i] / (i+1.0);
		series[3][i+1] = l[83][i] / (i+1.0);
		series[4][i+1] = l[91][i] / (i+1.0);
		series[5][i+1] = l[100][i] / (i+1.0);
		series[6][i+1] = l[126][i] / (i+1.0);
		series[7][i+1] = l[134][i] / (i+1.0);
		series[8][i+1] = l[143][i] / (i+1.0);
	}


}

void fun2 (real_t *x, real_t series[NVAR2][ORDER+1]) {

	int i, j;
	
	double par[14] = {THSYN,ESYN,GSYN,ENA,GNA,EK,GK2,EL,GL,C,TNA,TK2,VSHIFT,IAPP};

	for (i=0; i<NVAR2; i++) series[i][0] = x[i];



	double l[37][ORDER];
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
