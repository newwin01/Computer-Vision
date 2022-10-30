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
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(65, 65), Size(80, 80));
			for (i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height); 
				Point tr(faces[i].x, faces[i].y); 
				rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			face_press = 78;
			imshow("FaceDetection", frame);
		}
		else if (press == 77 || press == 109) {//m,M
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(45, 45), Size(60, 60));
			for (i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				Point tr(faces[i].x, faces[i].y);
				rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			face_press = 77;
			imshow("FaceDetection", frame);
		}	else if (press == 70 || press == 102) {//F,f
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(35, 35), Size(45, 45));
			for (i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				Point tr(faces[i].x, faces[i].y);
				rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
			}
			face_press = 70;
			imshow("FaceDetection", frame);
		} else if (press == 82 || press == 114) {//R, r
			face_press = 0;
			imshow("FaceDetection", frame);
		} else if (face_press == 78 && (press == 84 || press == 116)) {//n & t
			face_classifier.detectMultiScale(grayframe, faces, 1.1, 3, 0, Size(65, 65), Size(80, 80));
			for (i = 0; i < faces.size(); i++) {
				Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				Point tr(faces[i].x, faces[i].y);
				blue_rectangle =  Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height);
			}
			i = 0;
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			blue_rectangle = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
			grabCut(frame, result, blue_rectangle, bgdModel, fgdModel, 10, GC_INIT_WITH_RECT); 
			compare(result, GC_PR_FGD, result, CMP_EQ); 
			foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 0, 0));
			image.copyTo(foreground, result);
			imshow("blue", result);
			imshow("FaceDetection", frame);

		}
		else {
			imshow("FaceDetection", frame);
		}
		prev_press = waitKey(delay);
		if (prev_press != -1) {
				press = prev_press;
		}

	}

	waitKey(0);
}