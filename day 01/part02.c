#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
	FILE *file;
	uint32_t buffer[4], i, sum_prev, sum_next, count = 0;
	
	file = fopen("input.txt", "r");
	
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	for(i = 0; i < 4; ++i)
		fscanf(file, "%d", &buffer[i]);
	while(!feof(file))
	{
		sum_prev = buffer[0] + buffer[1] + buffer[2];
		sum_next = buffer[1] + buffer[2] + buffer[3];
		
		if(sum_next > sum_prev)
			++count;
		
		buffer[0] = buffer[1];
		buffer[1] = buffer[2];
		buffer[2] = buffer[3];
		
		fscanf(file, "%d", &buffer[3]);
	}
	
	fprintf(stdout, "%d\n", count);
	
	fclose(file);
	return 0;
}
