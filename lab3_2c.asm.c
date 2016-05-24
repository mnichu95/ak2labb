unsigned long long rdtsc(void);   # deklaracja funcj
#include <stdio.h>

int main(void)
{
    unsigned long long tc = rdtsc();
    printf("%llu",tc);
    return 0;
}

