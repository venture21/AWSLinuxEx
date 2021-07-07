#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ./killTx [signal번호] [pid]
// argc = 3
// argv[1] => signal Number
// argv[2] => pid
// "--help" : 사용방법 안내 
int main(int argc, char *argv[])
{
    int result;
    int sigNum;
    pid_t pid;

    // 인자값의 갯수가 3개가 아니거나 "./killTx --help"
    if(argc !=3 || strcmp(argv[1], "--help")==0)
	    printf("%s pid sig-num\n", argv[0]);

    // pid를 숫자로 변환
    pid = atoi(argv[2]);
    sigNum = atoi(argv[1]);
    //내가 보내고자하는 프로세스에게 시그널을 전달(발생)
    result = kill(pid, sigNum);
    if(result!=0)
    {
        printf("Error:system call kill()\n");
    }
    else
    {
        printf("시그널이 정상적으로 전달되었습니다.\n");
    }

    return 0;
}