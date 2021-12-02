#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
    FILE *file;
    uint32_t next, prev, count = 0;

    file = fopen("input.txt", "r");

    if(file == NULL)
    {
        fprintf(stdout, "Error opening file!\n");
        exit(1);
    }

    fscanf(file, "%d", &prev);
    while(!feof(file))
    {
        fscanf(file, "%d", &next);

        if(next > prev)
            ++count;

        prev = next;
    }

    fprintf(stdout, "%d", count);

    fclose(file);
    return 0;
}
