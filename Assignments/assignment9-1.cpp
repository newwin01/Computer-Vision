#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

double calculating_PSNR(Mat original, Mat frame);

int main(){
    Mat quantization_mat1 = (Mat_<double>(8, 8) << 16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68, 109, 103, 77, 24, 35, 55, 64, 81, 104, 113, 92, 49, 64, 78, 87, 103, 121, 120, 101, 72, 92, 95, 98, 112, 100, 103, 99 );

    Mat quantization_mat2 = (Mat_<double>(8, 8) << 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 );

    Mat quantization_mat3 = (Mat_<double>(8, 8) << 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 );

    Mat image;
    Mat image_ycbcr;
    Mat Ycbcr_channels[3]; 
    Mat y(512, 512, CV_8UC1);
    Mat y_con(512,512,CV_32FC1);
    Mat final(512,512,CV_8UC1);
    image = imread("Lena.png", IMREAD_COLOR); 
    cvtColor(image, image_ycbcr, CV_BGR2YCrCb); 
    split(image_ycbcr, Ycbcr_channels);
    for (int j = 0; j < 512; j++){ 
        for (int i = 0; i < 512; i++){
            y.at<uchar>(j, i) = 0;
            y.at<uchar>(j, i) = Ycbcr_channels[0].at<uchar>(j,i); 
        }
    }

    y.convertTo(y,CV_32FC1);
    
    Mat crop;
    for(int k=0;k<512;k=k+8){
        for(int j=0;j<512;j=j+8){
            Rect rect_crop(k,j,8,8);
            crop = y(rect_crop);
            dct(crop,crop,0);
        }
    }
    Mat final_1(512,512,CV_32FC1);
    for(int k=0;k<512;k=k+8){
        for(int a=0;a<512;a=a+8){
            for(int i=k;i<k+8;i++){
                for(int j=a;j<a+8;j++){
                    final_1.at<float>(i,j)=round(y.at<float>(i,j)/quantization_mat1.at<double>(i-k,j-a));
                    final_1.at<float>(i,j)=final_1.at<float>(i,j)*quantization_mat1.at<double>(i-k,j-a);
                }
            }
        }
    }
    for(int k=0;k<512;k=k+8){
        for(int j=0;j<512;j=j+8){
            Rect rect_crop(k,j,8,8);
            crop = final_1(rect_crop);
            dct(crop,crop,1);
        }
    }
    final_1.convertTo(final_1,CV_8UC1);
    imshow("QM1",final_1);
    
    

    Mat final_2(512,512,CV_32FC1);
    for(int k=0;k<512;k=k+8){
        for(int a=0;a<512;a=a+8){
            for(int i=k;i<k+8;i++){
                for(int j=a;j<a+8;j++){
                    final_2.at<float>(i,j)=round(y.at<float>(i,j)/quantization_mat2.at<double>(i-k,j-a));
                    final_2.at<float>(i,j)=final_2.at<float>(i,j)*quantization_mat2.at<double>(i-k,j-a);
                }
            }
        }
    }
    for(int k=0;k<512;k=k+8){
        for(int j=0;j<512;j=j+8){
            Rect rect_crop(k,j,8,8);
            crop = final_2(rect_crop);
            dct(crop,crop,1);
        }
    }
    final_2.convertTo(final_2,CV_8UC1);
    imshow("QM2",final_2);


    Mat final_3(512,512,CV_32FC1);
    for(int k=0;k<512;k=k+8){
        for(int a=0;a<512;a=a+8){
            for(int i=k;i<k+8;i++){
                for(int j=a;j<a+8;j++){
                    final_3.at<float>(i,j)=round(y.at<float>(i,j)/quantization_mat3.at<double>(i-k,j-a));
                    final_3.at<float>(i,j) = final_3.at<float>(i,j)*quantization_mat3.at<double>(i-k,j-a);
                }
            }
        }
    }
    for(int k=0;k<512;k=k+8){
        for(int j=0;j<512;j=j+8){
            Rect rect_crop(k,j,8,8);
            crop = final_3(rect_crop);
            dct(crop,crop,1);
        }
    }
    final_3.convertTo(final_3,CV_8UC1);
    imshow("QM3",final_3);

    for(int k=0;k<512;k=k+8){
        for(int j=0;j<512;j=j+8){
            Rect rect_crop(k,j,8,8);
            crop = y(rect_crop);
            dct(crop,crop,1);
        }
    }

    y.convertTo(y,CV_8UC1);
    imshow("Original Y",y);
    cout.precision(8);
    cout << "QM1: psnr = " << PSNR(y,final_1) << endl;
    cout << "QM1: my psnr = " << calculating_PSNR(y,final_1) << endl;
    cout << "QM2: psnr = " << PSNR(y,final_2) << endl;
    cout << "QM2: my psnr = " << calculating_PSNR(y,final_2) << endl;
    cout << "QM3: psnr = " << PSNR(y,final_3) << endl;
    cout << "QM3: my psnr = " << calculating_PSNR(y,final_3) << endl;

    waitKey(0);
    return 0;
}

double calculating_PSNR(Mat original, Mat frame){
    double PSNR = 0.0;
    double MSE = 0.0;
    double value = 0.0;
    for(int i=0;i<512;i++){
        for(int j=0;j<512;j++){
            value = original.at<uchar>(i,j) - frame.at<uchar>(i,j);
            MSE = value*value + MSE;
        }
    }
    MSE = MSE/(512*512);
    PSNR = 20*log10(255.0) - 10*log10(MSE);

    return PSNR;
}