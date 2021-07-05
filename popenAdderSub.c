#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
    int i;
    int sValue, eValue;
    long result;
    // 시작값과 종료값을 확인
    if(argc !=3)
    {
        fprintf(stderr,"popenAdderSub 시작값,종료값\n");
        return 1;
    }

    sValue = atoi(argv[1]);
    eValue = atoi(argv[2]);

    result =0;
    for(i=sValue;i<eValue+1;i++)
    {
        result +=i;
    }
    printf("%ld\n",result);
}
