#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define SIMULATED_DAYS 256

int main(void)
{
	FILE *file;
	u16 input_len = 1;
	u64 i, j;
	char buf[1024], *token;
	u64 fish_states[9] = {0};

	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	fgets(buf, 1024, file);
	fclose(file);

	for(i = 0; buf[i] != '\0'; ++i)
		if(buf[i] == ',')
			++input_len;
		
	i = 0;
	token = strtok(buf, ",");
	while(token != NULL)
	{
		u8 temp = (u8) strtol(token,NULL,10);
		++fish_states[temp];
		token = strtok(NULL, ",");
		++i;
	}
	
	for(i = 0; i < SIMULATED_DAYS; ++i)
	{
		u64 new_fish = fish_states[0];
		
		for(j = 0; j < 8; ++j)
			fish_states[j] = fish_states[j + 1];
		
		fish_states[6] += new_fish;
		fish_states[8] = new_fish;
		
		fprintf(stdout, "Day %d completed.\n", i+1);
	}
	
	u64 total_pop = 0;
	for(i = 0; i < 9; ++i)
		total_pop += fish_states[i];
	printf("Total pop: %llu\n", total_pop);
	
	return 0;
}
