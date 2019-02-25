const int DESIRED_CAMERA_WIDTH = 640;
const int DESIRED_CAMERA_HEIGHT = 480;
const int NUM_STICK_FIGURE_ITERATIONS = 40; // Sets how long the stick figure face should be shown for skin detection.

const char *windowName = "Cartoonifier";   // Name shown in the GUI window.
// Set to true if you want to see line drawings instead of paintings.
bool m_sketchMode = false;
// Set to true if you want to change the skin color of the character to an alien color.
bool m_alienMode = true;
// Set to true if you want an evil "bad" character instead of a "good" character.
bool m_evilMode = false;
// Set to true if you want to see many windows created, showing various debug info. Set to 0 otherwise.
bool m_debugMode = false;


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#include "cartoon.h"            // Cartoonify a photo.
#include "ImageUtils.h"

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
// Keypress event handler. Note that it should be a 'char' and not an 'int' to better support Linux.
void onKeypress(char key)
{
    switch (key) {
        case 's':
            m_sketchMode = !m_sketchMode;
            cout << "Sketch / Paint mode: " << m_sketchMode << endl;
            break;
        case 'a':
            m_alienMode = !m_alienMode;
            cout << "Alien / Human mode: " << m_alienMode << endl;
            // Display a stick figure outline when alien skin is enabled,
            // so the user puts their face in the correct place.
            if (m_alienMode) {
                m_stickFigureIterations = NUM_STICK_FIGURE_ITERATIONS;
            }
            break;
        case 'e':
            m_evilMode = !m_evilMode;
            cout << "Evil / Good mode: " << m_evilMode << endl;
            break;
        case 'd':
            m_debugMode = !m_debugMode;
            cout << "Debug mode: " << m_debugMode << endl;
            break;
    }
}

int main() {

    cout<<"CV VERSION:"<<CV_VERSION<<endl;
    int cameraNumber =0;
    VideoCapture camera;
    initWebcam(camera,cameraNumber);

    // 这是摄像头的分辨率
    camera.set(CAP_PROP_FRAME_WIDTH, DESIRED_CAMERA_WIDTH);
    camera.set(CAP_PROP_FRAME_HEIGHT , DESIRED_CAMERA_HEIGHT);

    namedWindow(windowName); //创建一个显示 图像的窗口

    while (true){
        Mat cameraFrame;
        camera >> cameraFrame;
        if(cameraFrame.empty()){
            cerr<<"Error:couldnt grab the next Frame!";
            exit(1);
        }

        Mat displayedFrame = Mat(cameraFrame.size(),CV_8UC3);

        int debugType=2;
        // Run the cartoonifier filter using the selected mode.
        cartoonifyImage(cameraFrame, displayedFrame, m_sketchMode, m_alienMode, m_evilMode, debugType);

        // Show a stick-figure outline of a face for a short duration, so the user knows where to put their face.
        if (m_stickFigureIterations > 0) {
            drawFaceStickFigure(displayedFrame);
            m_stickFigureIterations--;
        }

        imshow(windowName,displayedFrame);

        char keypress=waitKey(20);

        if (keypress == VK_ESCAPE) {   // Escape Key
            // Quit the program!
            break;
        }
        // Process any other keypresses.
        if (keypress > 0) {
            onKeypress(keypress);
        }

    }
    return 0;
}