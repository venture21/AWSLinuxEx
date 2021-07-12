// OpenCV를 사용하여 동영상 녹화하기
// API설명 참조 사이트 : https://opencvlib.weebly.com/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
    // 1. VideoCapture("동영상파일의 경로")
    //    VideoCapture(0)
    VideoCapture cap;
    int deviceID = 0;
    int apiID = cv::CAP_V4L2;

    Mat frame;
    // STEP 1. 카메라 장치 열기 
    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        perror("ERROR! Unable to open camera\n");
        return -1;
    }
    //  라즈베리파이 카메라의 해상도를 1280X720으로 변경 
    //cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    //cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    cap.set(CAP_PROP_FPS,60);
    // Video Recording
    //  현재 카메라에서 초당 몇 프레임으로 출력하고 있는가?
    float videoFPS = cap.get(CAP_PROP_FPS);
    int videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int videoHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    printf("videoFPS=%f\n",videoFPS);
    printf("width=%d, height=%d\n",videoWidth, videoHeight);

    // while(1)
    // {

    // }



    return 0;
}
