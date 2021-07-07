#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int glob_var = 3;

// 스레드 함수를 생성할때 
// 리턴값은 void*
// 넘겨 받는 인수도 void*
void* t_function(void* data)
{
    int value;
    int i=0;
    pthread_t t_id;
    glob_var++;
    // 스레드의 ID값을 확인
    t_id = pthread_self();
    printf("pid=%d, t_id=%ld, glob_var=%d\n",getpid(), t_id, glob_var);

    value = *((int *)data);
    printf("value=%d\n",value);

    return  (void*)(value*value);
}

int main(void)
{
    pthread_t p_thread[2];
    int a = 1;
    int b = 2;
    int err;
    int status;

    printf("현재 PID=%d, glob_var=%d\n", getpid(), glob_var);

    // 추가로 스레드를 2개 생성
    // 1st : thread변수의 주소값,
    // 2nd : thread attibute(NULL)
    // 3rd : 스레드 생성시 실행할 스레드 함수 주소
    // 4th : 스레드 생성시 전달할 인자값
    err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a);

    // 스레드가 정상적으로 생성X
    if(err!=0)
    {
        perror("ERROR:pthread_create(0): "); 
        exit(1);
    }

    err = pthread_create(&p_thread[1], NULL, t_function, (void*)&b);

    // 스레드가 정상적으로 생성X
    if(err!=0)
    {
        perror("ERROR:pthread_create(1): "); 
        exit(2);
    }

    pthread_join(p_thread[0], (void**)&status);
    printf("thread_join(0) : %d\n", status);
    
    pthread_join(p_thread[1], (void**)&status);
    printf("thread_join(1) : %d\n", status); 



}
