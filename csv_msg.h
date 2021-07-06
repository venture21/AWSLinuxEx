#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



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
    int  endFlag;
};

#define KEY_VALUE 0x1234
