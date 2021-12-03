#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define INPUT_SIZE 12

int main(void)
{
	FILE *file;
	uint32_t counters[INPUT_SIZE] = {0}, numl = 0, 
	gamma = 0, epsilon = 0, temp;
	uint8_t i;
	char str[INPUT_SIZE+1];
	
	file = fopen("input.txt", "r");
	
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while(!feof(file))
	{
		fscanf(file, "%s", str);
		
		for(i = 0; i < INPUT_SIZE; ++i)
		{
			counters[i] += (str[i] - '0');
		}
		++numl;
	}
	
	temp = numl / 2;
	for(i = 0; i < INPUT_SIZE; ++i)
	{
		gamma = (gamma << 1) + (counters[i] > temp);
		epsilon = (epsilon << 1) + (counters[i] < temp);
	}
	
	fprintf(stdout, "%d\n", gamma * epsilon);
	
	fclose(file);
	return 0;
}