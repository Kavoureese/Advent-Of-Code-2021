#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define INPUT_BUF_LEN 1024

int main(void)
{
	FILE *file;
	u32 counter = 0;
	u8 temp;
	char buf[INPUT_BUF_LEN], *token, *p;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while(fgets(buf, INPUT_BUF_LEN, file) != NULL)
	{
		token = strtok(buf, "|");
		token = strtok(NULL, "|");
		++token;
		if(!(token[strlen(token)-1] >= 'a' && token[strlen(token)-1] <= 'z'))
			token[strlen(token)-1] = '\0';
		
		p = strtok(token, " ");
		while(p != NULL)
		{
			temp = strlen(p);
			switch(temp)
			{
				case 2:
					++counter;
					break;
				case 3:
					++counter;
					break;
				case 4:
					++counter;
					break;
				case 7:
					++counter;
					break;
			}
			p = strtok(NULL, " ");
		}
	}
	fclose(file);
	
	fprintf(stdout, "Count: %u\n", counter);
	
	return 0;
}