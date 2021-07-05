#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];
int primes[] = {2,3,5,7};

int main(int argc, char *argv[])
{
    int test;
    int *ptest;
    *ptest = test;
    static int key = 9973;
    static char mbuf[10240000];
    char *p;
    p = malloc(1024);

    printf("test addr = 0x%x \n", ptest);
    printf("*p addr =0x%x \n", p);
    printf("globBuf addr=0x%x \n", globBuf);
    printf("primes[]=0x%x \n", primes);


}
