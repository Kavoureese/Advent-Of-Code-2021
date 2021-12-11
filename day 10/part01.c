#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define BUF_LEN 256

static inline char is_bracket(char);
static inline char is_opening(char);
static inline uint32_t map_bracket_to_value(char);
uint32_t is_corrupted(char*, uint32_t);

int main(void)
{
	FILE *file;
	char buf[BUF_LEN];
	uint32_t score = 0;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while(fgets(buf, BUF_LEN, file) != NULL)
	{
		uint32_t temp = strlen(buf);
		if(!is_bracket(buf[temp - 1]))
			buf[temp - 1] = '\0';
		
		score += is_corrupted(buf, temp);
	}
	fclose(file);
	
	fprintf(stdout, "Score: %u\n", score);
	
	return 0;
}

static inline char is_bracket(char a)
{
	if(a == 0x28 || a == 0x29 ||
	   a == 0x5b || a == 0x5d ||
	   a == 0x3c || a == 0x3e ||
	   a == 0x7b || a == 0x7d)
	{
		return 1;
	}
	return 0;
}

static inline char is_opening(char a)
{
	if(a == 0x28 || a == 0x3c || a == 0x5b || a == 0x7b)
		return 1;
	return 0;
}

static inline uint32_t map_bracket_to_value(char a)
{
	switch(a)
	{
		case ')':
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
	}
}

uint32_t is_corrupted(char *buf, uint32_t len)
{
	char stack[BUF_LEN] = {0};
	int32_t top = 0, i;
	
	for(i = 0; i < len; ++i)
	{
		char temp = buf[i];
		
		if(is_opening(temp))
			stack[top++] = temp;
		else
		{
			if(top == 0) // invalid
				return map_bracket_to_value(temp);
			else
			{
				if(temp == ')' && stack[top - 1] == '(' ||
				   temp == '}' && stack[top - 1] == '{' ||
				   temp == ']' && stack[top - 1] == '[' ||
				   temp == '>' && stack[top - 1] == '<')
				{
					--top;
				}
				else // invalid
					return map_bracket_to_value(temp);
			}
		}
	}
	return 0;
}