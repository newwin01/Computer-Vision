#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main(){
	Mat frame;
	int delay;
	VideoCapture cap;
    //canny
    Rect left(200,400,400,200);
    Rect right(600,400,400,200);
    Mat left_roi, right_roi;
    Mat canny_left, canny_right;
    Mat frame_copy;
    //line
    float average1_rho=0;
    float average1_theta=0;
    float average2_rho=0;
    float average2_theta=0;
    float a1=0, b1=0, x1=0, y1=0;
    float a2=0, b2=0, x2=0, y2=0;
    Point p1, p2, p3, p4;
    
    vector<Vec2f> left_lines;
    vector<Vec2f> right_lines;

	// check file existence
	if (cap.open("road.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
	delay = 1000/cap.get(CAP_PROP_FPS);

	while (cap.get(CAP_PROP_POS_MSEC)<20000) {
		cap >> frame;
		if (frame.empty()) {
			cout << "end of video" << endl;
			break;
		}
        
        frame_copy = frame.clone();
        left_roi = frame_copy(left);
        cvtColor(left_roi,left_roi,CV_BGR2GRAY);
        right_roi = frame_copy(right);
        cvtColor(right_roi,right_roi,CV_BGR2GRAY);
        blur(left_roi,canny_left,Size(5,5));
        blur(right_roi,canny_right,Size(5,5));
        Canny(canny_left,canny_left, 10, 60, 3);
        Canny(canny_right,canny_right, 10, 60, 3);
        namedWindow("Left canny");
        moveWindow("Left canny", 200, 0);
        imshow("Left canny", canny_left);
        namedWindow("Right canny");
        moveWindow("Right canny", 600, 0);
        imshow("Right canny", canny_right);
        HoughLines(canny_left,left_lines,1,(CV_PI/180),60,0,0,30*(CV_PI/180),60*(CV_PI/180));
        average1_rho = 0;
        average1_theta = 0;
        for (int i = 0; i < left_lines.size(); i++) {
            average1_rho = average1_rho+left_lines[i][0];
            average1_theta = average1_theta+left_lines[i][1];
        }
        average1_rho = average1_rho/left_lines.size();
        average1_theta = average1_theta/left_lines.size();
        a1 = cos(average1_theta);
        b1 = sin(average1_theta);
        x1 = a1*average1_rho+200;
        y1 = b1*average1_rho+400;
        p1 = Point(cvRound(x1 + 1000 * (-b1)) ,cvRound(y1 + 1000 * a1)); 
        p2 = Point(cvRound(x1 - 1000 * (-b1)) ,cvRound(y1 - 1000 * a1));
        line(frame, p1, p2, Scalar(0, 0, 255), 3, 8);
        HoughLines(canny_right,right_lines,1,(CV_PI/180),60,0,0,120*(CV_PI/180),150*(CV_PI/180));
        average2_rho = 0;
        average2_theta = 0;
        for (int i = 0; i < right_lines.size(); i++) {
            average2_rho = average2_rho+right_lines[i][0];
            average2_theta = average2_theta+right_lines[i][1];
        }
        average2_rho = average2_rho/right_lines.size();
        average2_theta = average2_theta/right_lines.size();
        a2 = cos(average2_theta);
        b2 = sin(average2_theta);
        x2 = a2*average2_rho+600;
        y2 = b2*average2_rho+400;
        p3 = Point(cvRound(x2 + 1000 * (-b2)), cvRound(y2 + 1000 * a2));
        p4 = Point(cvRound(x2 - 1000 * (-b2)), cvRound(y2 - 1000 * a2)); 
        line(frame, p3, p4, Scalar(0, 0, 255), 3, 8);

        imshow("frame",frame);
        waitKey(delay);
    }
	waitKey(0);
}