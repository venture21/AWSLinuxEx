#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

#define TIME_FILENAME 0
#define FOLDER_NAME   1
#define LOG_TIME      2

using namespace cv;
using namespace std;

char fileName[30];
char tBUF[BUFSIZ];

void getTime(int ret_type)
{
    time_t UTCtime;
    struct tm *tm;
    // 사용자 문자열로 시간정보를 저장하기 위한 문자열 버퍼

    // 커널에서 시간 정보를 읽어서
    // UTCtime변수에 넣어준다.
    time(&UTCtime); // UTC 현재 시간 읽어오기
    printf("time : %u\n", (unsigned)UTCtime); // UTC 현재 시간 출력

    tm = localtime(&UTCtime);
    //printf("asctime : %s", asctime(tm)); // 현재의 시간을 tm 구조체를 이용해서 출력

    // 1st : 우리가 만들 문자열 저장할 버퍼
    // 2nd : 버퍼 사이즈
    // 3rd : %a : 간단한 요일, %m :월, %e : 일, %H : 24시, %M :분, %S :초, %Y :년
    //strftime(buf,sizeof(buf),"%a %m %e %H:%M:%S %Y", tm); // 사용자 정의 문자열 지정
    if (ret_type==TIME_FILENAME)
        strftime(tBUF,sizeof(tBUF),"%Y%m%d%H%M%S.avi", tm);
    else if(ret_type==FOLDER_NAME)
        strftime(tBUF,sizeof(tBUF),"%Y%m%d%H", tm);
    else if(ret_type==LOG_TIME)
        strftime(tBUF,sizeof(tBUF),"[%Y-%m-%d %H:%M:%S]", tm);
    //printf("strftime: %s\n",buf);
}

void makefileName(void)
{
    time_t UTCtime;
    struct tm *tm;
    // 사용자 문자열로 시간정보를 저장하기 위한 문자열 버퍼
    char buf[BUFSIZ];
    // 커널에서 시간 정보를 읽어서
    // UTCtime변수에 넣어준다.
    time(&UTCtime); // UTC 현재 시간 읽어오기
    printf("time : %u\n", (unsigned)UTCtime); // UTC 현재 시간 출력

    tm = localtime(&UTCtime);
    //printf("asctime : %s", asctime(tm)); // 현재의 시간을 tm 구조체를 이용해서 출력

    // 1st : 우리가 만들 문자열 저장할 버퍼
    // 2nd : 버퍼 사이즈
    // 3rd : %a : 간단한 요일, %m :월, %e : 일, %H : 24시, %M :분, %S :초, %Y :년
    //strftime(buf,sizeof(buf),"%a %m %e %H:%M:%S %Y", tm); // 사용자 정의 문자열 지정
    strftime(fileName,sizeof(fileName),"[%Y-%m-%d] %H:%M:%S", tm); // 사용자 정의 문자열 지정
    printf("strftime: %s\n",fileName); 
    //fileName => "202107121458.avi"
}


int main(int, char**)
{
    //카메라 이미지 한 장을 저장하기 위한 이미지 객체 
    Mat frame;

    // 카메라를 선택하기 위한 객체
    // cap은 fd와 동일한 존재
    VideoCapture cap;
    // 카메라 갯수가 증가하면 0번부터 1씩 증가
    int deviceID = 0;
    int apiID = cv::CAP_V4L2;   

    // STEP 1. 카메라 장치 열기 
    cap.open(deviceID, apiID);

    // check if we succeeded
    if (!cap.isOpened()) {
        perror("ERROR! Unable to open camera\n");
        return -1;
    }

    //--- GRAB AND WRITE LOOP
    printf("Start grabbing\n"); 
    printf("Press any key to terminate\n");

    while(1)
    {
        // 카메라에서 매 프레임마다 이미지 읽기
        cap.read(frame);

        // check if we succeeded
        if (frame.empty()) {
            perror("ERROR! blank frame grabbed\n");
            break;
        }
        // "Live"라는 창을 생성하고, 그 창에 frame 이미지를 보여준다.
        imshow("Live", frame);
	// waitKey함수는 ms단위로 대기함수 
	// ()가 비어 있으면 키입력이 들어오기 전까지 무한 대기
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
