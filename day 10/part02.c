#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define BUF_LEN 256

static inline char is_bracket(char);
static inline char is_opening(char);
static inline uint32_t map_bracket_to_value(char);
uint64_t is_incomplete(char*, uint64_t);
void insertionSort(uint64_t*, uint64_t);

int main(void)
{
	FILE *file;
	char buf[BUF_LEN];
	uint64_t scores[101] = {0}, i = 0, input_len = 0;
	
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
		
		scores[i++] = is_incomplete(buf, temp);
		++input_len;
	}
	
	insertionSort(scores, input_len);
	
	i = 0;
	while(scores[i] == 0)
		++i;
	
	fprintf(stdout, "Score: %llu\n", scores[(input_len + i) / 2]);
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
		case '(':
			return 1;
		case '[':
			return 2;
		case '{':
			return 3;
		case '<':
			return 4;
	}
}

uint64_t is_incomplete(char *buf, uint64_t len)
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
				return 0;
			else
			{
				if(temp == ')' && stack[top - 1] == '(' ||
				   temp == '}' && stack[top - 1] == '{' ||
				   temp == ']' && stack[top - 1] == '[' ||
				   temp == '>' && stack[top - 1] == '<')
				{
					--top;
				}
				else if(temp == ')' && !(stack[top - 1] == '(') ||
						temp == '}' && !(stack[top - 1] == '{') ||
						temp == ']' && !(stack[top - 1] == '[') ||
						temp == '>' && !(stack[top - 1] == '<'))
				{
					return 0;
				}
			}
		}
	}
	
	uint64_t score = 0;
	for(i = top - 1; i >= 0; --i)
	{
		score *= 5;
		score += map_bracket_to_value(stack[i]);
	}

	return score;
}

void insertionSort(uint64_t arr[], uint64_t n)
{
    int64_t i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}