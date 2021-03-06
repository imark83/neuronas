#define MIN(a,b) ((a)<(b))? (a) : (b)
#define MAX(a,b) ((a)>(b))? (a) : (b)

#define CPU

#define FILENAME	"T.txt"
#define FLOAT


#ifdef FLOAT
#define real_t float
#define RANDOM_FILE	"random32.bin"
#endif

#ifdef DOUBLE
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define real_t double
#define RANDOM_FILE	"random64.bin"
#endif



// GEOMETRY VALUES
#define N			(10)		// GRIDSIZE
#define CUTNUMBER	(5000)		// NUMBER OF CUTS FOR POINC. OF EACH NEURON!
#define CENTERX		(0.5)
#define CENTERY		(0.5)
#define RADIUS		(0.49)
#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y

// NEURON AND NETWORK PARAMETERS
#define EVENTVALUE	(-1.23)		// POINCARE SECTION
#define THSYN		(-0.91)
#define GSYN		(0.01)
#define ESYN		(-2.0)
#define A			(1.0)
#define B			(3.0)
#define C			(1.0)
#define D			(5.0)
#define XR			(-1.6)
#define S			(4.0)
#define R			(0.001)
// MINIMUM VALUE 1.269
#define IAPP		(1.3)
#define INTERWORLD_PROPORTION	(0.2)


// INTEGRATOR PARAMETERS
#define NVAR_S		(3)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NVAR_N		(27)		// NUMBER OF VARIABLES OF THE NETWORK
#define NVAR_SW		(9)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NNEURON		(9)
#define NNEURON_SW	(3)
#define TOL			(1.0e-5)	// TOLERANCE FOR THE RUNGE-KUTTA INTEGRATION
#define INITIAL_STEP	(1.0e-6)	// INITIAL STEPSIZE



