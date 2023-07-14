#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// int main() {
//     VideoCapture capture("background.mp4"); 
//     Mat image, sum, avg;
//     int cnt = 2;
//     capture >> avg;
//     while (true) {
//         if (!capture.read(image)) 
//         break; 
//         add(image / cnt, avg*(cnt - 1) / cnt, avg);
//         imshow("avg", avg); 
//         cnt++;
//         waitKey(33);
//     }
// } 

// int main() {
// VideoCapture capture("background.mp4");
//     Mat background, image, gray, result, foregroundMask, foregroundImg;
// //set the first frame as background
//     capture >> background;
//     cvtColor(background, background, CV_BGR2GRAY);
//     while (true) {
//         if (capture.grab() == 0) 
//             break; 
//             capture.retrieve(image); 
//             cvtColor(image, gray, CV_BGR2GRAY);
//             absdiff(background, gray, foregroundMask);
//             threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY); 
//             foregroundMask.copyTo(foregroundImg);
//             gray.copyTo(foregroundImg, foregroundMask);
//             imshow("foregroundImg", foregroundImg); 
//             imshow("foregroundMask", foregroundMask); 
//             imshow("background", background);
//             waitKey(33); 
//         }
// }

int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(); 
    Mat image, foregroundMask, backgroundImg, foregroundImg;
    VideoCapture cap("background.mp4");
    while (true) {
        cap >> image;
        resize(image, image, Size(640, 480));
        if (foregroundMask.empty()) 
            foregroundMask.create(image.size(), image.type());
        // image: Next video frame. Floating point frame will be used without scaling and //should be in range [0,255]. 
        // foregroundMask: The output foreground mask as an 8-bit binary image.
        bg_model->apply(image, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
        threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY); foregroundImg = Scalar::all(0);
        image.copyTo(foregroundImg, foregroundMask);
        // backgroundImg: The output background image. 
        bg_model->getBackgroundImage(backgroundImg);
        imshow("foreground mask", foregroundMask); 
        imshow("foreground image", foregroundImg);
        if (!backgroundImg.empty()) {
        imshow("mean background image", backgroundImg); 
        }
        waitKey(33); 
    }
}