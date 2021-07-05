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
        printf("Enter some text:");
        //키보드로 입력받고,최대 BUFSIZ, buffer에 저장
        fgets(buffer,BUFSIZ, stdin);
        some_data.my_msg_type=1;
        //strcpy(dst,src)
        strcpy(some_data.some_text, buffer);
        // STEP 2. 메시지큐에 보내기
        // (void*)오직 주소값만(API에서 지정)
        // msgsnd의 리턴값이 -1이면 메시지큐에서 정상 전송X
        if(msgsnd(msgid, (void*)&some_data, MAX_TEXT, 0)==-1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer,"end",3)==0)
        {
            running=0;
        }
    }

    exit(EXIT_SUCCESS);

}
