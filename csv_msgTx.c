#include "csv_msg.h"

//#define DEBUG

int main(void)
{
    char buff[30];
    int running=1;
    char *pState;
    char *ptr;
    int msgid;

    //구조체 객체 선언
    struct Data st;

    //구조체 객체 초기화
    memset(&st, 0, sizeof(st));

    // test.csv파일을 생성한다. write mode(text)
    FILE *fp = fopen("test.csv", "r");

    // STEP 1. 메시지큐 생성
    msgid = msgget((key_t)KEY_VALUE, 0666 | IPC_CREAT);
    if(msgid==-1)
    {
        fprintf(stderr,"msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);

    }
    while(running)
    {
        // read csv
        pState = fgets(buff, sizeof(buff), fp);
        if(pState==NULL)
        {
            //running=0;
            break;
        }

        // strtok : 문자열에서 ','를 기준으로 token으로 나누어준다.
        ptr = strtok(buff,",");
        strcpy(&st.name, ptr);
        ptr = strtok(NULL,",");
        st.kor = atoi(ptr);
        ptr = strtok(NULL,",");
        st.eng = atoi(ptr);
        ptr = strtok(NULL,",");
        st.math = atoi(ptr);
        ptr = strtok(NULL,",");
        st.scien = atoi(ptr);
        st.endFlag = 0;

#ifdef DEBUG
        printf("name=%s\n",&st.name);
        printf("kor=%d\n",st.kor);
        printf("eng=%d\n",st.eng);
        printf("math=%d\n",st.math);
        printf("scien=%d\n",st.scien);
#endif 

        st.msg_type = 1;
        //STEP 2. 메시지큐에 보내기
        if(msgsnd(msgid, (void*)&st, sizeof(st), 0)==-1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
    }
 
    // 마지막 데이터를 보내는 구조체는 endFlag=1로 설정한다. 
    // 구조체 초기화
    memset(&st, 0, sizeof(st));
    st.msg_type = 1;
    st.endFlag = 1;
    if(msgsnd(msgid, (void*)&st, sizeof(st), 0)==-1)
    {
        fprintf(stderr, "msgsnd failed\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
