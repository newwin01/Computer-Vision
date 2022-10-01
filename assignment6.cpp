#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat finger, adaptive, adaptive1;
    Mat finger_dst, adaptive_dst, adaptive1_dst;
    finger = imread("finger_print.png");
    imshow("finger",finger);
    // adaptive = imread("adaptive.png",0);
    // adaptive1 = imread("adaptive_1.jpg",0);
    // adaptiveThreshold(finger,finger_dst,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,85,15);
    // adaptiveThreshold(adaptive,adaptive_dst,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,85,10);
    // adaptiveThreshold(adaptive1,adaptive1_dst,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,85,15);



    // imshow("result",finger_dst);
    // imshow("result1",adaptive1_dst);
    // imshow("result2",adaptive_dst);
    waitKey(0);
}