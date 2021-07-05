#include <stdio.h>  //printf
#include <unistd.h> //pid_t
#include <stdlib.h> // 문자열처리
#include <sys/types.h> // wait()
#include <sys/wait.h>  // wait()


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
    }
    // 자식 Proc인 경우
    else
    {
        printf("자식 Proc : 내 PID=%d\n", getpid());
        //execl("/bin/ls", "ls", "-al", NULL);
        //execl("/bin/test","test",NULL);
        execl("/usr/bin/python","python","hello.py",NULL);
    }

    wait(&status);
	
    return 0;

}
