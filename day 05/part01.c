#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef struct vector2_i {u16 a; u16 b;} v2i;
typedef struct struct_vent {v2i start; v2i end;} vent;

static inline u8 count_digits(u16);
static inline u16 power(u16 base, u16 exp)
	{u16 i; for(i = 1; i < exp; ++i) base*=10; return base;}
static inline void swap(u16 *a, u16 *b)
	{u16 temp = *a; *a = *b; *b = temp;}

int main(void)
{
	FILE *file;
	u16 input_len = 0, max;
	u32 i, j;
	char buf[25];

	file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}

	// Count lines
	while((i = getc(file)) != EOF)
		input_len = input_len + (i == '\n');
    fclose(file);

	vent *buffer = (vent*) malloc(sizeof(vent)*input_len);
	if(buffer == NULL)
    {
        fprintf(stdout, "Failed allocation!\n");
        exit(1);
    }

    file = fopen("input.txt", "r");
	if(file == NULL)
	{
		fprintf(stdout, "Error opening file!\n");
		exit(1);
	}

	// Get input
	i = 0;
	max = 0;
	while(fgets(buf, 25, file) != NULL)
	{
		vent temp;
		if(sscanf(buf, "%hu,%hu -> %hu,%hu", &temp.start.a, &temp.start.b,
                                              &temp.end.a, &temp.end.b) == 4)
		{

			buffer[i] = temp;

			if(temp.start.a > max)
				max = temp.start.a;

			if(temp.start.b > max)
				max = temp.start.b;

			if(temp.end.a > max)
				max = temp.end.a;

			if(temp.end.b > max)
				max = temp.end.b;

			++i;
		}
	}

	fclose(file);

	u32 size = power(10, count_digits(max));
	u16 *diagram = (u16*) malloc(sizeof(u16)*size*size);
	if(diagram == NULL)
    {
        fprintf(stdout, "Failed allocation!\n");
        exit(1);
    }

	// init diagram
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			diagram[i*size + j] = 0;

	// map vents on diagram
	for(i = 0; i < input_len; ++i)
	{
		if(buffer[i].start.a != buffer[i].end.a && buffer[i].start.b != buffer[i].end.b)
			continue;

		u16 start, end;

		if(buffer[i].start.a == buffer[i].end.a)
		{
			start = buffer[i].start.b;
			end = buffer[i].end.b;

			if(buffer[i].start.b > buffer[i].end.b)
				swap(&start, &end);

			for(j = start; j <= end; ++j)
				++diagram[j*size + buffer[i].start.a];
		}
		else
		{
            start = buffer[i].start.a;
			end = buffer[i].end.a;

			if(buffer[i].start.a > buffer[i].end.a)
                swap(&start, &end);

            for(j = start; j <= end; ++j)
                ++diagram[buffer[i].start.b*size + j];
		}
	}

	u16 overlaps = 0;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			overlaps = overlaps + (diagram[i*size + j] > 1);

	fprintf(stdout, "%d\n", overlaps);

	return 0;
}

u8 count_digits(u16 num)
{
	u8 digits = 0;
	while(num != 0)
	{
		++digits;
		num /= 10;
	}
	return digits;
}
