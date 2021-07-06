#include <stdio.h>
#include <unistd.h>
#include <sys/time.h> // getimeofday( ) 함수에서 사용
#include <stdlib.h>

struct value
{
	int start;
	int end;
};

void disp_runtime(struct timeval UTCtime_s, struct timeval UTCtime_e)
{
	struct timeval UTCtime_r;
	if((UTCtime_e.tv_usec- UTCtime_s.tv_usec)<0)
	{
		UTCtime_r.tv_sec  = UTCtime_e.tv_sec - UTCtime_s.tv_sec - 1;
		UTCtime_r.tv_usec = 1000000 - UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	else
	{
		UTCtime_r.tv_sec = UTCtime_e.tv_sec - UTCtime_s.tv_sec;
		UTCtime_r.tv_usec = UTCtime_e.tv_usec - UTCtime_s.tv_usec;
	}
	printf("runtime : %ld sec %ld\n", UTCtime_r.tv_sec, UTCtime_r.tv_usec);
}

int main()
{
    // linux micro sec까지 측정 
    // UTCtime_s: 측정 시작시간
    // UTCtime_e : 측정 종료시간
    struct timeval UTCtime_s, UTCtime_e;

    gettimeofday(&UTCtime_s, NULL);

    // 100000usec -> 100msec
    usleep(100000);

    gettimeofday(&UTCtime_e, NULL);
    disp_runtime(UTCtime_s, UTCtime_e);
}