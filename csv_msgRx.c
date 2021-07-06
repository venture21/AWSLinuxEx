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

    // STEP 1. 메시지큐 생성
    msgid = msgget((key_t)KEY_VALUE, 0666 | IPC_CREAT);
    if(msgid==-1)
    {
        fprintf(stderr,"msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);
    }

    // result.csv파일을 생성한다. write mode(text)
    FILE *fp = fopen("result.csv", "w");

    while(running)
    {

        // 정상적으로 메시지큐를 읽지 못한 경우
        if(msgrcv(msgid, (void*)&st, sizeof(st), 0, 0)==-1)
        {
            fprintf(stderr,"msgrcv failed with error:%d\n", errno);
            exit(EXIT_FAILURE);
        }

        if(st.endFlag==1)
        {
            //running=0;
            break;
        }

        st.total = st.kor+st.eng+st.math+st.scien;
        st.avg = (st.total/4);
#ifdef DEBUG
        printf("name=%s\n",&st.name);
        printf("kor=%d\n",st.kor);
        printf("eng=%d\n",st.eng);
        printf("math=%d\n",st.math);
        printf("scien=%d\n",st.scien);
        printf("avg=%d\n",st.avg);
        printf("total=%d\n",st.total);
#endif
    
        fprintf(fp, "%s, %d, %d, %d, %d, %d, %d\n",
            st.name,st.kor,st.eng,st.math,st.scien,st.avg,st.total);      
    }

    //메시지큐 수신 프로세스에서 메시지큐를 삭제
    if(msgctl(msgid, IPC_RMID, 0)==-1)
    {
        fprintf(stderr,"msgctl(IPC_RMID) failed:%d\n", errno);
        exit(EXIT_FAILURE);
    }


    exit(EXIT_SUCCESS);
}
