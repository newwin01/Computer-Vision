#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void displayImage(Mat src,String title);

int main(){
    Mat frame,foregroundMask,backgroundImg, foregroundImg;
    Mat gray;
    int delay;
    VideoCapture cap;
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    vector<vector<Point> > contours;
    vector<Vec4i>hierarchy;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));

    if (cap.open("Project22.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
    delay = 1000/cap.get(CAP_PROP_FPS);
    while(1){
        cap >> frame;
        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        if (foregroundMask.empty()) foregroundMask.create(frame.size(), frame.type());
        bg_model->apply(frame,foregroundMask);
        GaussianBlur(foregroundMask,foregroundMask,Size(11,11),5,5);
        threshold(foregroundMask,foregroundMask,249,255,THRESH_BINARY);
        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg,foregroundMask);
        bg_model->getBackgroundImage(backgroundImg);
        erode(foregroundMask,foregroundMask,element);
        findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        if(contours.size()>0){
            displayImage(frame,"project2");
        }
        else{
            imshow("project2",frame);
        }
        waitKey(delay);
    }
    waitKey(0);
}

void displayImage(Mat src,String title){
    putText(src,format("Alert! Moving object!"),Point(0,40),FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),1);
    imshow(title,src);
}