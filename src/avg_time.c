#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *result_path = "~comp428/a1/out/averages.txt";

int file_average(char *path);
size_t length(int x);
char* to_string(int x);
char* pad_string(char* string, size_t length);
char* to_padded_string(int x, size_t length);
char* out_path(int x);
int avg_result(int p);
void print_out(FILE *file, int p);

int main(int argc, char* argv[])
{
    FILE *file = fopen(result_path, "w");
    fprintf(file, "Processes\t\tAverage Time\n");
    fprintf(file, "=============================\n");
    int p = 1;
    print_out(file, p);
    for(p = 2; p <= 20; p += 2)
    {
        print_out(file, p);
    }

    return 0;
}

int file_average(char *path)
{
    FILE *file = fopen(path, "r");
    int i = 0;
    int total = 0;
    int count = 0;
    while (!feof(file))
    {
        fscanf(file, "%d", &i);
        if (feof(file))
            break;
        total += i;
        count++;
    }

    return total / count;
}

size_t length(int x)
{
    return snprintf(NULL, 0, "%d", x);
}

char* to_string(int x)
{
    char *string = malloc(sizeof(char) * length(x));
    sprintf(string, "%d", x);
    return string;
}

char* pad_string(char* string, size_t new_length)
{
    size_t length = strlen(string);
    char *padded_string;
    if (new_length > length)
    {
        padded_string = malloc(sizeof(char) * (new_length + 1));
        int count = new_length - length;
        char *padding = malloc(sizeof(char) * (count + 1));
        while (count > 0)
        {
            strcat(padding, "0");
            count--;
        }
        strcat(padded_string, padding);
        strcat(padded_string, string);
    }
    else
    {
        padded_string = string;
    }

    return padded_string;
}

char* to_padded_string(int x, size_t length)
{
    return pad_string(to_string(x), length);
}

int avg_result(int p)
{
    return file_average(out_path(p));
}

char* out_path(int x)
{
    const char *prefix = "~comp428/a1/out/out";
    const char *suffix = ".txt";
    const size_t length = strlen(prefix) + 2 + strlen(suffix);
    
    char *path = malloc(sizeof(char) * (length + 1));
    strcat(path, prefix);
    strcat(path, to_padded_string(x, 2));
    strcat(path, suffix);
    
    return path;
}

void print_out(FILE *file, int p)
{
    fprintf(file, "%d\t\t%d\n", p, avg_result(p));
}

