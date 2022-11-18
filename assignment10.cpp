#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


struct MouseParams{
    Mat img;
    vector<Point2f> in, out;
};


static void onMouse(int event, int x, int y, int, void* param){
    MouseParams* mp = (MouseParams*)param;
    if (event == EVENT_LBUTTONDOWN) { 
        mp->out.push_back(Point2f(x, y));
    }
    if (event == EVENT_RBUTTONDOWN){
        mp->out.clear();
    }
}

int main()
{
    Mat frame1;
    VideoCapture cap1;
    Mat frame2;
    VideoCapture cap2;
    int delay;

    Mat result;
    Mat mask_tmp;
    cap1.open("Timesquare.mp4");
    cap2.open("contest.mp4");
    MouseParams mp;
    delay = 1000 / cap1.get(CAP_PROP_FPS);
    int width, height;
    width = cap2.get(CAP_PROP_FRAME_WIDTH);
    height = cap2.get(CAP_PROP_FRAME_HEIGHT);
    Mat mask(height,width,CV_8UC1,Scalar(255));
    int width1, height1;
    width1 = cap1.get(CAP_PROP_FRAME_WIDTH);
    height1 = cap1.get(CAP_PROP_FRAME_HEIGHT);

    mp.in.push_back(Point2f(0, 0)); 
    mp.in.push_back(Point2f(width, 0)); 
    mp.in.push_back(Point2f(width, height)); 
    mp.in.push_back(Point2f(0, height));


    while(1){
        cap1 >> frame1;
        cap2 >> frame2;
        if(frame1.empty()){
            break;
        }
        mp.img = frame1;
        if (mp.out.size() == 4) {
            mask_tmp = frame1.clone();
            Mat homo_mat = getPerspectiveTransform(mp.in, mp.out);
            warpPerspective(frame2, result, homo_mat, Size(width1, height1));
            warpPerspective(mask, mask_tmp, homo_mat, Size(width1, height1));
            result.copyTo(frame1,mask_tmp);
            imshow("background",frame1);
        } else {
            for (size_t i = 0; i < mp.out.size(); i++) {
                circle(frame1, mp.out[i], 3, Scalar(0, 0, 255), 5); 
            }
        }
        imshow("input",frame2);
        imshow("background",frame1);
        setMouseCallback("background",onMouse,(void*)&mp);
        waitKey(delay);
    }
    waitKey(0);
    return 0;
}