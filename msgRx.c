#include "msg.h"

int main(void)
{
    // 구조체 객체 선언
    struct my_msg_st some_data;
    int msgid;
    // 전송할 데이터가 있느냐?
    int running=1;
    char buffer[BUFSIZ];

    // STEP 1. 메시지큐 생성
    msgid = msgget((key_t)0x1234, 0666|IPC_CREAT);
    // 메시지큐가 생성되지X
    if(msgid==-1)
    {
        fprintf(stderr,"msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(running)
    {
        // 정상적으로 메시지큐를 읽지 못한 경우
        if(msgrcv(msgid, (void*)&some_data, BUFSIZ, 0, 0)==-1)
        {
            fprintf(stderr,"msgrcv failed with error:%d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Receive:%s", some_data.some_text);

        if (strncmp(some_data.some_text,"end",3)==0)
        {
            running=0;
        }
    }

    //메시지큐 수신 프로세스에서 메시지큐를 삭제
    if(msgctl(msgid, IPC_RMID, 0)==-1)
    {
        fprintf(stderr,"msgctl(IPC_RMID) failed:%d\n", errno);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
