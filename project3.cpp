#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv; 
using namespace std; 
using namespace dnn;

void displayLine(Mat src);
void displayCarNearby(Mat src);


int main(){
    Mat frame;
    int delay;
    VideoCapture cap;

    //for line
    Rect left(150,200,100,280);
    Rect right(450,200,100,280);
    Rect center(300,200,100,280);
    Mat left_roi, right_roi, center_roi;
    Mat canny_left, canny_right, canny_center;
    Mat frame_copy;
    float average1_rho=0;
    float average1_theta=0;
    float average2_rho=0;
    float average2_theta=0;
    float average3_rho = 0;
    float average3_theta = 0;
    float a1=0, b1=0, x1=0, y1=0;
    float a2=0, b2=0, x2=0, y2=0;
    float a3=0, b3=0, x3=0, y3=0;
    Point p1, p2, p3, p4, p5, p6;
    vector<Vec2f> left_lines;
    vector<Vec2f> right_lines;
    vector<Vec2f> center_lines;

    //for detect
    Mat frame_detect;
    String modelConfiguration = "deep/yolov2-tiny.cfg"; 
    String modelBinary = "deep/yolov2-tiny.weights";
    Net net = readNetFromDarknet(modelConfiguration, modelBinary);
    if (cap.open("Project3_1.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
    delay = 1000/cap.get(CAP_PROP_FPS);

    
    vector<String> classNamesVec;
    ifstream classNamesFile("deep/coco.names");
    if (classNamesFile.is_open()) {
        string className = "";
        while (std::getline(classNamesFile, className)) 
        classNamesVec.push_back(className);

    }


    //for ROI hough line
    // cap >> frame;
    // frame_copy=frame.clone();

    // left_roi = frame_copy(left);
    // right_roi = frame_copy(right);
    // imshow("frame",frame);
    // imshow("left",left_roi);
    // imshow("right",right_roi);
    // waitKey(0);


    while (1) {
        cap >> frame; 
        if (frame.empty()) {
            waitKey(); 
            break;
        }
        frame_copy = frame.clone();


        // hough line

        left_roi = frame_copy(left);
        cvtColor(left_roi,left_roi,CV_BGR2GRAY);
        right_roi = frame_copy(right);
        cvtColor(right_roi,right_roi,CV_BGR2GRAY);
        blur(left_roi,canny_left,Size(5,5));
        blur(right_roi,canny_right,Size(5,5));
        Canny(canny_left,canny_left, 10, 60, 3);
        Canny(canny_right,canny_right, 10, 60, 3);
        imshow("Left canny", canny_left);
        imshow("Right canny", canny_right);

        //left
        HoughLines(canny_left,left_lines,1,(CV_PI/180),60,0,0,30*(CV_PI/180),60*(CV_PI/180));
        average1_rho = 0;
        average1_theta = 0;
        for (int i = 0; i < left_lines.size(); i++) {
            average1_rho = average1_rho+left_lines[i][0];
            average1_theta = average1_theta+left_lines[i][1];
        }
        // average1_rho = average1_rho/left_lines.size();
        // average1_theta = average1_theta/left_lines.size();
        // a1 = cos(average1_theta);
        // b1 = sin(average1_theta);
        // x1 = a1*average1_rho+150;
        // y1 = b1*average1_rho+200;
        // p1 = Point(cvRound(x1 + 1000 * (-b1)) ,cvRound(y1 + 1000 * a1)); 
        // p2 = Point(cvRound(x1 - 1000 * (-b1)) ,cvRound(y1 - 1000 * a1));
        // line(frame, p1, p2, Scalar(0, 0, 255), 3, 8);

        //right
        HoughLines(canny_right,right_lines,1,(CV_PI/180),60,0,0,120*(CV_PI/180),150*(CV_PI/180));
        average2_rho = 0;
        average2_theta = 0;
        for (int i = 0; i < right_lines.size(); i++) {
            average2_rho = average2_rho+right_lines[i][0];
            average2_theta = average2_theta+right_lines[i][1];
        }
        // average2_rho = average2_rho/right_lines.size();
        // average2_theta = average2_theta/right_lines.size();
        // a2 = cos(average2_theta);
        // b2 = sin(average2_theta);
        // x2 = a2*average2_rho+450;
        // y2 = b2*average2_rho+200;
        // p3 = Point(cvRound(x2 + 1000 * (-b2)), cvRound(y2 + 1000 * a2));
        // p4 = Point(cvRound(x2 - 1000 * (-b2)), cvRound(y2 - 1000 * a2)); 
        // line(frame, p3, p4, Scalar(0, 0, 255), 3, 8);

        //center
        center_roi = frame_copy(center);
        cvtColor(center_roi,center_roi,CV_BGR2GRAY);
        blur(center_roi,canny_center,Size(5,5));
        Canny(canny_center,canny_center, 10, 70, 3);
        imshow("center",canny_center);
        HoughLines(canny_center,center_lines,1,(CV_PI/180),60,0,0,130*(CV_PI/180),180*(CV_PI/180));
        // average3_rho = 0;
        // average3_theta = 0;
        // for (int i = 0; i < center_lines.size(); i++) {
        //     average3_rho = average3_rho+center_lines[i][0];
        //     average3_theta = average3_theta+center_lines[i][1];
        // }
        // average3_rho = average3_rho/center_lines.size();
        // average3_theta = average3_theta/center_lines.size();
        // a3 = cos(average3_theta);
        // b3 = sin(average3_theta);
        // x3 = a3*average3_rho+300;
        // y3 = b3*average3_rho+200;
        // p5 = Point(cvRound(x3 + 1000 * (-b3)) ,cvRound(y3 + 1000 * a3)); 
        // p6 = Point(cvRound(x3 - 1000 * (-b3)) ,cvRound(y3 - 1000 * a3));
        // line(frame, p5, p6, Scalar(0, 0, 255), 3, 8);


        if(left_lines.empty()&&right_lines.empty()){
            if(!(center_lines.empty())){
                displayLine(frame);
            }
        }
        // Detection

        frame_detect = frame.clone();
        if (frame_detect.channels() == 4) cvtColor(frame_detect, frame_detect, COLOR_BGRA2BGR);
        Mat inputBlob = blobFromImage(frame_detect, 1 / 255.F, Size(416, 416), Scalar(), true, false); 
        net.setInput(inputBlob, "data"); 
        Mat detectionMat = net.forward("detection_out"); 
        float confidenceThreshold = 0.24; 
        for (int i = 0; i < detectionMat.rows; i++) { 
        const int probability_index = 5;
        const int probability_size = detectionMat.cols - probability_index;
        float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
        size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr; 
        float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
        if (confidence > confidenceThreshold) {
            float x_center = detectionMat.at<float>(i, 0) * frame_detect.cols;
            float y_center = detectionMat.at<float>(i, 1) * frame_detect.rows; 
            float width = detectionMat.at<float>(i, 2) * frame_detect.cols; 
            float height = detectionMat.at<float>(i, 3) * frame_detect.rows;
            Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2)); 
            Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2)); 
            Rect object(p1, p2);
            Scalar object_roi_color(0, 255, 0);

            rectangle(frame, object, object_roi_color);
            
            String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : cv::format("unknown(%d)", objectClass);
            String label = format("%s detected nearby!", className.c_str(), confidence);
            int baseLine = 0;
            Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            rectangle(frame, Rect(p1, Size(labelSize.width, labelSize.height + baseLine)), object_roi_color, FILLED);
            putText(frame, label, p1 + Point(0, labelSize.height), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0)); 
            }
        }

        imshow("YOLO: Detections", frame); 
        if (waitKey(delay) >= 0) break;
    }
}

void displayCarNearby(Mat src){
    putText(src,format("Alert! Moving object!"),Point(0,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,0),1);
}

void displayLine(Mat src){
    putText(src,format("Lane Departure!!"),Point(40,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,0),2);
}