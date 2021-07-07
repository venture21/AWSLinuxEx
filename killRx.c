#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigHandler(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    (void)signal(SIGINT, SIG_DFL);
}

int main(void)
{
    // signal을 활용하기 위해서는
    // signal과 핸들러를 정의해야 한다.
    // SIGINT라는 시그널이 들어오면, sigHandler()로
    // 점프해서 이동해라.(=>커널에 등록)
    signal(SIGINT, sigHandler);
    //signal(SIGINT, SIG_DFL);

    while(1){
        printf("Hello World!\n");
        sleep(1);
    }
}