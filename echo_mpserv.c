// 멀티 프로세스를 이용해서 여러 명의 
// 클라이언트를 동시에 처리할 수 있게 구조를 변경
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void read_childproc(int sig)
{
    pid_t pid;
	int status;
	pid=waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;

    pid_t pid;
    socklen_t adr_sz;
    char buf[BUF_SIZE];
    int str_len;

    if(argc!=2) {
	    printf("Usage : %s <port>\n", argv[0]);
	    exit(1);
	}
    // SIGCHLD신호가 수신되었을때,
    // read_childproc()함수로 자동 이동(커널) 
    signal(SIGCHLD, read_childproc);

    // STEP 1. socket()
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);

    // STEP 2. bind()
    memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
 	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");   

    // STEP 3. listen()
    if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
    
    while(1)
    {
        // STEP 4. accept()
		adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if(clnt_sock==-1)
			continue;
		else
			puts("new client connected...");

        // 새로운 클라이언트가 접속 했다면
        // 클라이언트 하나당 프로세스 하나를 생성
        pid = fork();

        // 정상적으로 프로세스가 생성되지 않은 경우
		if(pid==-1)
		{
			close(clnt_sock);
			continue;
		} 
        // 자식프로세스 (클라이언트 처리 프로세스)
        else if (pid==0)
        {
			close(serv_sock);
            
            // STEP 5. read(), write()
			while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0)
				write(clnt_sock, buf, str_len);
			// STEP 6. client close()
			close(clnt_sock);
			puts("client disconnected...");
			return 0;            
        }
		else
			close(clnt_sock);
    }
    // STEP 6. server close()
	close(serv_sock);
	return 0;    

}
