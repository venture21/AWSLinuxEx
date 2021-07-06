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
    char buff[30];
    //구조체 객체 선언
    struct Data st;

    //구조체 객체 초기화
    memset(&st, 0, sizeof(st));

    // test.csv파일을 생성한다. write mode(text)
    FILE *fp = fopen("test.csv", "r");

    // read csv
    fgets(buff, sizeof(buff), fp);

    // strtok : 문자열에서 ','를 기준으로 token으로 나누어준다.
    char *ptr = strtok(buff,",");
    strcpy(&st.name, ptr);
    ptr = strtok(NULL,",");
    st.kor = atoi(ptr);
    ptr = strtok(NULL,",");
    st.eng = atoi(ptr);
    ptr = strtok(NULL,",");
    st.math = atoi(ptr);
    ptr = strtok(NULL,",");
    st.scien = atoi(ptr);

    printf("name=%s\n",&st.name);
    printf("kor=%d\n",st.kor);
    printf("eng=%d\n",st.eng);
    printf("math=%d\n",st.math);
    printf("scien=%d\n",st.scien);

    
    return 0;
}
