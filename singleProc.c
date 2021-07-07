
#include <stdio.h>

int main(void)
{
    long i;
    long result;

    result =0;

    for(i=1;i<=2000000000;i++)
    {
        result+=i;
    }

    printf("result=%ld\n",result);
    return 0;
}