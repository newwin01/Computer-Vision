#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	// Mat img = imread("lena.png");

	// if (img.empty()) {
	// 	cerr << "image reading is failed!" << endl;
	// 	exit(-1);
	// }

	// imshow("lena", img);
	// waitKey(0);

	//example 1 

	//int w = 150, h = 100;
	//Mat image(h, w, CV_8UC1, Scalar(255));
	//cout << "Size: " << image.size().height << "," << image.size().width << endl;
	//imshow("image", image);
	//waitKey(0);
	//return 0;

	//example 2

	//Mat m1 = (Mat_ < double >(3, 3)	<< 1, 2, 3, 4, 5, 6, 7, 8, 9);
	//Mat m_shallow = m1;
	//Mat m_deep = m1.clone();
	//cout << "m1 =\n" << m1 << endl << endl;
	//cout << "m_shallow =\n" << m_shallow << endl << endl;
	//cout << "m_deep =\n" << m_deep << endl << endl;
	//// Update m1 
	//m1.at < double >(0, 0) = 100;
	//cout << "m1 =\n" << m1 << endl << endl;
	//cout << "m_shallow =\n" << m_shallow << endl << endl;
	//cout << "m_deep =\n" << m_deep << endl << endl;
	//waitKey(0);

	//example 3

	//Mat image = imread("lena.png", 0);
	//Mat copied_img = image.clone();

	//Mat image = imread("lena.png");
	//Mat mask = Mat::zeros(image.size(), image.type());
	//Mat copied;
	//Rect rect = Rect(10, 10, 100, 100); // LT position, width, height
	//rectangle(mask, rect, Scalar(255, 0, 0), -1, 8, 0);
	//image.copyTo(copied, mask);
	//imshow("original", image);
	//imshow("copied", copied);
	//waitKey(0);
	//return 0;

	//example 4

	//Mat image = imread("lena.png");
	//Mat after_convertTo, after_convertScaleAbs;
	//imshow("original", image);
	//image.convertTo(after_convertTo, CV_16SC1);
	//imshow("after convertTo", after_convertTo);
	//convertScaleAbs(image, after_convertScaleAbs, 2, 3);
	//imshow("after convertScaleAbs", after_convertScaleAbs);
	//image.setTo(Scalar(0));
	//imshow("after setTo", image);
	//waitKey(0);


	//Mat frame;
	//VideoCapture cap;
	//// check if file exists. if none program ends
	//if (cap.open("background.mp4") == 0) {
	//	cout << "no such file!" << endl;
	//	waitKey(0);
	//}
	//double fps = cap.get(CAP_PROP_FPS);
	//double time_in_msec = cap.get(CAP_PROP_POS_MSEC);
	//int total_frames = cap.get(CAP_PROP_FRAME_COUNT);

	Mat frame;
	int fps;
	int total_fps;
	int delay;
	VideoCapture cap;
	// check file existence
	if (cap.open("background.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
	total_fps = cap.get(CAP_PROP_FRAME_COUNT);
	delay = 1000/cap.get(CAP_PROP_FPS);
	while (cap.get(CAP_PROP_POS_MSEC)<3000) {
		cap >> frame;
		if (frame.empty()) {
			cout << "end of video" << endl;
			break;
		}
		imshow("video", frame);
		fps = cap.get(CAP_PROP_POS_FRAMES);
		cout << "Frame: " << fps << " / " << total_fps << endl;
		waitKey(delay);
	}
	waitKey(0);
}