#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define BUF_CAP 128
#define STR_LEN 100

typedef uint32_t u32;

char (*arr)[STR_LEN+1];

u32 calculate_basin(u32, u32, u32);

int main(void)
{
	FILE *file;
	char buf[BUF_CAP];
	u32 input_len = 1, i, j, prod;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while((i = getc(file)) != EOF)
		input_len = input_len + (i == '\n');
	
	if (fseek(file, 0L, SEEK_SET) != 0)
	{
		fprintf(stdout, "Error rewinding file!\n");
		exit(1);
	}
	
	arr = malloc(sizeof(*arr) * input_len);
	if(arr == NULL)
	{
		fprintf(stdout, "Failed allocation!\n");
		exit(1);
	}
	
	i = 0;
	while(fgets(buf, BUF_CAP, file) != NULL)
	{
		u32 len = strlen(buf);
		if(!(buf[len - 1] >= '0' && buf[len - 1] <= '9'))
			buf[(len--) - 1] = '\0';
		
		strcpy(arr[i++], buf);
	}
	fclose(file);
	
	for(i = 0; i < input_len; ++i)
	{
		for(j = 0; j < STR_LEN; ++j)
		{
			// Check top
			if(i != 0)
				if(arr[i][j] >= arr[i-1][j])
					continue;
			// Check bottom
			if(i != input_len - 1)
				if(arr[i][j] >= arr[i+1][j])
					continue;
			// Check left
			if(j != 0)
				if(arr[i][j] >= arr[i][j-1])
					continue;
			// Check right
			if(j != STR_LEN - 1)
				if(arr[i][j] >= arr[i][j+1])
					continue;
			
			
		}
	}
	
	fprintf(stdout, "Sum: %u\n", sum);
	
	return 0;
}