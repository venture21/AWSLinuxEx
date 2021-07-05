// ****************************************************
// 과제 : 프로세스를 1개를 추가로 만들어서
// 메인 프로그램에서는 1~100000까지를 더하고
// popen  100001~200000 더하는 프로그램을 불러와서 실행 
// 결과값 메시지 출력을 통해 전달받고 메인프로그램에서 
// 1~200000의 더한값을 출력
//
// 사용 함수 : popen(), atoi()
// ****************************************************

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long adder(int sValue, int eValue)
{
    int i;
    long result;
    result =0;
    for(i=sValue;i<eValue+1;i++)
    {
        result +=i;
    }
    printf("result=%ld\n",result);

    return result;
}

int main(void)
{
    FILE *read_fp;
    int chars_read;
    long result1, result2, result;
    char buffer[BUFSIZ +1]; //초기화되지x
    //printf("BUFSIZ=%d\n",BUFSIZ);
    // buffer를 buffer 사이즈만큼 '\0'로 초기화
    memset(buffer,'\0', sizeof(buffer));
    // popen은 터미널프로세스 + "ls -al"
    // 출력되는 문자열 -> read_fp로 리턴
    read_fp = popen("./popenAdderSub 100001, 200000","r");
    result1 = adder(1, 100000);

    // popen이 정상적으로 실행된 경우
    if (read_fp!=NULL)
    {
            // buffer에 저장, 1바이트단위로, 최대 BUFSIZ, 
            // read_fp로부터 읽어서
            // return인 chars_read는 읽어온 바이트 수
            chars_read = fread(buffer,sizeof(char), BUFSIZ, read_fp);
            if (chars_read>0)
            {
                result2 = atol(buffer);
            }
            
            pclose(read_fp);
            result = result1 + result2;
            printf("%ld+%ld=%ld\n",result1, result2, result); 
            exit(0);
    }
    else
    {
        exit(-1);
    }
}
