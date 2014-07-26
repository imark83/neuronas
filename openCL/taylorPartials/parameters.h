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



#define M		(128)		// HORIZONTAL GRIDSIZE
#define N		(128)		// VERTICAL GRIDSIZE
#define yMIN		(-0.5)		// MINIMUM VALUE FOR y
#define yMAX		(0.7)		// MAXIMUM VALUE FOR y
#define YMIN		(-0.5)		// MINIMUM VALUE FOR Y
#define YMAX		(0.5)		// MAXIMUM VALUE FOR Y
#define H		(0.125)		// ENERGY
#define TF		(600.0)		// FINAL INTEGRATION TIME



#define TOL 		(1.0e-8)	// TOLERANCE FOR INTEGRATION
#define ORDER		(15)		// ORDER OF TAYLOR SERIES


#define NVAR	(4)			// NUMBER OF VARIABLES
#define NCOL	(8)			// NUMBER OF VARIABLES INCLUDING VARIATIONALS
#define NDER	(1)			// NUMBER OF VARIATIONALS (1 FOR FLI)
//#define TF	(64.2652399541350)	// FINAL TIME

