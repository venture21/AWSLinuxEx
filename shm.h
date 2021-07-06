#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//공유메모리 공간 100개 
// sizeof(int)*SHMSIZE => 400 btyes
#define SHMSIZE 100
#define KeyValue 0x1234
