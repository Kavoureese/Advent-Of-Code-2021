#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
	FILE *file;
	uint32_t x_pos = 0, depth = 0, aim = 0, magnitude;
	char direction[8];
	
	file = fopen("input.txt", "r");
	
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while(!feof(file))
	{
		fscanf(file, "%s %d", direction, &magnitude);
		
		switch(direction[0])
		{
			case 'f':
				x_pos += magnitude;
				depth += aim * magnitude;
				break;
			case 'u':
				aim -= magnitude;
				break;
			case 'd':
				aim += magnitude;
				break;
		}
	}
	
	fprintf(stdout, "%d", x_pos * depth);
	
	fclose(file);
	return 0;
}
