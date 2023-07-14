#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat finger, adaptive, adaptive1;
    Mat finger_dst, adaptive_dst, adaptive1_dst;
    int average;
    int pre_average=0;
    finger = imread("finger_print.png",0);
    adaptive = imread("adaptive.png",0);
    adaptive1 = imread("adaptive_1.jpg",0);
    threshold(finger,finger_dst,0,255,THRESH_BINARY|THRESH_OTSU);
    adaptiveThreshold(adaptive,adaptive_dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,9,7);
    adaptiveThreshold(adaptive1,adaptive1_dst,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,45,15);
    imshow("finger_print",finger_dst);
    imshow("adaptive_1",adaptive1_dst);
    imshow("adaptive",adaptive_dst);
    waitKey(0);
}