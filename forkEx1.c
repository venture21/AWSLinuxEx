#include <stdio.h>  //printf
#include <unistd.h> //pid_t
#include <stdlib.h> // 문자열처리
#include <sys/types.h> // wait()
#include <sys/wait.h>  // wait()
#include <fcntl.h>     // open(), read()

#define BUFF_SIZE 1024

int main(void)
{
   int status;
   pid_t pid;

   pid = fork();

   // fork()가 정상적으로 실행되지 않은경우
   if(pid<0)
   {
       printf("Can't create child process\n");
       return 0;
   }

   // 부모 프로세스
   else if(pid>0)
   {
       printf("부모 Proc %d : %d\n", getpid(), pid);
       wait(&status);
   }
   // 자식 프로세스
   else
   {
       sleep(1);
       printf("자식 Proc %d\n", getpid());
   }

   return 0;

}
