#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

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
