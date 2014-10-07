char buildOptions[100] = "-I .";
int status;
	
size_t devInfo, devInfos[3];
char dname[500];

// Get the first available platform
// Example: AMD Accelerated Parallel Processing
cl_platform_id platform[2];
clGetPlatformIDs(2,			// number of platforms to add to list
		platform, 		// list of platforms found
		NULL);			// number of platforms available

// Get the first GPU device the platform provides
cl_device_id device, devices[3];
clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_ALL, 
		1, 			// number of devices to add
		&devices[0], 		// list of devices
		NULL);			// number of devices available


clGetDeviceIDs(platform[1], CL_DEVICE_TYPE_ALL, 
		2, 			// number of devices to add
		&devices[1], 		// list of devices
		NULL);			// number of devices available


clGetPlatformInfo (platform[0], CL_PLATFORM_NAME,500,dname,NULL);
printf ("CL_PLATFORM_NAME = %s\n", dname);
clGetDeviceInfo (devices[0], CL_DEVICE_NAME, 500, dname,NULL);
printf ("\tDevice name = %s\n", dname);
clGetDeviceInfo (devices[0], CL_DEVICE_MAX_COMPUTE_UNITS, 
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax compute Units = %i\n", (int) devInfo);
clGetDeviceInfo (devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, 
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax work group size = %i\n", (int) devInfo);
clGetDeviceInfo (devices[0], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax number of dimensions = %i\n", (int) devInfo);
clGetDeviceInfo (devices[0], CL_DEVICE_MAX_WORK_ITEM_SIZES,
		3*sizeof (size_t), devInfos, NULL);
printf ("\tMax work group sizes = %i, %i, %i\n\n", 
	(int) devInfos[0], (int) devInfos[1], (int) devInfos[2]);



clGetPlatformInfo (platform[1], CL_PLATFORM_NAME,500,dname,NULL);
printf ("CL_PLATFORM_NAME = %s\n", dname);
clGetDeviceInfo (devices[1], CL_DEVICE_NAME, 500, dname,NULL);
printf ("\tDevice name = %s\n", dname);
clGetDeviceInfo (devices[1], CL_DEVICE_MAX_COMPUTE_UNITS, 
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax compute Units = %i\n", (int) devInfo);
clGetDeviceInfo (devices[1], CL_DEVICE_MAX_WORK_GROUP_SIZE, 
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax work group size = %i\n", (int) devInfo);
clGetDeviceInfo (devices[1], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
		sizeof (size_t), &devInfo, NULL);
printf ("\tMax number of dimensions = %i\n", (int) devInfo);
clGetDeviceInfo (devices[1], CL_DEVICE_MAX_WORK_ITEM_SIZES,
		3*sizeof (size_t), devInfos, NULL);
printf ("\tMax work group sizes = %i, %i, %i\n\n", 
	(int) devInfos[1], (int) devInfos[1], (int) devInfos[2]);


#ifdef CPU
device = devices[0];
#endif

#ifdef GPU0
device = devices[1];

setenv("CUDA_CACHE_DISABLE", "1", 1);
#endif

#ifdef GPU1
device = devices[2];

setenv("CUDA_CACHE_DISABLE", "1", 1);
#endif

clGetDeviceInfo (device, CL_DEVICE_NAME, 500, dname,NULL);

printf ("\nChosen device = %s\n", dname);


cl_context context = clCreateContext (
		0,			// optional (context properties)
		1,			// number of devices
		&device,		// pointer to device list
		NULL, NULL, 		// optional (callback func for reporting errors)
		&status);		// no error code returned
if (status != CL_SUCCESS) {
	printf ("create context error = %d\n", status);
	return 1;
}
cl_command_queue queue = clCreateCommandQueue (
		context,		// valid context
		device,			// device associated with context
		CL_QUEUE_PROFILING_ENABLE,	// optional (command queue properties)
		&status);		// no error code returned
if (status != CL_SUCCESS) {
	printf ("create queue error = %d\n", status);
	return 1;
}


