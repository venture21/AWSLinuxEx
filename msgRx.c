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
    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
    // 메시지큐가 생성되지X
    if(msgid==-1)
    {
        fprintf(stderr,"msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);
    }

}
