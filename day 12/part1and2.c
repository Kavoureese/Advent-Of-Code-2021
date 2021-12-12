#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define BUF_LEN 10
#define VERTICES 16

char adjacency[VERTICES*VERTICES] = {0};
char visited[VERTICES] = {0};
char verts[VERTICES][6];
uint8_t g_vert_size = 0;
uint8_t g_start_index, g_end_index;

uint8_t vert_index(char*);
void DFSpart1(uint8_t, uint64_t *);
void DFSpart2(uint8_t, char, uint64_t *);

int main(void)
{
	FILE *file;
	char buf[BUF_LEN], *token;
	uint8_t i, j;
	uint64_t count = 0;
	
	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error printing file\n");
		exit(1);
	}
	
	while(fgets(buf, BUF_LEN, file) != NULL)
	{
		uint8_t temp = strlen(buf);
		if(!(buf[temp - 1] >= 'a' && buf[temp - 1] <= 'z') &&
		   !(buf[temp - 1] >= 'A' && buf[temp - 1] <= 'Z') &&
		   !(buf[temp - 1] >= '0' && buf[temp - 1] <= '9'))
		{
			buf[temp - 1] = '\0';
		}
		
		token = strtok(buf, "-");
		uint8_t a = vert_index(token);
		token = strtok(NULL, "-");
		uint8_t b = vert_index(token);
		
		adjacency[a*VERTICES + b] = 1;
		adjacency[b*VERTICES + a] = 1;
	}
	fclose(file);
	
	g_start_index = vert_index("start");
	g_end_index = vert_index("end");
	
	visited[g_start_index] = 1;
	DFSpart2(g_start_index, 0, &count);
	
	fprintf(stdout, "Part 2: %llu\n", count);
	
	return 0;
}

uint8_t vert_index(char *str)
{
	uint8_t i;
	
	for(i = 0; i < g_vert_size; ++i)
		if(strcmp(str, verts[i]) == 0)
			return i;
	
	strcpy(verts[g_vert_size], str);
	return g_vert_size++;
}

void DFSpart1(uint8_t cur_ind, uint64_t *count)
{
	if(cur_ind == g_end_index)
	{
		(*count)++;
		return;
	}
	
	uint8_t i;
	for(i = 0; i < g_vert_size; ++i)
	{
		if(adjacency[cur_ind*VERTICES + i] && !visited[i])
		{
			if(!(verts[i][0] >= 'A' && verts[i][0] <= 'Z'))
				visited[i] = 1;
			
			DFSpart1(i, count);
			visited[i] = 0;
		}
	}
}

void DFSpart2(uint8_t cur_ind, char twice, uint64_t *count)
{
	if(cur_ind == g_end_index)
	{
		(*count)++;
		return;
	}
	
	uint8_t i;
	for(i = 0; i < g_vert_size; ++i)
	{
		if(adjacency[cur_ind*VERTICES + i])
		{
			if(verts[i][0] >= 'A' && verts[i][0] <= 'Z')
				DFSpart2(i, twice, count);
			else if(!visited[i])
			{
				visited[i] = 1;
				DFSpart2(i, twice, count);
				visited[i] = 0;
			}
			else if(!twice && i != g_start_index)
				DFSpart2(i, 1, count);
		}
	}
}