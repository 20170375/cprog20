#include "kvs.h"

int put(kvs_t* kvs, const char* key, const char* value)
{
	if(kvs == NULL)
		return -1;

	printf("put: %s, %s\n", key, value);
	/* do program here */
	node_t* newNode = (node_t*) malloc (sizeof(node_t));
	strcpy(newNode->key, key);
	newNode->value = (char*) malloc (sizeof(char)* 300);
	strcpy(newNode->value, value);

	node_t* tail = kvs->db;
	if(tail != NULL)
		tail->next = newNode;
	else
		kvs->db = newNode;
	kvs->items = kvs->items + 1;

	return 0;
}
