#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
    //환경변수에 MYDIR, USER_FOLDER라는 것을 추가
    setenv("MYDIR2","/home/park", 0);
    setenv("USR_FOLDER","/usr",0);

    //환경변수가 잘 설정되었는지 확인
    printf("MYDIR=%s\n", getenv("MYDIR2"));
    printf("USR_FOLDER=%s\n",getenv("USR_FOLDER"));

    return 0;
}
