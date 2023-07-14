#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
//     Mat image, AvgImg, GaussianImg; image = imread("lena.png");
// // Blurs an image using the normalized box filter
// // image: input image, AvgImg: output image, Size(5, 5): blurring kernel size 
//     blur(image, AvgImg, Size(5, 5));
// // Blurs an image using a Gaussian filter
// // image: input image, GaussianImg: output image, Size(5, 5): Gaussian kernel size 
// // 1.5: Gaussian kernel standard deviation in X direction
//     GaussianBlur(image, GaussianImg, Size(5, 5), 1.5);
//     imshow("Input image", image);
//     imshow("Average image", AvgImg); 
//     imshow("Gaussian blurred image", GaussianImg);
//     waitKey(0);
//     return 0;



    // Mat image, laplacian, abs_laplacian, sharpening; 
    // image = imread("Moon.png", 0);
    // GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT); // calculates the Laplacian of an image
    // // image: src, laplacian: dst, CV_16S: desire depth of dst,
    // // 1: aperture size used to compute second-derivative (optional) 
    // // 1: optional scale factor for the computed Laplacian values
    // // 0: optional delta value that is added to the result 
    // Laplacian(image, laplacian, CV_16S, 1, 1, 0); 
    // convertScaleAbs(laplacian, abs_laplacian); sharpening = abs_laplacian + image;
    // imshow("Input image", image); 
    // imshow("Laplacian", laplacian); 
    // imshow("abs_Laplacian", abs_laplacian); 
    // imshow("Sharpening", sharpening);
    // waitKey(0);

    Mat image = imread("saltnpepper.png", 0);
    imshow("SaltAndPepper", image);
    Mat mf1, mf2;
    // Blurs an image using the median filter
    // image: src, mf1: dst, 3: aperture size(must be odd and greater than 1) 
    medianBlur(image, mf1, 3);
    imshow("MedianFiltered1", mf1);
    medianBlur(image, mf2, 9); imshow("MedianFiltered2", mf2);
    waitKey(0);
    return 0;
}