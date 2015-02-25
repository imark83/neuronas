void fS (real_t *rop, real_t *x) {

	real_t local_rop[NVAR_S];

	real_t m_NaInf = 1.0 / (1.0 + exp (-150.0*(x[0] + 0.0305)));
	real_t h_NaInf = 1.0 / (1.0 + exp (500.0*(x[0] + 0.0325)));
	real_t m_K2Inf = 1.0 / (1.0 + exp (-83.0*(x[0] + 0.018 + VSHIFT)));

	real_t I_Na = GNA * (x[0] - ENA) * x[1] * m_NaInf * m_NaInf * m_NaInf;
	real_t I_K2 = GK2 * (x[0] - EK) * x[2] * x[2];
	real_t I_L = GL * (x[0] - EL);

	local_rop[0] = (-I_Na - I_K2 - I_L - IAPP) / C;
	local_rop[1] = (h_NaInf - x[1]) / TNA;
	local_rop[2] = (m_K2Inf - x[2]) / TK2;

	
	rop[0] = local_rop[0];
	rop[1] = local_rop[1];
	rop[2] = local_rop[2];

}
