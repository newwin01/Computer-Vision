#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
// Mat image, canny;
// image = imread("lena.png", 0);
// //performs canny edge detection
// //image: input Mat, canny: output Mat //190: Thresh_low of double thresholding //200: Thresh_high of double thresholding //3: aperture size of the Sobel operation 
// Canny(image, canny, 190, 200, 3);
// imshow("Input image", image);
// imshow("canny", canny);
// waitKey(0); 

Mat image, edge, result;
float rho, theta, a, b, x0, y0;
Point p1, p2;
vector<Vec2f> lines;
image = imread("chess_pattern.png"); 
result = image.clone();
cvtColor(image, image, CV_BGR2GRAY); 
Canny(image, edge, 50, 200, 3);
//applying Hough Transform to find lines in the image
//edge: input Mat, lines: output vector of lines
//1: (rho) distance resolution of the accumulator in pixels 
//CV_PI/180: (theta) angle resolution of the accumulator in radians 
//150: (threshold) accumulator threshold parameter
//minimum angle to check for lines. Must fall between 0 and max_theta. 
//maximum angle to check for lines. Must fall between min_theta and CV_PI 
HoughLines(edge, lines, 1, CV_PI / 180, 150,0,CV_PI);
for (int i = 0; i < lines.size(); i++) { 
    rho = lines[i][0];
    theta = lines[i][1]; a = cos(theta);
    b = sin(theta);
    x0 = a * rho; y0 = b * rho;
    p1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * a)); 
    p2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * a));
    line(result, p1, p2, Scalar(0, 0, 255), 3, 8);
}
imshow("Input image", image); 
imshow("edge", edge); 
imshow("Hough Transform", result); 
waitKey(0);


}