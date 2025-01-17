#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include<filesystem>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

Mat convertToGreyScale(const Mat& img);
Mat convolve(const Mat& img, const vector<vector<int>>& kernel);

#endif