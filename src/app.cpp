#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "ImageProcessing.h"

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

int main() {
    string input_dir = "/Users/amannagarkar/Documents/SCU Phd Coursework/CV - CSEN 344/Assignment 1 - Image Operations/res/Images";
    string output_dir = "/Users/amannagarkar/Documents/SCU Phd Coursework/CV - CSEN 344/Assignment 1 - Image Operations/res/BWImages";

    fs::create_directories(output_dir);

    for (const auto& entry: fs::directory_iterator(input_dir) ){
        
        if (entry.is_regular_file()){
            string image_path = entry.path().string();
            Mat img = imread(image_path, IMREAD_COLOR);
            if(img.empty()){
                cout<<"Image is empty"<<endl;
                continue;
            }

            Mat gray_img = convertToGreyScale(img);

            string output_img_path = output_dir + "/" + entry.path().filename().string(); 
            imwrite(output_img_path, gray_img);

        }
        cout<<"Images Saved in: "<<output_dir<<endl;
    }

    return 0;
}