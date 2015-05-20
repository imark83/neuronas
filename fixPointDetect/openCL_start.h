
	
	cl_platform_id platform;		// OpenCL Platform
	cl_device_id device;			// compute device 
	cl_context context;			// compute context
	cl_command_queue queue;			// compute command queue

	cl_program program;			// compute program
	cl_kernel kernel;			// compute kernel


	cl_int errorCode;
	char infoString[500];

	/* PLATFORM INITIALIZE AND PLATFORM INFO */
	if ((errorCode = clGetPlatformIDs(1, &platform, NULL)) != CL_SUCCESS) {
		printf ("Error getting Platform ID. Error code = %i\n", errorCode);
		return 0;
	}
	printf ("PLATFORM INFO:\n");

	clGetPlatformInfo (platform, CL_PLATFORM_PROFILE, 500, infoString, NULL);
	printf ("\tPlatform profile    = %s\n", infoString);

	clGetPlatformInfo (platform, CL_PLATFORM_VERSION, 500, infoString, NULL);
	printf ("\tPlatform version    = %s\n", infoString);

	clGetPlatformInfo (platform, CL_PLATFORM_NAME, 500, infoString, NULL);
	printf ("\tPlatform name       = %s\n", infoString);

	clGetPlatformInfo (platform, CL_PLATFORM_VENDOR, 500, infoString, NULL);
	printf ("\tPlatform vendor     = %s\n", infoString);

	if (argc > 1) if (strcmp ("show_extensions", argv[1]) == 0) {
		clGetPlatformInfo (platform, CL_PLATFORM_EXTENSIONS, 500, infoString, NULL);
		printf ("\tPlatform extensions = %s\n", infoString);
		return 0;
	}

	



	/* DEVICE INITIALIZE AND DEVICE INFO */

	if ((errorCode = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL)) != CL_SUCCESS) {
		printf ("Error getting Device ID. Error code = %i\n", errorCode);
		return 0;
	}


	printf ("DEVICE INFO:\n");

	clGetDeviceInfo (device, CL_DEVICE_NAME, 500, infoString, NULL);
	printf ("\tDevice name:        %s\n", infoString);

	clGetDeviceInfo (device, CL_DEVICE_ADDRESS_BITS, 500, infoString, NULL);
	printf ("\tDevice default address bits = %u\n", *((cl_uint *) infoString));

	clGetDeviceInfo (device, CL_DEVICE_AVAILABLE, 500, infoString, NULL);
	printf ("\tDevice available            = ");
		if (infoString[0]) printf ("TRUE\n");
		else printf ("FALSE\n");

	clGetDeviceInfo (device, CL_DEVICE_GLOBAL_MEM_SIZE, 500, infoString, NULL);
	printf ("\tDevice global mem size (MB) = %lu\n", (*((cl_ulong *) infoString) / 1024 / 1024));

	clGetDeviceInfo (device, CL_DEVICE_LOCAL_MEM_SIZE, 500, infoString, NULL);
	printf ("\tDevice local mem size (KB)  = %lu\n", (*((cl_ulong *) infoString) / 1024));

	clGetDeviceInfo (device, CL_DEVICE_LOCAL_MEM_TYPE, 500, infoString, NULL);
	printf ("\tDevice local mem type       = ");
		if (*((unsigned int *) infoString) == CL_LOCAL) printf ("LOCAL\n");
		if (*((unsigned int *) infoString) == CL_GLOBAL) printf ("GLOBAL\n");

	clGetDeviceInfo (device, CL_DEVICE_MAX_CLOCK_FREQUENCY, 500, infoString, NULL);
	printf ("\tDevice clock freq (MHz)     = %lu\n", *((cl_ulong *) infoString));

	clGetDeviceInfo (device, CL_DEVICE_MAX_COMPUTE_UNITS, 500, infoString, NULL);
	printf ("\tDevice compute units        = %lu\n", *((cl_ulong *) infoString));

	clGetDeviceInfo (device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 500, infoString, NULL);
	printf ("\tDevice compute max sizes    = %zi, %zi, %zi\n", *((size_t *) infoString), 
				*((size_t *) infoString+1), *((size_t *) infoString)+2);

	clGetDeviceInfo (device, CL_DEVICE_MAX_WORK_GROUP_SIZE, 500, infoString, NULL);
	printf ("\tDevice compute max sizes    = %zi\n", *((size_t *) infoString));






	/* CONTEXT CREATION */

	context = clCreateContext (NULL, 1, &device, NULL, NULL, &errorCode);
	if (errorCode != CL_SUCCESS) {
		printf ("Error creating Context. Error code = %i\n", errorCode);
		return 0;
	}





	/* QUEUE CREATION */

	queue = clCreateCommandQueue (context, device, CL_QUEUE_PROFILING_ENABLE, &errorCode);
	if (errorCode != CL_SUCCESS) {
		printf ("Error creating queue. Error code = %i\n", errorCode);
		return 0;
	}





	// PROGRAM CREATION
	program = clCreateProgramWithSource (context, 1, (const char **) &source, NULL, &errorCode);
	if (errorCode != CL_SUCCESS) {
		printf ("Error creating Program. Error code = %i\n", errorCode);
		return 0;
	}


	// PROGRAM BUILD AND BUILD LOG FILE
	if ((errorCode = clBuildProgram (program, 1, &device, "-I /Users/marcos/Desktop/neuronas/fixPointDetect", NULL, NULL)) != CL_SUCCESS) {
		printf ("Error building Program. Error code = %i\n", errorCode);
		
		size_t logSize;
		clGetProgramBuildInfo (program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
		char *buildLog = (char*) malloc (logSize * sizeof (char));
		clGetProgramBuildInfo (program, device, CL_PROGRAM_BUILD_LOG, logSize, buildLog, NULL);
		printf ("BUILD LOG:\n%s\n", buildLog);

		return 0;
	}




	// KERNEL BUILD AND KERNEL INFO
	kernel = clCreateKernel (program, kernelName, &errorCode);
	if (errorCode != CL_SUCCESS) {
		printf ("Error creating Kernel. Error code = %i\n", errorCode);
		return 0;
	}

/*	clGetKernelWorkGroupInfo ( kernel, device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof (size_t), infoString, NULL);
	printf ("\nWarp size = %zi\n", *((size_t*) infoString));
*/


