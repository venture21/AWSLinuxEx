#include <stdio.h>   // printf()
#include <unistd.h>  // pid_t, getpid(), sleep()

int main(void)
{
    pid_t pid, ppid;
    pid = getpid(); //현재 자신의 프로세스 ID를 읽어온다.
    ppid = getppid(); //자신의 부모프로세스 ID를 읽어온다.
    printf("my pid=%d\n",pid);
    printf("my ppid=%d\n", ppid);
    sleep(10);   

}




