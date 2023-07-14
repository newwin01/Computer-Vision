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
void displayMovingCar(Mat src);

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
    vector<Vec2f> left_lines;
    vector<Vec2f> right_lines;
    vector<Vec2f> center_lines;

    //for detect
    Mat frame_detect, frame_near;
    String modelConfiguration = "deep/yolov2-tiny.cfg"; 
    String modelBinary = "deep/yolov2-tiny.weights";
    Net net = readNetFromDarknet(modelConfiguration, modelBinary);
    if (cap.open("Project3_2.mp4") == 0) {
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
    Rect car_center(200,0,300,480);
    Mat frame_move;
    Mat frame_center;
    Mat background;
    cap >> background;
    background = background(car_center);
    cvtColor(background, background, CV_BGR2GRAY);
    int frame_count=0;
    Point p1_temp;
    Point p2_temp;
    int decision=0;

    int decision_car=0;
    int decision_human=0;
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

        //left
        HoughLines(canny_left,left_lines,1,(CV_PI/180),60,0,0,30*(CV_PI/180),60*(CV_PI/180));

        //right
        HoughLines(canny_right,right_lines,1,(CV_PI/180),60,0,0,120*(CV_PI/180),150*(CV_PI/180));

        //center
        center_roi = frame_copy(center);
        cvtColor(center_roi,center_roi,CV_BGR2GRAY);
        blur(center_roi,canny_center,Size(5,5));
        Canny(canny_center,canny_center, 10, 70, 3);

        HoughLines(canny_center,center_lines,1,(CV_PI/180),65,0,0,150*(CV_PI/180),177*(CV_PI/180));

        //lane departure
        if(left_lines.empty()&&right_lines.empty()){
            if(!(center_lines.empty())){
                displayLine(frame);
            }
        }
        // Detection
        frame_detect = frame.clone();
        if(frame_count%1==0){
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
                String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : cv::format("unknown(%d)", objectClass);
                decision_car=0;
                decision_human=0;
                if(p2.y>frame.rows-100||p1.y>frame.rows-100){//p1, p2 location
                    if(className=="car"){
                        displayCarNearby(frame);  
                    }
                    if(className=="person"){
                        displayHuman(frame);
                    }
                }
                Scalar object_roi_color(0, 0 , 255);
                rectangle(frame, object, object_roi_color);
                }
            }    
        }

         //Car moving
        frame_move = frame_copy(car_center);
        frame_center = frame_copy(car_center);
        int detect_stay = 0;
        if (frame_move.channels() == 4) cvtColor(frame_move, frame_move, COLOR_BGRA2BGR);
        Mat inputBlob = blobFromImage(frame_move, 1 / 255.F, Size(416, 416), Scalar(), true, false); 
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
                float x_center = detectionMat.at<float>(i, 0) * frame_move.cols;
                float y_center = detectionMat.at<float>(i, 1) * frame_move.rows; 
                float width = detectionMat.at<float>(i, 2) * frame_move.cols; 
                float height = detectionMat.at<float>(i, 3) * frame_move.rows;
                Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2)); 
                Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2)); 
                Rect object(p1, p2);
                String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : cv::format("unknown(%d)", objectClass);
                if(className=="car"&&(object.area()>13000)){ // car is staying
                    if(p1_temp.x==0&&p2_temp.x==0){
                        p1_temp=p1;
                        p2_temp=p2;
                    }
                    Scalar object_roi_color(0, 0 , 255);
                    rectangle(frame_center, object, object_roi_color);
                    if(frame_count%3==0){
                        if(p1_temp.x<p1.x-3||p2_temp.x-3>p2.x){
                            if(p1_temp.y<p1.y-3||p2_temp.y-3>p2.y)
                                decision=1;
                            else decision=0;
                        }
                    }
                    if(decision==1) displayMovingCar(frame);
                    if(frame_count%40==0){
                        if(!(p1.x==0)&&!(p1.y==0)){
                            p1_temp=p1;
                        }
                        if(!(p2.x==0)&&!(p1.y==0)){
                            p2_temp=p2;
                        }
                    }
                }
            }
        }

        imshow("Project3", frame); 
        key = waitKey(delay);
        frame_count++;
        if(key!=-1) break;
    }
}

void displayCarNearby(Mat src){
    putText(src,format("Car detected nearby"),Point(src.cols/2,80),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}
void displayLine(Mat src){
    putText(src,format("Lane Departure!!"),Point(src.cols/2,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}
void displayHuman(Mat src){
    putText(src,format("Human detected nearby!!"),Point(src.cols/2-100,120),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}
void displayMovingCar(Mat src){
    putText(src,format("Car is moving!!"),Point(src.cols/2,160),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
}