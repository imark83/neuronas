#define MIN(a,b) ((a)<(b))? (a) : (b)
#define MAX(a,b) ((a)>(b))? (a) : (b)


#define CPU
#define DOUBLE

#ifdef FLOAT
#define real_t float
#endif

#ifdef DOUBLE
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define real_t double
#endif



#define M		(1)		// HORIZONTAL GRIDSIZE
#define N		(1)		// VERTICAL GRIDSIZE
#define yMIN		(-0.5)		// MINIMUM VALUE FOR y
#define yMAX		(0.7)		// MAXIMUM VALUE FOR y
#define YMIN		(-0.5)		// MINIMUM VALUE FOR Y
#define YMAX		(0.5)		// MAXIMUM VALUE FOR Y
#define H		(0.125)		// ENERGY
#define TF		(600.0)		// FINAL INTEGRATION TIME



#define TOL 		(1.0e-8)	// TOLERANCE FOR INTEGRATION
#define ORDER		(15)		// ORDER OF TAYLOR SERIES


#define NVAR	(9)			// NUMBER OF VARIABLES
#define NCOL	(18)			// NUMBER OF VARIABLES INCLUDING VARIATIONALS
#define NDER	(1)			// NUMBER OF VARIATIONALS (1 FOR FLI)


#define EVENTVALUE	(-0.04)		// POINCARE SECTION


#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(0.0003)
#define ENA		(0.045)
#define GNA		(160.0)
#define EK		(-0.07)
#define GK2		(30.0)
#define EL		(-0.046)
#define GL		(8.0)
#define C		(0.5)
#define TNA		(0.0405)
#define TK2		(0.9)
#define	IAPP		(0.006)
#define VSHIFT		(-0.018690)



