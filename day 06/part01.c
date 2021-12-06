#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define NEW_TIME 6
#define SIMULATED_DAYS 13

typedef struct lantern_struct {u8 cur_time; struct lantern_struct *next;} lanfish;

void add_new_fish(lanfish*);
void print_children(lanfish*);
void check_children(lanfish*);
u32 count_children(lanfish*);

int main(void)
{
	FILE *file;
	u8 input_len = 1;
	u16 i, j;
	char buf[25], *token;
	lanfish *arr;

	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}
	
	fgets(buf, 25, file);
	fclose(file);
	for(i = 0; buf[i] != '\0'; ++i)
		if(buf[i] == ',')
			++input_len;
	
	arr = (lanfish*) malloc(sizeof(lanfish)*input_len);
	
	i = 0;
	token = strtok(buf, ",");
	while(token != NULL)
	{
		arr[i].cur_time = (u8) strtol(token,NULL,10);
		arr[i].next = NULL;
		token = strtok(NULL, ",");
		++i;
	}
	
	for(i = 0; i < SIMULATED_DAYS; ++i)
	{
		for(j = 0; j < input_len; ++j)
		{
			check_children(&arr[j]);
			if(arr[j].cur_time == 0)
			{
				add_new_fish(&arr[j]);
				arr[j].cur_time = NEW_TIME;
			}
			else
				--arr[j].cur_time;
		}
	}
	
	for(i = 0; i < input_len; ++i)
	{
		print_children(&arr[i]);
		printf("\n");
	}
	
	u32 total_pop = 0;
	for(i = 0; i < input_len; ++i)
		total_pop += count_children(&arr[i]);
	printf("Total pop: %d\n", total_pop);
	
	return 0;
}

void add_new_fish(lanfish *start)
{
	while(start->next != NULL)
		start = start->next;
	
	start->next = (lanfish*) malloc(sizeof(lanfish));
	start->next->cur_time = NEW_TIME + 2;
	start->next->next = NULL;
}

void print_children(lanfish *p)
{
	while(p != NULL)
	{
		printf("%hhu ", p->cur_time);
		p = p->next;
	}
}

void check_children(lanfish *p)
{
	p = p->next;
	
	while(p != NULL)
	{
		if(p->cur_time == 0)
		{
			add_new_fish(p);
			p->cur_time = NEW_TIME;
		}
		else
			--(p->cur_time);
		
		p = p->next;
	}
}

u32 count_children(lanfish *p)
{
	u32 pop = 0;
	while(p != NULL)
	{
		++pop;
		p = p->next;
	}
	return pop;
}

