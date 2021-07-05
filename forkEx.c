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
   int fd;
   int i = 3;
   pid_t pid;
   char buff[BUFF_SIZE];
   int rdByte;

   // file descriptor table
   // 프로세스의 생성과 함께 시스템에서 
   // 자동으로 장치를 열어준다.
   // 0 : stdin, 1:stdout, 2:stderr
   // 다음으로 낮은값으로 open시 번호를 할당 -> 3
   fd = open("a.txt",O_RDONLY);

   if(fd==-1)
   {
       printf("Can't open\n");
       return 0;       
   }

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
       printf("i=%d\n", i);
       rdByte = read(fd, buff, BUFF_SIZE);
       if(rdByte<0)
	  printf("Can't read file\n");
       else
	  printf("read:%s\n",buff);
      // wait(&status);
   }
   // 자식 프로세스
   else
   {
       sleep(1);
       printf("자식 Proc %d\n", getpid());
       printf("i=%d\n", i);
       printf("fd=%d\n",fd);
       rdByte = read(fd, buff, BUFF_SIZE);
       if(rdByte<0)
          printf("Can't read file\n");
       else
          printf("read:%s\n",buff);



   }

   return 0;

}
