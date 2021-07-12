// OpenCV를 사용하여 동영상 녹화하기
// API설명 참조 사이트 : https://opencvlib.weebly.com/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// "202107121433.avi"
#define OUTPUT_VIDEO_NAME "test.avi"

int main(int, char**)
{
    // 1. VideoCapture("동영상파일의 경로")
    //    VideoCapture(0)
    VideoCapture cap;
    VideoWriter writer;

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
    writer.open(OUTPUT_VIDEO_NAME, VideoWriter::fourcc('D','I','V','X'),
    videoFPS, Size(videoWidth, videoHeight), true);

    if (!writer.isOpened())
    {
        perror("Can't write video");
        return -1;
    }
#define VIDEO_WINDOW_NAME "record"
    namedWindow(VIDEO_WINDOW_NAME);

    while(1)
    {
        // 카메라에서 매 프레임마다 이미지 읽기
        cap.read(frame);
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
            break;
        }

    }
    writer.release();
    destroyWindow(VIDEO_WINDOW_NAME);

    return 0;
}
