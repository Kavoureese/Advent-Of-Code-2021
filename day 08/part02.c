#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define INPUT_BUF_LEN 1024

char strings[10][8];
char numbers[10][8];
char output[4][8];

void sort_alpha(char *, u8);
void sort_len();
void map_strings_to_numbers();

int main(void)
{
	FILE *file;
	u8 first_len, second_len, temp, i, j, index;
	u32 sum = 0, tens;
	char buf[INPUT_BUF_LEN], *first, *second;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	while(fgets(buf, INPUT_BUF_LEN, file) != NULL)
	{
		first = strtok(buf, "|");
		first_len = strlen(first);
		if(!(first[first_len-1] >= 'a' && first[first_len-1] <= 'z'))
			first[first_len-1] = '\0';
		
		second = strtok(NULL, "|");
		++second;
		second_len = strlen(second);
		if(!(second[second_len-1] >= 'a' && second[second_len-1] <= 'z'))
			second[second_len-1] = '\0';
		
		index = 0;
		first = strtok(first, " ");
		while(first != NULL)
		{
			temp = strlen(first);
			sort_alpha(first, temp);
			
			strcpy(strings[index++], first);
			
			first = strtok(NULL, " ");
		}
		
		index = 0;
		second = strtok(second, " ");
		while(second != NULL)
		{
			temp = strlen(second);
			sort_alpha(second, temp);
			
			strcpy(output[index++], second);
			
			second = strtok(NULL, " ");
		}
		
		sort_len();
		map_strings_to_numbers();
		
		tens = 1;
		for(i = 0; i < 4; ++i)
		{
			for(j = 0; j < 10; ++j)
				if(strcmp(output[3-i], numbers[j]) == 0)
				{
					sum += j * tens;
					tens *= 10;
					break;
				}
		}
	}
	fclose(file);
	
	fprintf(stdout, "SUM: %u\n", sum);
	return 0;
}

void map_strings_to_numbers()
{
	char *temp, *t_str;
	u8 i, index, used[2];
	
	t_str = (char*) malloc(sizeof(char)*2);
	
	strcpy(numbers[1], strings[0]);
	strcpy(numbers[4], strings[2]);
	strcpy(numbers[7], strings[1]);
	strcpy(numbers[8], strings[9]);
	
	for(i = 3; i <= 5; ++i)
	{
		if(strchr(strings[i], numbers[1][0]) != NULL && strchr(strings[i], numbers[1][1]) != NULL)
		{
			strcpy(numbers[3], strings[i]);
			used[0] = i;
			break;
		}
	}

	index = 0;
	for(i = 0; i < strlen(numbers[4]); ++i)
	{
		temp = strchr(numbers[1], numbers[4][i]);
		if(temp == NULL)
		{
			t_str[index++] = numbers[4][i];
		}
	}
	
	for(i = 3; i <= 5; ++i)
	{
		if(strchr(strings[i], t_str[0]) != NULL && strchr(strings[i], t_str[1]) != NULL)
		{
			strcpy(numbers[5], strings[i]);
			used[1] = i;
			break;
		}
	}
	free(t_str);
	
	switch(used[0]+used[1])
	{
		case 7:
			strcpy(numbers[2], strings[5]);
			break;
		case 8:
			strcpy(numbers[2], strings[4]);
			break;
		case 9:
			strcpy(numbers[2], strings[3]);
			break;
	}
	
	for(i = 6; i <= 8; ++i)
	{
		if(strchr(strings[i], numbers[3][0]) != NULL &&
		   strchr(strings[i], numbers[3][1]) != NULL &&
		   strchr(strings[i], numbers[3][2]) != NULL &&
		   strchr(strings[i], numbers[3][3]) != NULL &&
		   strchr(strings[i], numbers[3][4]) != NULL)
		{
			strcpy(numbers[9], strings[i]);
			used[1] = i;
			break;
		}
	}
	
	for(i = 6; i <= 8; ++i)
	{
		if(strchr(strings[i], numbers[5][0]) != NULL &&
		   strchr(strings[i], numbers[5][1]) != NULL &&
		   strchr(strings[i], numbers[5][2]) != NULL &&
		   strchr(strings[i], numbers[5][3]) != NULL &&
		   strchr(strings[i], numbers[5][4]) != NULL &&
		   strcmp(strings[i], numbers[9]) != 0)
		{
			strcpy(numbers[6], strings[i]);
			used[0] = i;
			break;
		}
	}
	
	
	switch(used[0]+used[1])
	{
		case 13:
			strcpy(numbers[0], strings[8]);
			break;
		case 14:
			strcpy(numbers[0], strings[7]);
			break;
		case 15:
			strcpy(numbers[0], strings[6]);
			break;
	}
}

void sort_alpha(char *p, u8 len)
{
	u8 i, j;
	char temp;
	
	for(i = 0; i < len - 1; ++i)
	{
		for(j = i + 1; j < len; ++j)
			if(p[i] > p[j])
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
	}
}

void sort_len()
{
	u8 i, j;
	char *temp = (char*) malloc(sizeof(char)*8);
	
	for(i = 0; i < 9; ++i)
	{
		for(j = i + 1; j < 10; ++j)
			if(strlen(strings[i]) > strlen(strings[j]))
			{
				strcpy(temp, strings[i]);
				strcpy(strings[i], strings[j]);
				strcpy(strings[j], temp);
			}
	}
	free(temp);
}