#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat drawHistogram(Mat src);
void displayImage(Mat src,String title);

int main(){
    Mat moon_img = imread("moon.png",0);
    if(moon_img.empty()) exit(-1);

    Mat moon_hist_img,moon_graph,moon_hist_graph;
    moon_graph = drawHistogram(moon_img);
    
    equalizeHist(moon_img,moon_hist_img);
    moon_hist_graph = drawHistogram(moon_hist_img);


    displayImage(moon_img,"before");
    displayImage(moon_hist_img,"after");

    imshow("h1",moon_graph);
    imshow("h2",moon_hist_graph);

    waitKey(0);

    return 0;
}


void displayImage(Mat src,String title){
    Mat hist;
    int histSize = 8;
    int position = 0;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    int height, width;
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange); 
    height = src.rows;
    width = src.cols;

    for(int i=0;i<histSize;i++){
        putText(src,format("bin%d: %f",i+1,(hist.at<float>(i)/(height*width))),Point(0,40+position),FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255),1);
        position=position+20;
    }
    imshow(title,src);
}

Mat drawHistogram(Mat src){
    Mat hist, histImage;
    // establish the number of bins
    int i, hist_w, hist_h, bin_w, histSize; 
    float range[] = { 0, 256 };
    const float* histRange = { range };
    hist_w = 512;//size of histogram
    hist_h = 512;
    //number of bins
    histSize = 16;
    bin_w = cvRound((double)hist_w / histSize);
    //draw the histogram
    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
    
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    for (i = 0; i < histSize; i++)
    {
        rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i+hist_w/histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
    }
    return histImage; 
}