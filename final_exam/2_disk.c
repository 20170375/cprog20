#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("Please type the number of sectors\n");
		printf("e.g.: ./2_disk 8\n");
		return -1;
	}


	// disk settings 
	int rpm = 5400;
	int seek_time = 6; // seek time (ms)
	int sect_per_track = 600; // average number of sectors per track 

	int sectors = atoi(argv[1]);
	printf("Read %d sectors\n", sectors);

	/* do program here */
	int total_time, rotation_latency, transfer_time;
	rotation_latency = 1/2 * (60/rpm) * 1000;
	transfer_time = 60/rpm * 1/400/sect_per_track * 1000;
	total_time = seek_time + rotation_latency + transfer_time;

	printf("seek_time %d(ms)\n",seek_time);
	printf("Rotation latency %d\n",rotation_latency);
	printf("Transfer time %d\n",transfer_time);
	printf("total time %d\n",total_time);

	return 0;	
}
