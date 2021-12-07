#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#define INPUT_BUF_SIZE 4096
#define U32_MAX_VALUE 4294967295

typedef uint16_t u16;
typedef uint32_t u32;

static inline u32 calculate_fuel_part1(u32 a) {return a;}
static inline u32 calculate_fuel_part2(u32 a) {return a*(a+1)/2;}

int main(void)
{
	FILE *file;
	u16 i, j, input_len = 1, *arr;
	u32 *fuel;
	char buf[INPUT_BUF_SIZE], *token;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	fgets(buf, INPUT_BUF_SIZE, file);
	fclose(file);

	for(i = 0; buf[i] != '\0'; ++i)
		if(buf[i] == ',')
			++input_len;
	
	arr = (u16*) malloc(sizeof(u16)*input_len);
	
	i = 0;
	token = strtok(buf, ",");
	while(token != NULL)
	{
		arr[i] = (u16) strtol(token,NULL,10);
		token = strtok(NULL, ",");
		++i;
	}
	
	u32 max = 0, min = U32_MAX_VALUE, size;
	for(i = 0; i < input_len; ++i)
	{
		if(max < arr[i])
			max = arr[i];
		if(min > arr[i])
			min = arr[i];
	}		
	size = max - min;
	fuel = (u32*) malloc(sizeof(u32)*size);
	
	for(i = 0; i < size; ++i)
	{
		u32 sum = 0;
		for(j = 0; j < input_len; ++j)
		{
			sum += calculate_fuel_part2(abs(arr[j] - i));
		}
		fuel[i] = sum;
	}
	
	u32 index = 0;
	min = U32_MAX_VALUE;
	for(i = 0; i < size; ++i)
	{
		if(min > fuel[i])
		{
			min = fuel[i];
			index = i;
		}
	}
		
	fprintf(stdout, "fuel: %u, pos: %u\n", min, index);
	return 0;
}