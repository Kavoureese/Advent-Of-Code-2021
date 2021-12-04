#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#define INPUT_LEN 100
#define NUM_OF_BOARDS 100

typedef uint8_t u8;
typedef uint16_t u16;

u8 order[INPUT_LEN];
u8 *buffer;
u8 winning_num;
bool *checks;
bool winner_flag = false;
bool winner_order[NUM_OF_BOARDS] = {false};
u8 win_count = NUM_OF_BOARDS;
u8 last_winner;

void find_num(u16 start, u16 end, u8 key);
bool check_for_bingo(u16 start, u16 end, u8 key, u8 board);

u16 sum_winner_board(u8 board);

int main(void)
{
    FILE *file;
    u16 i, bingo;
	buffer = (u8*) malloc((5*5*NUM_OF_BOARDS)*sizeof(u8));
	checks = (bool*) malloc((5*5*NUM_OF_BOARDS)*sizeof(bool));
	
	for(i = 0; i < 5*5*NUM_OF_BOARDS; ++i)
		checks[i] = false;
	
	file = fopen("input.txt", "r");

    if(file == NULL)
    {
        fprintf(stdout, "Error opening file!\n");
        exit(1);
    }

    // Read number order
    i = 0;
    while(!feof(file))
    {
        fscanf(file, "%hhu,", &order[i]);
		++i;
        if(i == INPUT_LEN)
            break;
    }
	
	// Read boards
    i = 0;
    while(!feof(file))
    {
        fscanf(file, "%hhu", &buffer[i]);
		++i;
    }
	fclose(file);
	
	// Simulate bingo
	for(bingo = 0; bingo < INPUT_LEN && win_count != 0; ++bingo)
	{
		for(i = 0; i < NUM_OF_BOARDS; ++i)
		{
			find_num(i*25, i*25+25, order[bingo]);
		}
		
		for(i = 0; i < NUM_OF_BOARDS; ++i)
		{
			winner_flag = check_for_bingo(i*25, i*25+25, order[bingo], i);
		}
	}
	
	printf("%d\n", sum_winner_board(last_winner) * winning_num);

    return 0;
}

void find_num(u16 start, u16 end, u8 key)
{
	u16 i;
	for(i = start; i < end; ++i)
	{
		if(buffer[i] == key)
		{
			checks[i] = true;
			return;
		}
	}
}

bool check_for_bingo(u16 start, u16 end, u8 key, u8 board)
{
	u8 i;
	
	// check horizontal
	for(i = 0; i < 5; ++i)
	{
		bool is_winner = checks[board*25 + 5*i] &&
						 checks[board*25 + 5*i + 1] &&
						 checks[board*25 + 5*i + 2] &&
						 checks[board*25 + 5*i + 3] &&
						 checks[board*25 + 5*i + 4];
		
		if(is_winner)
		{
			if(winner_order[board] == false)
			{
				--win_count;
				if(win_count == 0)
				{
					last_winner = board;
					winning_num = key;
				}
			}
			 
			winner_order[board] = true;
			return true;
		}
	}
	
	//check vertical
	for(i = 0; i < 5; ++i)
	{
		bool is_winner = checks[board*25 + i] &&
						 checks[board*25 + i + 5] &&
						 checks[board*25 + i + 10] &&
						 checks[board*25 + i + 15] &&
						 checks[board*25 + i + 20];
			
		if(is_winner)
		{
			if(winner_order[board] == false)
			{
				--win_count;
				if(win_count == 0)
				{
					last_winner = board;
					winning_num = key;
				}
			}
			 
			winner_order[board] = true;
			return true;
		}
	}
	
	return false;
}

u16 sum_winner_board(u8 board)
{
	u8 i, j;
	u16 sum = 0;
	
	for(i = 0; i < 5; ++i)
	{
		for(j = 0; j < 5; ++j)
		{
			if(!checks[board*25 + i*5 + j])
				sum += buffer[board*25 + i*5 + j];
		}
	}
	return sum;
}