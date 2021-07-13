// OpenCV를 사용하여 동영상 녹화하기
// API설명 참조 사이트 : https://opencvlib.weebly.com/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>   // O_WRONLY
#include <unistd.h>  // write() ,read()


using namespace cv;
using namespace std;

#define VIDEO_WINDOW_NAME "record"
char fileName[30];

char tBUF[100];

#define TIME_FILENAME 0
#define FOLDER_NAME   1
#define LOG_TIME      2

void getTime(int ret_type)
{
    time_t UTCtime;
    struct tm *tm;
    // 사용자 문자열로 시간정보를 저장하기 위한 문자열 버퍼

    // 커널에서 시간 정보를 읽어서
    // UTCtime변수에 넣어준다.
    time(&UTCtime); // UTC 현재 시간 읽어오기
    //printf("time : %u\n", (unsigned)UTCtime); // UTC 현재 시간 출력

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

int main(int, char**)
{
    // 1. VideoCapture("동영상파일의 경로")
    //    VideoCapture(0)
    VideoCapture cap;
    VideoWriter writer;

    int deviceID = 0;
    int apiID = cv::CAP_V4L2;
    int exitFlag = 0;
    int MaxFrame = 1780;
    int frameCount;
    int fd;
    int WRByte;
    char buff[200];
    Mat frame;

    // 로그파일을 기록하기 위해 파일열기
    fd = open("/home/pi/blackBox/blackbox.log",O_WRONLY | O_CREAT | O_TRUNC, 0644);
    getTime(LOG_TIME);
    sprintf(buff, "%s blackbox log파일 저장을 시작합니다.",tBUF);
    WRByte = write(fd, buff, strlen(buff));

    // STEP 1. 카메라 장치 열기 
    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        perror("ERROR! Unable to open camera\n");
        return -1;
    }

    //  라즈베리파이 카메라의 해상도를 1280X720으로 변경 
    //cap.set(CAP_PROP_FRAME_WIDTH, 320);
    //cap.set(CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CAP_PROP_FPS,30);
    // Video Recording
    //  현재 카메라에서 초당 몇 프레임으로 출력하고 있는가?
    float videoFPS = cap.get(CAP_PROP_FPS);
    int videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int videoHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    printf("videoFPS=%f\n",videoFPS);
    printf("width=%d, height=%d\n",videoWidth, videoHeight);

    // 1st : 저장하고자 하는 파일명
    // 2nd : 코덱을 지정
    // 3rd : FPS
    // 4th : ImageSize,
    // 5th : isColor=True
    while(1)
    {
        // 시간정보를 읽어와서 파일명을 생성
        // 전역변수 fileName에 저장
        getTime(TIME_FILENAME);
        printf("FILENAME:%s\n",tBUF);
        sprintf(buff, "/home/pi/blackBox/%s",tBUF);
        writer.open(buff, VideoWriter::fourcc('D','I','V','X'),
        videoFPS, Size(videoWidth, videoHeight), true);

        if (!writer.isOpened())
        {
            perror("Can't write video");
            return -1;
        }
        frameCount =0;
        namedWindow(VIDEO_WINDOW_NAME);

        while(frameCount<MaxFrame)
        {
            // 카메라에서 매 프레임마다 이미지 읽기
            cap.read(frame);
            frameCount++;
            // check if we succeeded
            if (frame.empty()) {
                perror("ERROR! blank frame grabbed\n");
                break;
            }

            // 읽어온 한 장의 프레임을  writer에 쓰기
            writer << frame; // test.avi
            imshow(VIDEO_WINDOW_NAME, frame);

            // ESC=>27 'ESC' 키가 입력되면 종료 
            if(waitKey(1000/videoFPS)==27)
            {
                printf("Stop video record\n");
                exitFlag = 1;
                break;
            }

        }
        writer.release();
        if(exitFlag==1)
            break;
    }
    cap.release();
    close(fd);
    destroyWindow(VIDEO_WINDOW_NAME);

    return 0;
}
