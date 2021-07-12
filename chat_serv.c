#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

//서버에서 사용할 버퍼의 크기
#define BUF_SIZE 100
// 서버가 최대로 접속 가능한 클라이언트 수
#define MAX_CLNT 256

// 서버에 클라이언트가 접속하면 
// 클라이언트의 데이터 송수신을 담당할 스레드 함수
void* handle_clnt(void* arg);

// 메시지를 보내는 함수
void send_msg(char * msg, int len);
// 에러처리 함수
void error_handling(char * msg);

// 전역 변수 영역을 통해 스레드간
// 공유 메모리 변수를 선언
// :전역 변수 영역은 모든 스레드에서 접근 가능 하므로
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
// mutex 변수 : critical section을 관리하기 위해
// mutex를 사용하여 lock, unlock
pthread_mutex_t mutx;  

// "./chat_serv 5000
// argv[0] = "./chat_serv"
// argv[1] = "5000"
int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_sz;

    // thread id값을 저장하는 변수
    pthread_t t_id;
    // 인자값이 2개가 아닌 경우
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
    // mutex 변수 초기화
    pthread_mutex_init(&mutx, NULL);

    // STEP 1. socket()
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);

    // STEP 2. bind() - 프로토콜, IP어드레스, 포트번호
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET; 
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

    // STEP 3. listen() - 서버 소켓의 대기열 버퍼 크기설정
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

    while(1)
    {
        // STEP 4. accept()
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

        // clnt_socks을 증가 시킨다.
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        // 방금 접속한 클라이언트의 데이터 처리를 위한 스레드 생성
        pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		// 스레드 생성후 생성한 메인 스레드가 관린하지 않고 생성된 스레드가
        // 종료하게되면 알아서 스레드를 종료한다. (관리가 필요하지 않음.)
        pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
        

        // STEP 6.1 client close()
    }

    // STEP 6.2 server close()


}

void* handle_clnt(void* arg)
{
    int clnt_sock=*((int*)arg);
    int str_len=0;
    int i;
    char msg[BUF_SIZE];

    // STEP 5. read() / write()
    // 클라이언트에서 접속을 종료할때까지 read()를 했을때 NULL값 수신
	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
        // 모든 클라이언트에게 메시지 전송
		send_msg(msg, str_len);


    pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)   // remove disconnected client
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
 	close(clnt_sock);
    // 현재의 스레드 함수는 리턴값을 사용하지 않음
	return NULL;   
}

void send_msg(char * msg, int len)   // send to all
{
	int i;
	pthread_mutex_lock(&mutx);
    // 클라이언트 한명 한명에게 메세지를 전송
	for(i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);
	pthread_mutex_unlock(&mutx);
}


void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}




























