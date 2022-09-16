#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    
    Mat moon_gray_image,saltnpepper;
    moon_gray_image = imread("moon.png",0);
    saltnpepper = imread("saltnpepper.png",0);
    //sharpening using unshapmask
    //set left half of image
    int height_moon, width_moon;
    height_moon = moon_gray_image.rows;
    width_moon = moon_gray_image.cols;
    Rect rect_moon(width_moon/2,0,width_moon/2,height_moon);
    //set matrixs for blur, original cropped image, original image
    Mat moon_filtered = moon_gray_image.clone();
    Mat rect_image = moon_gray_image(rect_moon);
    Mat original_moon = rect_image.clone();
    Mat moon_croped;
    //use GaussianBlur
    GaussianBlur(rect_image,moon_croped,Size(3,3),0);
    Mat moon_final;
    //subtract and add scale
  
    subtract(original_moon,moon_croped,moon_final);
    // moon_final = original_moon + (moon_final*0.5);
    scaleAdd(moon_final,1.0,original_moon,moon_final);
    //sharpened image to original image
    moon_final.copyTo(moon_filtered(rect_moon));
    



    // median filter on the right half of saltnpepper image
    int height = saltnpepper.rows;
    int width = saltnpepper.cols;
    Rect rect(0,0,width/2,height);
    Mat saltnpepper_result = saltnpepper.clone();
    medianBlur(saltnpepper_result(rect),saltnpepper_result(rect),9);

    
    // display results
    imshow("moon",moon_gray_image);
    imshow("moon_filterd",moon_filtered);
    imshow("saltnpepper",saltnpepper);
    imshow("saltnpepper_filtered",saltnpepper_result);


    waitKey(0);
    return 0;
}