#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main() {
	CascadeClassifier face_classifier; 
	Mat frame, grayframe; 
	vector<Rect> faces; 
	vector<Rect> blue_rect;
	int i;
	int t_press=0;
	face_classifier.load("haarcascade_frontalface_alt.xml");
	int delay, press=82, prev_press;
	int face_press=0;
	VideoCapture cap;
	Mat blue_frame(frame.cols, frame.rows, CV_8UC3, Scalar(255, 0, 0));
	Rect blue_rectangle;
	Mat result, bgdModel, fgdModel, image, foreground;


	if (cap.open("Faces.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
	delay = 1000 / cap.get(CAP_PROP_FPS);
	while (1) {
		cap >> frame;
		if (frame.empty()) {
			cout << "end of video" << endl;
			break;
		}
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);
		if (press == 78 || press == 110) {//n,N
			image = frame.clone();
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 5, 0, Size(80, 80), Size(90, 90));
			i=0;
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height); 
			Point tr(faces[i].x, faces[i].y); 
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			blue_rectangle =  Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height);
			if(t_press==1){
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT); 
				compare(result, GC_PR_FGD, result, CMP_EQ); 
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("blue", foreground);
				imshow("FaceDetection", image); 
			} else if(t_press==0){
				imshow("FaceDetection", image);
			}
		}
		else if (press == 77 || press == 109) {//m,M
			image = frame.clone();
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 5, 0, Size(50, 50), Size(60, 60));
			i=0;
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height); 
			Point tr(faces[i].x, faces[i].y); 
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			blue_rectangle =  Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height);
			if(t_press==1){
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT); 
				compare(result, GC_PR_FGD, result, CMP_EQ); 
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("blue", foreground);
				imshow("FaceDetection", image); 
			} else if(t_press==0){
				imshow("FaceDetection", image);
			}
		}	else if (press == 70 || press == 102) {//F,f
			i=0;
			image = frame.clone();
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 5, 0, Size(25, 25), Size(40,40));
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			blue_rectangle =  Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height);
			if(t_press==1){
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT); 
				compare(result, GC_PR_FGD, result, CMP_EQ); 
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("blue", foreground);
				imshow("FaceDetection", image); 
			} else if(t_press==0){
				imshow("FaceDetection", image);
			}
		} else if (press == 82 || press == 114) {//R, r
			press=82;
			imshow("FaceDetection", frame);
		} else if(t_press == 0 && (press == 84 || press == 116)){ //need detection
			putText(frame,format("Detect before tracking"),Point(0,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),1);
			imshow("FaceDetection", frame);
		} 
		prev_press = waitKey(delay);
		if (prev_press != -1) {
			if(prev_press==78||prev_press==110||prev_press==77||prev_press==109||prev_press==70||prev_press==102||prev_press==82||prev_press==114||prev_press==84||prev_press==116){
				if((press!=82)&&(prev_press == 84 || prev_press == 116)&&t_press==0){
					t_press=1;
				} else if((prev_press == 84 || prev_press == 116)&&(t_press==1)){
					t_press=0;
				}else{
					press = prev_press;
				}
			}
		}
	}
	waitKey(0);
}