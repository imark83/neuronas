
/***********************************************************************
FUNCTION HEADERS FOR PROCESSING A SINGLE NEURON
**********************************************************************/
// taylor method for a single neuron. event for 1st value at EVENT VALUE
real_t taylor1 (real_t x[NVAR1], real_t tf, int event, real_t VSHIFT);
// computation of taylor series for a single neuron
void fun1 (real_t x[NVAR1], real_t series[NVAR1][ORDER+1], real_t VSHIFT);
// estimates stepsize
real_t getStep1 (real_t series[NVAR1][ORDER+1]);
// horner evaluation
void horner1 (real_t x[NVAR1], real_t series[NVAR1][ORDER+1], real_t stepsize);




/***********************************************************************
FUNCTION HEADERS FOR PROCESSING A 3-CELL CPG
**********************************************************************/
// taylor method for a single neuron. event for 1st value at EVENT VALUE
void taylor (real_t x[NVAR], real_t tf, real_t delay[3*CUTNUMBER], real_t VSHIFT, int cutnumber);
// computation of taylor series for a single neuron
void fun (real_t x[NVAR], real_t series[NVAR][ORDER+1], real_t VSHIFT);
// estimates stepsize
real_t getStep (real_t series[NVAR][ORDER+1]);
// horner evaluation
void horner (real_t x[NVAR], real_t series[NVAR][ORDER+1], real_t stepsize);


