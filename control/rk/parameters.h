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


// GEOMETRY VALUES
#define M		(128)		// HORIZONTAL GRIDSIZE
#define N		(128)		// VERTICAL GRIDSIZE
#define CUTNUMBER	(3)		// NUMBER OF CUTS FOR POINC. OF EACH NEURON!
#define CENTERX		(0.5)
#define CENTERY		(0.5)
#define RADIUS		(0.45)
#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y

// NEURON AND NETWORK PARAMETERS
#define EVENTVALUE	(-0.04)		// POINCARE SECTION
#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(0.0007)	// GSYN INCREASED!
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
#define VSHIFT		(-0.021)	// FIGURE 7
//#define VSHIFT 		(-0.020650)



// INTEGRATOR PARAMETERS
#define NVAR_S		(3)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NVAR_N		(9)		// NUMBER OF VARIABLES OF THE NETWORK
#define TOL		(1.0e-8)	// TOLERANCE FOR THE RUNGE-KUTTA INTEGRATION
#define INITIAL_STEP	(1.0e-7)	// INITIAL STEPSIZE



