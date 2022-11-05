
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
	int t_press = 0;
	face_classifier.load("haarcascade_frontalface_alt.xml");
	int delay, press = 82, prev_press;
	int face_press = 0;
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
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(75, 75), Size(100, 100));
			if (faces.size() > 1) {
				if (faces[0].area() > faces[1].area()) {
					i = 0;
				}
				else {
					i = 1;
				}
			}
			else {
				i = 0;
			}
			if (faces.empty()) {
				continue;
			}
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			Point text(lb.x - 20, lb.y);
			putText(image, format("n"), text, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1);
			blue_rectangle = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
			if (t_press == 1) {
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT);
				compare(result, GC_PR_FGD, result, CMP_EQ);
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("tracking", foreground);
				imshow("Faces", image);
			}
			else if (t_press == 0) {
				imshow("Faces", image);
			}
		}
		else if (press == 77 || press == 109) {//m,M
			image = frame.clone();
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(35, 35), Size(55, 55));
			if (faces.size() > 1) {
				if (faces[0].area() > faces[1].area()) {
					i = 0; 
				}
				else {
					i = 1; 
				}
			}
			else {
				i = 0;
			}
			if (faces.empty()) {
				continue;
			}
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			blue_rectangle = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
			Point text(lb.x - 25, lb.y);
			putText(image, format("m"), text, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 1);
			if (t_press == 1) {
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT);
				compare(result, GC_PR_FGD, result, CMP_EQ);
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("tracking", foreground);
				imshow("Faces", image);
			}
			else if (t_press == 0) {
				imshow("Faces", image);
			}
		}
		else if (press == 70 || press == 102) {//F,f
			image = frame.clone();
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(25, 25), Size(40, 40));
			if (faces.size() > 1) {
				if (faces[0].area() < faces[1].area()) {
					i = 0;
				}
				else {
					i = 1;
				}
			}
			else {
				i = 0;
			}
			if (faces.empty()) {
				continue;
			}
			i = 0;
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			rectangle(image, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			blue_rectangle = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
			Point text(lb.x - 15, lb.y);
			putText(image, format("f"), text, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 1);
			if (t_press == 1) {
				grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT);
				compare(result, GC_PR_FGD, result, CMP_EQ);
				foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
				frame.copyTo(foreground, result);
				imshow("tracking", foreground);
				imshow("Faces", image);
			}
			else if (t_press == 0) {
				imshow("Faces", image);
			}
		}
		else if (press == 82 || press == 114) {//R, r
			press = 82;
			imshow("Faces", frame);
		}
		else if (t_press == 0 && (press == 84 || press == 116)) { //need detection
			putText(frame, format("Detect before tracking"), Point(0, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
			imshow("Faces", frame);
		}
		prev_press = waitKey(delay);
		if (prev_press != -1) {
			if (prev_press == 78 || prev_press == 110 || prev_press == 77 || prev_press == 109 || prev_press == 70 || prev_press == 102 || prev_press == 82 || prev_press == 114 || prev_press == 84 || prev_press == 116) {
				if ((press != 82) && (prev_press == 84 || prev_press == 116) && t_press == 0) {
					t_press = 1;
				}
				else if ((prev_press == 84 || prev_press == 116) && (t_press == 1)) {
					destroyWindow("tracking");
					t_press = 0;
				}
				else {
					press = prev_press;
				}
			}
		}
	}
	waitKey(0);
}
