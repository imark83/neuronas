#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#include "parameters.h"


int main (int argc, char *argv[]) {
	int i, j;
	const size_t global_work_size[] = {M, N};
	const size_t local_work_size[] = {1, 1};
	const char *source = "#include \"neuron_kernel.cl\"\n";
	const char *kernelName = "neuron";

	#include "openCL_start.h"

	cl_event event;

	// ALLOCATE MEMORY


	// SET KERNEL ARGUMENTS


	// LAUNCH KERNEL
	clEnqueueNDRangeKernel (queue, kernel,
		2,			// WORKING DIMENSIONS
		NULL,			// GLOBAL OFFSET
		global_work_size,	// GLOBAL WORK SIZE
		local_work_size,	// LOCAL WORK SIZE
		0,			// NUM EVENTS IN WAIT LIST
		NULL,			// WAIT LIST
		&event);		// EVENT FOR TIMING

	clFinish (queue);


	// RELEASE MEMORY

	// CLEAN UP OPENCL OBJECTS
	clReleaseKernel (kernel);
	clReleaseProgram (program);
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}
