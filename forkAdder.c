#include <stdio.h>  //printf
#include <unistd.h> //pid_t
#include <stdlib.h> // 문자열처리
#include <sys/types.h> // wait()
#include <sys/wait.h>  // wait()

int adder(int start, int end)
{
    int i=0, result=0;
    for(i=start;i<end+1;i++)
        result+=i;

    return result;
}


int main(void)
{
    int result; 
    int status;
    pid_t pid;
    pid = fork();

    // fork()가 정상적으로 실행되지 않은경우
    if(pid<0) 
    {
        printf("Can't create process!\n");
        return -1;
    }
    // 부모 Proc인 경우
    else if(pid>0)
    {
        printf("부모 Proc : 자식 PID=%d\n", pid);
        result = adder(1,100000);
        printf("부모 result=%d\n",result);
    }
    // 자식 Proc인 경우
    else
    {
        printf("자식 Proc : 내 PID=%d\n", getpid());
        result = adder(100001,200000);
        printf("자식 result=%d\n",result);

    }

    wait(&status);
	
    return 0;

}
