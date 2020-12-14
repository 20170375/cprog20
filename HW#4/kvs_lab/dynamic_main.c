#include "kvs.h"

extern kvs_t* open();
extern int close(kvs_t* kvs);
extern int put(kvs_t* kvs, const char* key, const char* value);
extern char* get(kvs_t* kvs, const char* key);

int main()
{
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

	return 0;
}
