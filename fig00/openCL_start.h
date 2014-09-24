
int status;
	
size_t devInfo, devInfos[3];
	cl_uint num_devices,entries;
	cl_ulong long_entries;
char dname[500];

// Get the first available platform
// Example: AMD Accelerated Parallel Processing
cl_platform_id platform[1];
clGetPlatformIDs(1,			// number of platforms to add to list
		platform, 		// list of platforms found
		NULL);			// number of platforms available

// Get the first GPU device the platform provides
cl_device_id device, devices[1], subdevices[4];
clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_ALL, 
		1, 			// number of devices to add
		&devices[0], 		// list of devices
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

clGetDeviceInfo(devices[0],CL_DRIVER_VERSION, 500, dname,NULL);
printf("\tDriver version = %s\n", dname);
		
clGetDeviceInfo(devices[0],CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong),&long_entries,NULL);
printf("\tGlobal Memory (MB):\t%lu\n",(unsigned long int) long_entries/1024/1024);

clGetDeviceInfo(devices[0],CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,sizeof(cl_ulong),&long_entries,NULL);
printf("\tGlobal Memory Cache (MB):\t%lu\n",(unsigned long int) long_entries/1024/1024);

clGetDeviceInfo(devices[0],CL_DEVICE_LOCAL_MEM_SIZE,sizeof(cl_ulong),&long_entries,NULL);
printf("\tLocal Memory (KB):\t%i\n",(int) long_entries/1024);

clGetDeviceInfo(devices[0],CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_ulong),&long_entries,NULL);
printf("\tMax clock (MHz) :\t%i\n",(int) long_entries);

clGetDeviceInfo(devices[0],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),&entries,NULL);
printf("\tNumber of parallel compute cores:\t%d\n",entries);

cl_device_local_mem_type cdlmt;
clGetDeviceInfo(devices[0],CL_DEVICE_LOCAL_MEM_TYPE, sizeof(cl_device_local_mem_type),&cdlmt,NULL);
if (cdlmt == CL_LOCAL)			
	printf("\tLocal Memory type:\t LOCAL\n");
if (cdlmt == CL_GLOBAL)
	printf("\tLocal Memory type:\t GLOBAL\n");


device = devices[0];

clGetDeviceInfo (device, CL_DEVICE_NAME, 500, dname,NULL);
printf ("\nChosen device = %s\n\n", dname);




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


