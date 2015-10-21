#define MIN(a,b) ((a)<(b))? (a) : (b)
#define MAX(a,b) ((a)>(b))? (a) : (b)

#define CPU

#define FILENAME	"T.txt"
#define FLOAT

#ifdef FLOAT
#define real_t float
#endif

#ifdef DOUBLE
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define real_t double
#endif


// GEOMETRY VALUES
#define M			(40)		// HORIZONTAL GRIDSIZE
#define N			(40)		// VERTICAL GRIDSIZE
#define CUTNUMBER	(40)		// NUMBER OF CUTS FOR POINC. OF EACH NEURON!
#define CENTERX		(0.5)
#define CENTERY		(0.5)
#define RADIUS		(0.45)
#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y

// NEURON AND NETWORK PARAMETERS
#define EVENTVALUE	(-1.23)		// POINCARE SECTION
#define THSYN		(-0.98)
#define GSYN		(0.005)
#define A			(1.0)
#define B			(3.0)
#define C			(1.0)
#define D			(5.0)
#define XR			(-1.6)
#define S			(4.0)
#define R			(0.001)
#define IAPP		(1.5)



// INTEGRATOR PARAMETERS
#define NVAR_S		(3)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NVAR_N		(9)		// NUMBER OF VARIABLES OF THE NETWORK
#define TOL		(1.0e-8)	// TOLERANCE FOR THE RUNGE-KUTTA INTEGRATION
#define INITIAL_STEP	(1.0e-6)	// INITIAL STEPSIZE



