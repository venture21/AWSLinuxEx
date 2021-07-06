#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data {
    // 메시지큐를 위한 선언
    long int msg_type;
    char name[10];
    int  kor;
    int  eng;
    int  math;
    int  scien;
    int  avg;
    int  total;
};

int main(void)
{
    char buff_in[10];
    //구조체 객체 선언
    struct Data st;

    //구조체 객체 초기화
    memset(&st, 0, sizeof(st));
    printf("sizeof(st)=%ld\n",sizeof(st));
    
    // input : name,kor,eng,math,scien
    printf("name:");
    scanf("%s", st.name);
    printf("kor:");
    scanf("%d", &st.kor);
    printf("eng:");
    scanf("%d", &st.eng);
    printf("math:");
    scanf("%d", &st.math);
    printf("scien:");
    scanf("%d", &st.scien);

    // test.csv파일을 생성한다. write mode(text)
    FILE *fp = fopen("test.csv", "a");
    // write csv
    fprintf(fp, "%s, %d, %d, %d, %d\n",
            st.name,st.kor,st.eng,st.math,st.scien);



    //printf("buff_in=%s \n",buff_in);
    
    return 0;
}
