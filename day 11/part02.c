#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define SIZE 10
#define BUF_LEN 12

char octopuses[SIZE*SIZE][2];

void increment_octo(void);
uint32_t check_for_flashes(void);
void increment_adjacent(uint8_t, uint8_t);
void increment_util(uint8_t, uint8_t);
void reset_flash_status(void);

int main(void)
{
	FILE *file;
	char buf[BUF_LEN];
	uint8_t i, j;
	uint32_t steps = 0;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	i = 0, j = 0;
	while(fgets(buf, BUF_LEN, file) != NULL)
	{
		uint8_t temp = strlen(buf);
		if(!(buf[temp - 1] >= '0' && buf[temp - 1] <= '9'))
			buf[temp - 1] = '\0';
		
		for(j = 0; j < temp; ++j)
			octopuses[i*SIZE + j][0] = buf[j] - '0';
		++i;
	}
	fclose(file);
	
	for(i = 0; i < SIZE; ++i)
        for(j = 0; j < SIZE; ++j)
            octopuses[i * SIZE + j][1] = 0;
	
	steps = 0;
	while(1)
	{
		increment_octo();
		
		if(check_for_flashes() == 100)
			break;
		++steps;
		reset_flash_status();
	}
	
	fprintf(stdout, "Step: %u\n", steps + 1);	
	return 0;
}

void increment_octo(void)
{
	uint8_t i, j;
	for(i = 0; i < SIZE; ++i)
		for(j = 0; j < SIZE; ++j)
			++octopuses[i*SIZE + j][0];
}

void reset_flash_status(void)
{
	uint8_t i, j;
	for(i = 0; i < SIZE; ++i)
		for(j = 0; j < SIZE; ++j)
			octopuses[i * SIZE + j][1] = 0;
}

uint32_t check_for_flashes(void)
{
	uint8_t i, j;
	uint32_t flashes = 0;
	
	// Check for flashes
	for(i = 0; i < SIZE; ++i)
	{
		for(j = 0; j < SIZE; ++j)
		{
			if(octopuses[i * SIZE + j][0] > 9 && octopuses[i * SIZE + j][1] == 0) // flashed
			{
				++flashes;
				octopuses[i * SIZE + j][0] = 0;
				octopuses[i * SIZE + j][1] = 1;
				increment_adjacent(i, j);
			}
		}
	}
	
	// check for new flashes 
	if(flashes > 0)
		flashes += check_for_flashes();
	
	return flashes;
}

void increment_adjacent(uint8_t col, uint8_t row)
{
	if(col != 0) // top
	{
		increment_util(col - 1,row);
		if(row != 0) // top left
			increment_util(col - 1, row - 1);
			
		if(row != SIZE - 1) // top right
			increment_util(col - 1, row + 1);
	}
	
	if(col != SIZE - 1) // bottom
	{
		increment_util(col + 1, row);
		if(row != 0) // bottom left
			increment_util(col + 1, row - 1);
			
		if(row != SIZE - 1) // bottom right
			increment_util(col + 1, row + 1);
	}
	
	if(row != 0) // left
		increment_util(col, row - 1);
	
	if(row != SIZE - 1) // right
		increment_util(col, row + 1); 
}

void increment_util(uint8_t i, uint8_t j)
{
	if(octopuses[i * SIZE + j][1] == 0)
	{
		++octopuses[i * SIZE + j][0];
	}
}