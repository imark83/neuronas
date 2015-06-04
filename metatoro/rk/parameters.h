#define MIN(a,b) ((a)<(b))? (a) : (b)
#define MAX(a,b) ((a)>(b))? (a) : (b)

#define CPU

#define FILENAME	"T.bin"
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
#define N		(4)		// NUMBER OF INTEGRATIONS
#define CUTNUMBER	(400)		// NUMBER OF CUTS FOR POINC. OF EACH NEURON!

// NEURON AND NETWORK PARAMETERS
#define INTERWORLD_PROPORTION (0.05);

#define EVENTVALUE	(-0.04)		// POINCARE SECTION
#define THSYN		(-0.03)
#define ESYN		(-0.0625)
#define GSYN		(0.0004)
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
#define VSHIFT		(-0.021)	
//#define VSHIFT 		(-0.01876)



// INTEGRATOR PARAMETERS
#define NVAR_S		(3)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NVAR_N		(27)		// NUMBER OF VARIABLES OF THE NETWORK
#define NVAR_SW		(9)		// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NNEURON		(9)
#define NNEURON_SW	(3)
#define TOL		(1.0e-6)	// TOLERANCE FOR THE RUNGE-KUTTA INTEGRATION
#define INITIAL_STEP	(1.0e-6)	// INITIAL STEPSIZE



