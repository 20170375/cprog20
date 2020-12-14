#include "kvs.h"

int close(kvs_t* kvs)
{
	/* do program */

	if(kvs)
		free(kvs);

	return 0;
}
