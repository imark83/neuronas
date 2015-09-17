#ifndef __my_protocol_h__
#define __my_protocol_h__

#define ATTACH_MAX_SIZE	512

typedef enum {SEND_ME=0, SEND_YOU, NO_MORE, WORK_DONE, THANK_YOU, THANK_YOU_NO_MORE} header_t;

typedef struct _message_t {
	header_t header;		// header of the message
	unsigned int index;		// position of data processed
	size_t len;		// length of data requested/processed
} message_t;

typedef int* attach_t;	// data processed

#endif

