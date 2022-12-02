#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv; 
using namespace std; 
using namespace dnn;

void displayLine(Mat src);
void displayCarNearby(Mat src);
void displayHuman(Mat src);

int main(){
    Mat frame;
    int delay;
    VideoCapture cap;
    int key;

    //for line
    Rect left(150,200,100,280);
    Rect right(500,200,100,280);
    Rect center(300,230,100,250);
    Mat left_roi, right_roi, center_roi;
    Mat canny_left, canny_right, canny_center;
    Mat frame_copy;
    // float average1_rho=0;
    // float average1_theta=0;
    // float average2_rho=0;
    // float average2_theta=0;
    // float average3_rho = 0;
    // float average3_theta = 0;
    // float a1=0, b1=0, x1=0, y1=0;
    // float a2=0, b2=0, x2=0, y2=0;
    // float a3=0, b3=0, x3=0, y3=0;
    // Point p1, p2, p3, p4, p5, p6;
    vector<Vec2f> left_lines;
    vector<Vec2f> right_lines;
    vector<Vec2f> center_lines;

    //for detect
    Mat frame_detect, frame_near;
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


    //for Moving car
    Rect car_center(220,180,300,300);
    Mat frame_move;
    Mat frame_center;
    Mat background;
    cap >> background;
    background = background(car_center);
    cvtColor(background, background, CV_BGR2GRAY);

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
        Canny(canny_left,canny_left, 10, 70, 3);
        Canny(canny_right,canny_right, 10, 70, 3);
        // imshow("Left canny", canny_left);
        // imshow("Right canny", canny_right);

        //left
        HoughLines(canny_left,left_lines,1,(CV_PI/180),60,0,0,30*(CV_PI/180),60*(CV_PI/180));
        // average1_rho = 0;
        // average1_theta = 0;
        // for (int i = 0; i < left_lines.size(); i++) {
        //     average1_rho = average1_rho+left_lines[i][0];
        //     average1_theta = average1_theta+left_lines[i][1];
        // }
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
        // average2_rho = 0;
        // average2_theta = 0;
        // for (int i = 0; i < right_lines.size(); i++) {
        //     average2_rho = average2_rho+right_lines[i][0];
        //     average2_theta = average2_theta+right_lines[i][1];
        // }
        // average2_rho = average2_rho/right_lines.size();
        // average2_theta = average2_theta/right_lines.size();
        // a2 = cos(average2_theta);
        // b2 = sin(average2_theta);
        // x2 = a2*average2_rho+500;
        // y2 = b2*average2_rho+200;
        // p3 = Point(cvRound(x2 + 1000 * (-b2)), cvRound(y2 + 1000 * a2));
        // p4 = Point(cvRound(x2 - 1000 * (-b2)), cvRound(y2 - 1000 * a2)); 
        // line(frame, p3, p4, Scalar(0, 0, 255), 3, 8);

        //center
        center_roi = frame_copy(center);
        cvtColor(center_roi,center_roi,CV_BGR2GRAY);
        blur(center_roi,canny_center,Size(5,5));
        Canny(canny_center,canny_center, 10, 70, 3);

        HoughLines(canny_center,center_lines,1,(CV_PI/180),65,0,0,150*(CV_PI/180),177*(CV_PI/180));
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
        // imshow("center",canny_center);

        //lane departure
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
                if(p2.y>frame.rows-100){//p1, p2 location
                    String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : cv::format("unknown(%d)", objectClass);
                    // String label = format("%s detected nearby!", className.c_str(), confidence);Scalar object_roi_color(0, 255, 0);
                    if(className=="car"){
                        displayCarNearby(frame);
                    }
                    if(className=="person"){
                        displayHuman(frame);
                    }
                    // int baseLine = 0;

                    // Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                    // putText(frame, label, p1 + Point(0, labelSize.height), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0)); 
                }
                Scalar object_roi_color(0, 0 , 255);
                rectangle(frame, object, object_roi_color);
            }
        }
        // frame_near = frame(Rect(0,frame.rows-100,frame.cols,100));
        // imshow("near",frame_near);

        //Car moving
       
        frame_move = frame_copy(car_center);
        frame_center = frame_copy(car_center);
        Mat gray, foregroundMask, foregroundImg;
        cvtColor(frame_center, gray, CV_BGR2GRAY);
        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 100, 255, CV_THRESH_BINARY); 
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);
        imshow("foregroundImg", foregroundImg); 
        imshow("foregroundMask", foregroundMask); 
        imshow("background", background);

        if (frame_move.channels() == 4) cvtColor(frame_move, frame_move, COLOR_BGRA2BGR);
        inputBlob = blobFromImage(frame_move, 1 / 255.F, Size(416, 416), Scalar(), true, false); 
        net.setInput(inputBlob, "data"); 
        detectionMat = net.forward("detection_out"); 
        confidenceThreshold = 0.24; 
        for (int i = 0; i < detectionMat.rows; i++) { 
            const int probability_index = 5;
            const int probability_size = detectionMat.cols - probability_index;
            float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
            size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr; 
            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
            if (confidence > confidenceThreshold) {
                float x_center = detectionMat.at<float>(i, 0) * frame_move.cols;
                float y_center = detectionMat.at<float>(i, 1) * frame_move.rows; 
                float width = detectionMat.at<float>(i, 2) * frame_move.cols; 
                float height = detectionMat.at<float>(i, 3) * frame_move.rows;
                Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2)); 
                Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2)); 
                Rect object(p1, p2);
                // if(object.area()>5000){
                    Scalar object_roi_color(0, 0 , 255);
                    rectangle(frame_center, object, object_roi_color);
                //}
                
            }
        }

        imshow("test", frame_center);


        imshow("Project3", frame); 
        key = waitKey(delay);
        if(key!=-1) break;
        // if(key==97){
        //     cap.get(CAP_PROP_POS_FRAMES);
        //     cap.
        // }
            
        // if(key==100)
        //     cap.get(CAP_PROP_POS_FRAMES);
    }
}

void displayCarNearby(Mat src){
    putText(src,format("Car detected nearby"),Point(src.cols/2,80),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}
void displayLine(Mat src){
    putText(src,format("Lane Departure!!"),Point(src.cols/2,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}
void displayHuman(Mat src){
    putText(src,format("Human detected nearby!!"),Point(src.cols/2,120),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}