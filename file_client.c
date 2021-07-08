#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
    int sock;
    FILE *fp;

	char buf[BUF_SIZE];
	int read_cnt;
    int flag;
	struct sockaddr_in serv_adr;

    if(argc!=3) {
	    printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

    // STEP 1. socket() : 소켓을 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // STEP 2.1 : 프로토콜, 서버의 주소, 포트번호를 설정한 뒤
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

    // STEP 2.2 : connect() 서버에 접속 요청
    connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    fp=fopen("receive.jpg", "wb");

    // read()함수를 blocking I/O -> non blocking I/O로 바꾸는 설정
    flag = fcntl( sock, F_GETFL, 0 );
    fcntl(sock, F_SETFL, flag | O_NONBLOCK );

    // STEP 3. read(), write()
	while((read_cnt=read(sock, buf, BUF_SIZE ))!=0)
		fwrite((void*)buf, 1, read_cnt, fp);
    // 상태 확인을 위해 터미널에 출력되는 메시지
    puts("Received file data");
    // 파일 데이터 수신이 끝나면 클라이언트는
    // "Thank you"라는 문자열을 전송

    write(sock, "Thank you", 10);

    // STEP 4. shutdown(), close()
    fclose(fp);
	close(sock);
	return 0;
}