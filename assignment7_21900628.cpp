#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat img,DB_img;
    string filename = "DBs/*.jpg";
    string image;
    string file;
    vector<String> DB_str;

    Mat descriptors1, descriptors2;
    Ptr<ORB> orbF = ORB::create(1000);
    vector<KeyPoint> keypoints1, keypoints2;
    vector< vector< DMatch> > matches;
    vector< DMatch > goodMatches;
    BFMatcher matcher(NORM_HAMMING);
    Mat imgMatches;

    int size=0;
    int prev_size=-1;
    int i, k; 
    float nndr;
    string mat_file;
    glob(filename,DB_str,false);

    cout << "Enter Quary image name: ";
    cin >> image;
    img = imread("query_image/"+image);
    if(img.empty()){
        cout << "No file!";
        return 0;
    }
    if(DB_str.size()==0){
        cout << "no Database" << endl;
        return 0;
    }
    cout << "Sample image Load Size: " << DB_str.size() << endl;
    resize(img,img,Size(640,480));
    orbF->detectAndCompute(img, noArray(), keypoints1, descriptors1); 
    for(int count=0;count<DB_str.size();count++){
        file = DB_str[count];
        DB_img = imread(file);
        if(DB_img.empty()){
            cout<<"no file in DB";
            return 0;
        }
        resize(DB_img,DB_img,Size(640,480));
        orbF->detectAndCompute(DB_img, noArray(), keypoints2, descriptors2);
        k = 2;
        matcher.knnMatch(descriptors1, descriptors2, matches, k);
        nndr = 0.6f;
        for (i = 0; i < matches.size(); i++) {
            if (matches.at(i).size() == 2 && matches.at(i).at(0).distance <= nndr * matches.at(i).at(1).distance) {
                goodMatches.push_back(matches[i][0]);
            }
        }
        cout << "Image number " << count+1 << " Matching: " << goodMatches.size() << endl;
        size = goodMatches.size();
        if(size>prev_size){
            prev_size=size;
            mat_file=file;
        }
        matches.clear();
        goodMatches.clear();
        matcher.clear();
    }
    if(prev_size>0)
        cout<< "Match found!" << endl;
    
    DB_img = imread(mat_file);
    resize(DB_img,DB_img,Size(640,480));
    orbF->detectAndCompute(DB_img, noArray(), keypoints2, descriptors2);
    k = 2;
    matcher.knnMatch(descriptors1, descriptors2, matches, k);
    nndr = 0.6f;
    for (i = 0; i < matches.size(); i++) {
        if (matches.at(i).size() == 2 && matches.at(i).at(0).distance <= nndr * matches.at(i).at(1).distance) {
            goodMatches.push_back(matches[i][0]);
        }
    }
    imshow("Query",img);
    drawMatches(img, keypoints1, DB_img, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Best_matching", imgMatches);
    waitKey(0);
    return 0;
}
