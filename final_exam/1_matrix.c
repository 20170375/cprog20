#include<stdio.h>
#include<stdlib.h>

#define ROWS 5
#define COLS 5

int add_cross(int* data, int r, int c)
{
	int up = (r-1)*COLS + c;
	int down = (r+1)*COLS + c;
	int right = r*COLS + c+1;
	int left= r*COLS + c-1;

	int sum = 0;

	if(data + up < (data + ROWS*COLS))
		sum += data[up];
	
	if(data + down < (data + ROWS*COLS))
		sum += data[down];

	if(data + right < (data + ROWS*COLS))
		sum += data[right];

	if(data + left < (data + ROWS*COLS))
		sum += data[left];
	
	return sum;
}

int main()
{
	int i, j;

	int* data = (int*) malloc (sizeof(int) * ROWS * COLS);

	if(!data) {
		printf("Failed to alloc memory\n");
		return 0;
	}
	
	// set initial value
	int* data_str = data;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			*(data_str + j) = i*j;
		}
		data_str = data_str + COLS;
	}


	// print data
	printf("---------------\n");
	data_str = data;
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			printf("%3d ", *(data_str + j));
		}
		printf("\n");
		data_str = data_str + COLS;
	}
	printf("---------------\n");


	// get add-cross
	for(i=1; i<ROWS; i++){
		for(j=1; j<COLS; j++){
			int sum = add_cross(data, i, j);
			printf("%3d ", sum);
		}
		printf("\n");
	}
}
