#include "parameters.h"
#include "rk_coef.h"



__kernel void neuron () {
	printf ("Hello from val %zi\n", M*get_global_id(1) + get_global_id(0));


}
