
#define DOUBLE


#ifdef DOUBLE
#define real_t double
#endif


#define FNAME 		"T.txt"

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



// GEOMETRY PARAMETERS
#define M		200
#define N		200
#define CUTNUMBER	5

#define CENTERX		(0.33333)
#define CENTERY		(0.66666)
#define RADIUS		(0.18333)

#define XMIN		(CENTERX-RADIUS)	// MINIMUM VALUE FOR y
#define XMAX		(CENTERX+RADIUS)	// MAXIMUM VALUE FOR y
#define YMIN		(CENTERY-RADIUS)	// MINIMUM VALUE FOR Y
#define YMAX		(CENTERY+RADIUS)	// MAXIMUM VALUE FOR Y


// INTEGRATION PARAMETERS
#define ORDER		17	// ORDER OF TAYLOR SERIES METHOD
#define TOL		1.0e-12	// TOLERANCE FOR INTEGRATION
#define NVAR1		3	// NUMBER OF VARIABLES OF A SINGLE NEURON
#define NVAR		9	// NUMBER OF VARIABLES OF A 3-CELL CPG
#define EVENTVALUE	(-0.04)	// POINCARE SECTION





