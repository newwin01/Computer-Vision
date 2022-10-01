#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat white_balacing(Mat img);

int main(){
	Mat frame;
    Mat final_frame;
	int delay;
	VideoCapture cap;
    char key='\0';
    char press_real='r';
    int rows,cols;
    //gamma
    float gamma = 2.5;
    unsigned char pix[256];
    MatIterator_<Vec3b> it, end;

    //HSI
    Mat HSV;
    vector<Mat> ic(3);
    uchar* h;
    uchar* s;

    for(int i=0;i<256;i++){
        pix[i] = saturate_cast<uchar>(pow((float)(i/255.0),gamma)*255.0f);
    }

	// check file existence
	if (cap.open("road.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}
	delay = 1000/cap.get(CAP_PROP_FPS);
    bool first = false;

	while (1) {
		cap >> frame;
		if (frame.empty()) {
			cout << "end of video" << endl;
			break;
		}
        rows = frame.rows;
        cols = frame.cols;
       
        if (press_real=='n'){//negative conversion
            cvtColor(frame,frame,CV_BGR2HSV);
            split(frame,ic);
            for (int j = 0; j < rows; j++) {
                h = ic[2].ptr<uchar>(j);
                for (int i = 0; i < cols; i++) {
                    h[i]=255-h[i];
                }
            }
            merge(ic,final_frame);
            cvtColor(final_frame,final_frame,CV_HSV2BGR);
        }  //gamma
        else if(press_real=='g'){
            cvtColor(frame,frame,CV_BGR2HSV);
            split(frame,ic);
            for(int j=0;j<rows;j++){
                h=ic[2].ptr<uchar>(j);
                for(int i=0;i<cols;i++){
                    h[i] = pix[h[i]];
                }
            }
            merge(ic,final_frame);
            cvtColor(final_frame,final_frame,CV_HSV2BGR);
        }
        else if(press_real=='h'){ //histogram equalization
            cvtColor(frame,frame,CV_BGR2HSV);
            split(frame, ic);
            equalizeHist(ic[2], ic[2]);
            merge(ic,final_frame);
            cvtColor(final_frame,final_frame, CV_HSV2BGR);
        }//color slicing Hue 9<h<23
        else if(press_real=='s'){
            cvtColor(frame,frame,CV_BGR2HSV);
            split(frame, ic);
             for (int j = 0; j < rows; j++) {
                h = ic[0].ptr<uchar>(j);
                s = ic[1].ptr<uchar>(j);
                for (int i = 0; i < cols; i++) {
                    if (h[i] > 9 && h[i] < 23) s[i] = s[i];
                        else s[i] = 0;
                }
            }
            merge(ic,final_frame);
            cvtColor(final_frame,final_frame, CV_HSV2BGR);
        }//color conversion 
        else if(press_real=='c'){
            cvtColor(frame,frame,CV_BGR2HSV);
            split(frame,ic);
            for (int j = 0; j < rows; j++) {
                h = ic[0].ptr<uchar>(j);
                for (int i = 0; i < cols; i++) {
                    if (h[i] > 129) h[i] = h[i] -129 ; else h[i] += 50;
                }
            }
            merge(ic,final_frame);
            cvtColor(final_frame,final_frame, CV_HSV2BGR);
        }
        //avg filtering
        else if(press_real=='a'){
            // cvtColor(frame,frame,CV_BGR2HSV);
            // split(frame,ic);
            // blur(ic[2],ic[2],Size(9,9));
            // merge(ic,final_frame);
            // cvtColor(final_frame,final_frame,CV_HSV2BGR);
            blur(frame,final_frame,Size(9,9));
        }
        else if(press_real=='w'){
            final_frame = white_balacing(frame);
        }
        else if(press_real==27){
            exit(-1);
        }
        else if(press_real=='r'){
            final_frame = frame;
        }
        else{
           exit(-1);
        }
        imshow("video",final_frame);
        key = waitKey(delay);
        if(key!=-1){
            if(key=='n'||key=='g'||key=='h'||key=='s'||key=='c'||key=='a'||key=='w'||key=='r'||key==27)
                press_real = key;
        } 
    }
	waitKey(0);
}

Mat white_balacing(Mat img) { 
    Mat bgr_channels[3]; 
    split(img, bgr_channels);
    double avg;
    int sum,temp,i, j, c;
    for (c = 0; c < img.channels(); c++) { 
        sum = 0;
        avg = 0.0f;
    for (i = 0; i < img.rows; i++) {
        for (j = 0; j < img.cols; j++) {
            sum += bgr_channels[c].at<uchar>(i, j);
        }
    }
    avg = sum / (img.rows * img.cols);
    for (i = 0; i < img.rows; i++) {
        for (j = 0; j < img.cols; j++) {
            temp = (128 / avg) * bgr_channels[c].at<uchar>(i, j);
            if (temp>255) bgr_channels[c].at<uchar>(i, j) = 255; 
            else bgr_channels[c].at<uchar>(i, j) = temp;
            }
        }
    }
    merge(bgr_channels, 3, img); 
    return img;
}