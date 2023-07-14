#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {


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