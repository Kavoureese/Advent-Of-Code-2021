#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#define INPUT_SIZE 12
#define INPUT_LEN 1000

typedef uint32_t u32;
typedef uint8_t u8;

typedef struct node {char str[INPUT_SIZE+1]; struct node *next;} node;
void append(node*, char*);
char delete_at_index(node**, char, u8, u32*);
u32 count_ones_at_index(node*, u8);

int main(void)
{
	FILE *file;
	u32 numl = 1, j = 0, len1s, len0s;
	char str[INPUT_SIZE+1], flag;
	
	file = fopen("input.txt", "r");
	
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	node *oxygen = (node *) malloc(sizeof(node));
	node *co2 = (node *) malloc(sizeof(node));
	
	fscanf(file, "%s", str);
	
	strcpy(oxygen->str, str);
	oxygen->next = NULL;
	
	strcpy(co2->str, str);
	co2->next = NULL;
	while(!feof(file))
	{
		fscanf(file, "%s", str);
		str[INPUT_SIZE] = '\0';
		
		append(oxygen, str);
		append(co2, str);
		
		++numl;
	}
	len1s = numl;
	len0s = numl;
	
	for(j = 0; j < INPUT_SIZE && len1s != 1; ++j)
	{
		float temp = len1s / 2.0f;
		u32 retval = count_ones_at_index(oxygen, j);

		flag = 1;
		while(flag)
		{
			if(retval >= ceil(temp))
			{
				flag = delete_at_index(&oxygen, '0', j, &len1s);
			}
			else
			{
				flag = delete_at_index(&oxygen, '1', j, &len1s);
			}
		}
	}
	
	for(j = 0; j < INPUT_SIZE && len0s != 1; ++j)
	{
		float temp = len0s / 2.0f;
		u32 retval = count_ones_at_index(co2, j);

		flag = 1;
		while(flag)
		{
			if(retval >= ceil(temp))
			{
				flag = delete_at_index(&co2, '1', j, &len0s);
			}
			else
			{
				flag = delete_at_index(&co2, '0', j, &len0s);
			}
		}
	}
	
	u32 result[2] = {0, 0};
	
	for(j = 0; j < INPUT_SIZE; ++j)
	{
		result[0] = (result[0] << 1) + (oxygen->str[j] - '0');
		result[1] = (result[1] << 1) + (co2->str[j] - '0');
	}
	
	fprintf(stdout, "%d\n", result[0] * result[1]);
	
	fclose(file);
	return 0;
}

char delete_at_index(node **head, char key, u8 index, u32 *len)
{
	node *temp = *head, *prev;
	
	if(temp != NULL && temp->str[index] == key)
	{
		*head = temp->next;
		free(temp);
		--(*len);
		return 1;
	}
	
	while(temp != NULL && temp->str[index] != key)
	{
		prev = temp;
		temp = temp->next;
	}
	
	if(temp == NULL)
		return 0;
	
	prev->next = temp->next;
	free(temp);
	--(*len);
	return 1;
}

void append(node *head, char *value)
{
	node *temp = head;
	
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = (node*) malloc(sizeof(node));
	strcpy(temp->next->str, value);
	temp->next->next = NULL;
}

u32 count_ones_at_index(node *head, u8 index)
{
	u32 count1s = 0;
	while(head != NULL)
	{
		count1s += (head->str[index] - '0');
		head = head->next;
	}
	return count1s;
}