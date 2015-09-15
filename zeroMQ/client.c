#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>


#define N	64
#define M	64

#include "my_protocol.h"

int main (int argc, char **argv) {
	// context of zeroMQ
	void *context = zmq_ctx_new ();
	void *socket  = zmq_socket (context, ZMQ_REQ);
	int errMsg = zmq_bind (socket, "tcp://eth0:5555");
	if (errMsg != 0) {
		fprintf (stderr, "Error binding socket\n");
		return errMsg;
	}

	message_t buffer;
	
}
