#include "shm.h"

int main(void)
{
    // 공유메모리 주소값을 가리키는 포인터
    // (void*)0 : NULL포인터로 초기화
    void *shared_Mem=(void*)0;
    int i;

    //실제 공유메모리 접근시 int포인터로 사용하기 위해
    int *shmaddr;
    int shmid;
    // step 1. shmget   400bytes
    shmid = shmget((key_t) 0x1234, sizeof(int)*SHMSIZE, 0666|IPC_CREAT);
    // 정상적으로 공유메모리 할당X
    if(shmid==-1)
    {
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
    }

    // step 2. shmat
    // (void*)0 -> 특정 주소값으로 할당하기 원하는 경우 주소값을 설정하는 인자(NULL)
    shared_Mem = shmat(shmid, (void*)0, 0);
    // 공유메모리가 할당되지 못하는 경우는 (void*)로 -1이 리턴된다.
    if(shared_Mem==(void*)-1)
    {
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);        
    }

	printf("Memory attached at 0x%p\n",shared_Mem);
 	shmaddr = (int*)shared_Mem;

    // step 3. memory access (0x0000001 ~ 0x00000100)
	for(i=0;i<SHMSIZE;i++)
	{
		*(shmaddr+i)=i+1;
		printf("shmaddr:%p, data:%d\n", shmaddr+i,*(shmaddr+i));
	}

    // step 4. shmdt
	if(shmdt(shared_Mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

    // step 5. shmctl(IPC_RMID) -> shmReader.c
    // 이 코드에서는 shmctl을 실행하지 않음
    exit(EXIT_SUCCESS);
}