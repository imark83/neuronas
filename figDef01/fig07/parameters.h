#define MIN(a,b) ((a)<(b))? (a) : (b)
#define MAX(a,b) ((a)>(b))? (a) : (b)


#define CPU
#define FILENAME	"T.txt"
#define DOUBLE

#ifdef FLOAT
#define real_t float
#endif

#ifdef DOUBLE
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define real_t double
#endif

#define M		1		// HORIZONTAL GRIDSIZE
#define N		1		// VERTICAL GRIDSIZE
#define NVAR2		3		// NUMBER OF VARIABLES FOR SINGLE NEURON
#define NVAR		9		// NUMBER OF VARIABLES
#define CUTNUMBER	1000		// NUMBER OF CUTS FOR POINC. OF EACH NEURON!
#define TOL 		(1.0e-8)	// TOLERANCE FOR INTEGRATION
#define ORDER		17		// ORDER     OF TAYLOR SERIES

#define EVENTVALUE	(-0.04)		// POINCARE SECTION


#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(-0.0005*0.8)
#define ENA		(0.045)
#define GNA		(160.0)
#define EK		(-0.07)
#define GK2		(30.0)
#define EL		(-0.046)
#define GL		(8.0)
#define C		(0.5)
#define TNA		(0.0405)
#define TK2		(0.9)


#define CENTERX		(0.5)
#define CENTERY		(0.5)
#define RADIUS		(0.45)

#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y
//#define VSHIFT		(-0.01895)	// FIGURE 5
//#define VSHIFT		(-0.0225)	// FIGURE 7
//#define VSHIFT		(-0.021)	// FIGURE 8
#define IAPP		(0.006)


