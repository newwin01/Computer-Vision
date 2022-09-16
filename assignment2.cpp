#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat gray_image, result_img,rotated_img;
    MatIterator_<uchar> it, end;
    float gamma = 10.0;
    unsigned char pix[256];
//gamma scale
    for(int i=0;i<256;i++){
        pix[i] = saturate_cast<uchar>(pow((float)(i/255.0),gamma)*255.0f);
    }

    gray_image = imread("lena.png",0);
    rotated_img = gray_image.clone();
//rotate image
    for(int j=0;j<gray_image.rows;j++){
        for(int i=0;i<gray_image.cols;i++){
           rotated_img.at<uchar>(gray_image.rows-i-1,j) = gray_image.at<uchar>(j,i);
        }
    }

    result_img = rotated_img.clone();
//transformation
    for(int j=0; j<rotated_img.rows;j++){
        for(int i=0;i<rotated_img.cols;i++){
            if(rotated_img.at<uchar>(j,i)<127)
                result_img.at<uchar>(j,i) = 255-rotated_img.at<uchar>(j,i);
            else 
                result_img.at<uchar>(j,i) = pix[rotated_img.at<uchar>(j,i)];
        }
    }

    imshow("gray image",gray_image);
    imshow("result",result_img);
    waitKey(0);
}