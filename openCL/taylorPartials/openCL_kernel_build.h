
cl_program program = clCreateProgramWithSource (context,
		1,			// number of strings
		(const char **)&source,	// strings
		NULL,			// string length or NULL terminated
		&status);		// no error code returned
if (status != CL_SUCCESS) {
	printf ("create program error = %d\n", status);
	return 1;
}

status = clBuildProgram (program,
		1,			// number of devices
		&device,		// pointer to device list
		"-I ./ ",		// optional (build options)
		NULL, NULL); 		// optional (callback function, argument)

if(status != CL_SUCCESS) { 
	printf("Error: Building Program \n");
	// First call to know the proper size
	size_t log_size;
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	char build_log[log_size+1];
	// Second call to get the log
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
	build_log[log_size] = '\0';
	puts (build_log);
	return 1; 
}

	// First call to know the proper size
	size_t log_size;
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	char build_log[log_size+1];
	// Second call to get the log
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
	build_log[log_size] = '\0';
	//puts (build_log);



cl_kernel testKernel = clCreateKernel (
		program,		// program object
		"test",		// kernel name in program
		NULL);			// no error code returned*/

/*int warp;
	clGetKernelWorkGroupInfo (testKernel, device,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof (size_t), &warp, NULL);
	printf ("WARP size = %i\n", warp);*/

