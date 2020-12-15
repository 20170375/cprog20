#include "kvs.h"

char* get(kvs_t* kvs, const char* key)
{
	/* do program here */
	if(kvs == NULL){
		printf("kvs is null\n");
		return NULL;
	}

	node_t* current = kvs->db;
	int item_num = kvs->items;
	for(int i=0; i<item_num; i++){
		if(current == NULL)
			break;
		if(strcmp(current->key, key) == 0)
			return current->value;
		current = current->next;
	}

	char* value = (char*)malloc(sizeof(char)*100);

	if(!value){
		printf("Failed to malloc\n");
		return NULL;
	}

	strcpy(value, "deadbeaf");
	return value;
}
