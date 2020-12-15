#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "kvs.h"

int main()
{

	void *handle;
	kvs_t* (*open)();
	int (*close)(kvs_t *);
	int (*put)(kvs_t *, const char *, const char *);
	char* (*get)(kvs_t *, const char *);
	char *error;
	
	handle = dlopen("./libkvs.so", RTLD_LAZY);
	if(!handle){
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	open = (kvs_t* (*)())dlsym(handle, "open");
	if ((error = dlerror()) != NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	close = (int(*)(kvs_t *))dlsym(handle, "close");
	if ((error = dlerror()) != NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	put = (int(*)(kvs_t *, const char *, const char *))dlsym(handle, "put");
	if ((error = dlerror()) != NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	get = (char*(*)(kvs_t *, const char *))dlsym(handle, "get");
	if ((error = dlerror()) != NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	// 1. create KVS

	kvs_t* kvs = open();

	if(!kvs) {
		printf("Failed to open kvs\n");
		return -1;
	}

	// 2. put data
	//    1) file read
	//    2) put data

	char** keys = (char**) malloc (sizeof(char*) * 100);
	for(int i=0; i<100; i++)
		keys[i] = (char*) malloc (sizeof(char)* 100);

	char key[100];
	char* value = (char*) malloc (sizeof(char)* 300);
	char* rvalue;

	FILE *file = fopen("student.dat","rb");

	if(file == NULL)
		return -1;

	int i = 0;
	while(1){
		if(fscanf(file, "%s %s", key, value) != 2)
			break;

		if(put(kvs, key, value) < 0){
			printf("Failed to put data\n");
			exit(-1);
		}
		strcpy(keys[i++], key);
	}

	// 3. get for test
	//    1) file read
	//    2) get & compare return value with original value

	int item_num = kvs->items;
	for(int i=0; i<item_num; i++){
		strcpy(key, keys[i]);
		if(!(rvalue = get(kvs, key))){
			printf("Failed to get data\n");
			exit(-1);
		}
		printf("get: %s, %s\n", key, rvalue);
	}
	
	fclose(file);

	// free memory allocation
	for(int i=0; i<100; i++)
		free(keys[i]);
	free(keys);
	free(value);
	close(kvs);

	if (dlclose(handle) < 0){
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	return 0;
}
