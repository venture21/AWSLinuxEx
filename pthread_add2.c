#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h> // getimeofday( ) 함수에서 사용

#define DEBUG

struct value {
    int start;
    int end;
    long result;
};


long adder(int start, int end)
{
	int i;
	long result=0;

	for(i = start ;i<=end; i++)
	{
		result += i;
	}

	return result;
}

// 스레드 함수를 생성할때 
// 리턴값은 void*
// 넘겨 받는 인수도 void*
void* add_func(void* data)
{
	int i;
	struct value *value;
	pthread_t t_id; 
    value = ((struct value *)data);



	for(i=value->start;i<value->end+1;i++)
	{
		value->result += i;
	}

#ifdef DEBUG
    //printf("start = %d\n", value.start);
	//printf("end = %d\n", value.end);
	//printf("result = %ld\n", value->result);
#endif

	return (void *)(0);
}

void disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
{
	struct timeval UTCtime_r;
	if((UTCtime_e.tv_usec- UTCtime_s.tv_usec)<0)
	{
		UTCtime_r.tv_sec  = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
		UTCtime_r.tv_usec = 1000000 + UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	else
	{
		UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
		UTCtime_r.tv_usec = UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	printf("runtime : %ld sec %ld\n", UTCtime_r.tv_sec, UTCtime_r.tv_usec);
}

// 
int main(int argc, char *argv[])
{
	pthread_t p_thread[2];
	int thread_num, start, end;
	int err;
	long result;
	struct value *value1,*value2;
    struct timeval UTCtime_s, UTCtime_e, UTCtime_r;

    if(argc!=4)
    {
        printf("USAGE : ./pthread_add [thread갯수] [시작값] [종료값]\n");
        return 0;
    }

    thread_num = atoi(argv[1]); 
    start = atoi(argv[2]);
    end = atoi(argv[3]);
	
    value1 = malloc(sizeof(struct value));
    value2 = malloc(sizeof(struct value));

	switch(thread_num)
	{
		case 1: 
                gettimeofday(&UTCtime_s, NULL);
				result = adder(start, end);
                gettimeofday(&UTCtime_e, NULL);
                disp_runtime(UTCtime_s, UTCtime_e);
				printf("1 thread result = %ld\n", result); 
				break;

		case 2: value1->start = start;
				value1->end   = end>>1;
				value2->start = (value1->end)+1;
				value2->end   = end;

                gettimeofday(&UTCtime_s, NULL);
    			if((err = pthread_create(&p_thread[0], NULL, add_func, (void*)value1)) < 0)
			    {
					perror("thread create error : "); 
					exit(1);
				}

				if((err = pthread_create (&p_thread[1], NULL, add_func, (void*)value2)) < 0)
				{
					perror("thread create error : ");
				    exit(2);
				}

				pthread_join(p_thread[0], (void **)&err);
				//printf("pthread1 is done!: %d\n", err);
				pthread_join(p_thread[1], (void **)&err);
				//printf("pthread2 is done!: %d\n", err);
				result = value1->result + value2->result;
                gettimeofday(&UTCtime_e, NULL);
                disp_runtime(UTCtime_s, UTCtime_e);
                //printf("value1.result=%lld, value2.result=%lld\n",value1->result, value2->result);
				printf("2 thread result = %ld\n", result); 
				break;
		default:
				printf("parameter error\n");
	}

	return 0;
}
