#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    FILE *read_fp;
    int chars_read;
    char buffer[BUFSIZ +1]; //초기화되지x
    //printf("BUFSIZ=%d\n",BUFSIZ);
    // buffer를 buffer 사이즈만큼 '\0'로 초기화
    memset(buffer,'\0', sizeof(buffer));
    // popen은 터미널프로세스 + "ls -al"
    // 출력되는 문자열 -> read_fp로 리턴
    read_fp = popen("ls -al","r");

    // popen이 정상적으로 실행된 경우
    if (read_fp!=NULL)
    {
            // buffer에 저장, 1바이트단위로, 최대 BUFSIZ, 
            // read_fp로부터 읽어서
            // return인 chars_read는 읽어온 바이트 수
            chars_read = fread(buffer,sizeof(char), BUFSIZ, read_fp);
            if (chars_read>0)
            {
                printf("out:\n%s\n", buffer);
            }
            
            pclose(read_fp);
            exit(0);
    }
    else
    {
        exit(-1);
    }
}
