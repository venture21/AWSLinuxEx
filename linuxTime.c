#include <time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/wait.h>

#define SHMCOUNT 1
#define SHMSIZE  sizeof(long)*SHMCOUNT
#define KEY_VALUE	(key_t)1234


void singleProcAdder(int startValue,int endValue)
{
	clock_t start_point, end_point;
	int i;
	long sum=0;

	// 시작 시간 기록
	start_point = clock();

	for(i=startValue;i<=endValue;i++)
		sum +=i;
		
	// 종료 시간 기록
	end_point = clock();

	printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
	printf("Result Value : %ld\n", sum); 
}


void multiProcAdder(int startValue,int endValue)
{
	int i;
	long sum=0;

	clock_t start_point, end_point;
	pid_t pid;

	int shmid;
	void *shared_Mem=(void*)0;
	long *shmaddr;

	pid = fork();
	if(pid==-1)
	{
		printf("Error:fork()\n");
		exit(-2);
	}

	// step 1. shmget()
	shmid = shmget(KEY_VALUE, SHMSIZE, 0666 | IPC_CREAT);

	// 공유메모리가 할당되지 않은 경우
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed with error\n");
		exit(EXIT_FAILURE);
	}

	// step 2. shmat()
	shared_Mem = shmat(shmid, (void*)0, 0);
	
	// shmat가 실패한 경우
	if(shared_Mem==(void*)-1)
	{
		fprintf(stderr,"shmat failed with error\n");
		exit(EXIT_FAILURE);
	}

	//shmat가 성공한 경우, 할당된 메모리 번지를 확인
	//printf("Memory attatch at 0x%p\n", shared_Mem);
	shmaddr = (long*)shared_Mem;
	
	if(pid>0)
	{
		// 시작 시간 기록
		start_point = clock();

		for(i=startValue;i<=(endValue>>1);i++)
			sum+=i;

		wait(NULL);
		sum +=*shmaddr;
		printf("Result Value : %ld\n", sum);
			
		// 종료 시간 기록
		end_point = clock();

		printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));

		// step 4. shmdt()
		if(shmdt(shared_Mem)==-1)
		{
			fprintf(stderr,"shmdt failed with error\n");
			exit(EXIT_FAILURE);
		}

		// step 5. shmctl (IPC_RMID)
		if(shmctl(shmid, IPC_RMID, 0)==-1)
		{
			fprintf(stderr,"shmctl failed with error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		for(i=(endValue>>1)+1;i<=endValue;i++)
		{
			sum+=i;
		}
		*shmaddr=sum;
		
		// step 4. shmdt()
		if(shmdt(shared_Mem)==-1)
		{
			fprintf(stderr,"shmdt failed with error\n");
			exit(EXIT_FAILURE);
		}
		exit(0);			
	}
}


int main(int argc, char *argv[])
{
	int startValue, endValue;
	int procNum;

	if(argc!=4)
	{
		printf("Usgae :  ./linuxTime [process_num] [startValue] [EndValue]\n");
		exit(-1);
	}
	procNum = atoi(argv[1]);
	startValue = atoi(argv[2]);
	endValue = atoi(argv[3]);

	if(procNum==1)
		singleProcAdder(startValue,endValue);
	else
		multiProcAdder(startValue,endValue);

}