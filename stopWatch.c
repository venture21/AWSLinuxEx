#include <stdio.h>
#include <unistd.h>
#include <sys/time.h> // getimeofday( ) 함수에서 사용
#include <stdlib.h>

#include <time.h>
#include <stdio.h>


int main(void)
{
	int i;
	long sum=0;
	int startValue=1;
	int endValue=2000000000;
	
	clock_t start_point, end_point;
	// 시작 시간 기록
	start_point = clock();
	
	for(i=startValue;i<=endValue;i++)
	sum +=i;
	
	// 종료 시간 기록
	end_point = clock();

	printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
	printf("Result Value : %ld\n", sum); 
}