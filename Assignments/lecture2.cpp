#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// int main() {
//     Mat image, image_gray;
//     int value, value_B, value_G, value_R, channels;
//     image = imread("lena.png");
//     image_gray = imread("lena.png", 0);
//     //at operator
//     value = image_gray.at<uchar>(50, 100);
//     cout << "value: " << value << endl;
//     value_B = image.at<Vec3b>(50, 100)[0];
//     value_G = image.at<Vec3b>(50, 100)[1];
//     value_R = image.at<Vec3b>(50, 100)[2];
//     cout << "value at (100,50): " << value_B << " " << value_G << " " << value_R << endl;
//     waitKey(0);
// }

// int main() {
//     Mat image = imread("lena.png");
//     int value, value_B, value_G, value_R, channels;
//     channels = image.channels();
//     //pointer
//     uchar* p;
//     p = image.ptr<uchar>(50);
//     value_B = p[100 * channels + 0];
//     value_G = p[100 * channels + 1];
//     value_R = p[100 * channels + 2];
//     cout << "value at (100,50): " << value_B << " " << value_G << " " << value_R << endl;
//     waitKey(0);
// }

//negative transformation 
// int main() {
//     Mat image = imread("lena.png", 0);
//     Mat negative_img = image.clone();
//     for (int j = 0; j < image.rows; j++)
//         for (int i = 0; i < image.cols; i++)
//             negative_img.at<uchar>( j, i) = 255 - image.at<uchar>( j, i);
//     imshow("Input image", image);
//     imshow("Negative transformation", negative_img);
//     waitKey(0);
//     return 0;
// }

//log transformation
// int main() {
//     Mat image = imread("lena.png", 0);
//     Mat f_img, log_img;
//     double c = 1.5f; // scale constant
//     image.convertTo(f_img, CV_32F);
//     f_img = abs(f_img) + 1;
//     log(f_img, f_img);
//     normalize(f_img, f_img, 0, 255, NORM_MINMAX); // normalize image to (0~255)
//     convertScaleAbs(f_img, log_img, c); // scaling by c, conversion to an unsigned 8-bit type
//     imshow("Input image", image);
//     imshow("Log transformation", log_img);
//     waitKey(0);
// }

//gamma transformation
int main() {
    Mat image = imread("lena.png", 0);
    Mat gamma_img;
    MatIterator_<uchar> it, end;
    float gamma = 0.5;
    unsigned char pix[256];
    for (int i = 0; i < 256; i++) {
        pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f );
    }
    gamma_img = image.clone();
    for (int j = 0; j < image.rows; j++)
        for (int i = 0; i < image.cols; i++)
            gamma_img.at<uchar>( j, i) = pix[gamma_img.at<uchar>( j, i)];

    imshow("Input image", image);
    imshow("Gamma transformation", gamma_img);
    waitKey(0);
}