const int DESIRED_CAMERA_WIDTH = 640;
const int DESIRED_CAMERA_HEIGHT = 480;
const int NUM_STICK_FIGURE_ITERATIONS = 40; // Sets how long the stick figure face should be shown for skin detection.

const char *windowName = "Cartoonifier";   // Name shown in the GUI window.
// Set to true if you want to see line drawings instead of paintings.
bool m_sketchMode = false;
// Set to true if you want to change the skin color of the character to an alien color.
bool m_alienMode = false;
// Set to true if you want an evil "bad" character instead of a "good" character.
bool m_evilMode = false;
// Set to true if you want to see many windows created, showing various debug info. Set to 0 otherwise.
bool m_debugMode = false;


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int m_stickFigureIterations = 0;  // Draws a stick figure outline for where the user's face should be.

#if !defined VK_ESCAPE
#define VK_ESCAPE 0x1B      // Escape character (27)
#endif

void initWebcam(VideoCapture& videoCapture,int cameraNUmber){
    try{
        videoCapture.open(cameraNUmber);
    }catch (cv::Exception &e){
        cerr<<"Error could not access camera!"<<endl;
        exit(1);

    }
    cout<<"open camera "<<cameraNUmber<<endl;

}
void readPicture(){
    Mat srcImage = imread("/Users/wuyongyu/CLionProjects/opencv_example/img.png");
    if (!srcImage.data) {
        std::cout << "Image not loaded";
    }
    imshow("[img]", srcImage);
    waitKey(0);
    int * a=NULL;
}
int main() {

    cout<<"CV VERSION:"<<CV_VERSION<<endl;
    int cameraNumber =0;
    VideoCapture camera;
    initWebcam(camera,cameraNumber);

    // 这是摄像头的分辨率
    camera.set(CAP_PROP_FRAME_WIDTH, DESIRED_CAMERA_WIDTH);
    camera.set(CAP_PROP_FRAME_HEIGHT , DESIRED_CAMERA_HEIGHT);

    return 0;
}