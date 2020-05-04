#include <stdio.h>
int main()
{
    short a = 10;
    int b = 100;
   
    int short_length = sizeof a;
    int int_length = sizeof(b);
    int long_length = sizeof(long);
    int char_length = sizeof(char);
   
    printf("short=%d, int=%d, long=%d, char=%d\n", short_length, int_length, long_length, char_length);
   
    return 0;
}