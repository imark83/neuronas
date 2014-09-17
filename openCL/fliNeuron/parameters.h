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


// INTEGRATION PARAMETERS
#define M		(512)			// HORIZONTAL GRIDSIZE
#define N		(512)			// VERTICAL GRIDSIZE
#define TF		(6000.0)		// FINAL INTEGRATION TIME
#define NVAR		(9)			// NUMBER OF VARIABLES
#define NCOL		(18)			// NUMBER OF VARIABLES 
#define NVAR2		(3)			// NUMBER OF VARIABLES FOR SINGLE NEURON
#define NDER		(1)			// NUMBER OF VARIATIONALS (1 FOR FLI)
#define TOL 		(1.0e-8)		// TOLERANCE FOR INTEGRATION
#define ORDER		(15)			// ORDER     OF TAYLOR SERIES
#define CUTNUMBER	(3)			// NUMBER OF CUTS FOR POINCARE
#define EVENTVALUE	(-0.04)		// POINCARE SECTION




// NEURON PARAMETERS
#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(-0.0005)
#define ENA		(0.045)
#define GNA		(160.0)
#define EK		(-0.07)
#define GK2		(30.0)
#define EL		(-0.046)
#define GL		(8.0)
#define C		(0.5)
#define TNA		(0.0405)
#define TK2		(0.9)
#define IAPP		(0.006)
#define VSHIFT		(-0.01895)		// FIGURE 5


// PLOT EDGES LIMIT PARAMETERS
#define CENTERX		(0.5)
#define CENTERY		(0.5)
#define RADIUS		(0.49)

#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y







//#define TF	(64.2652399541350)	// FINAL TIME

