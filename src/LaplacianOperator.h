#ifndef LAPLACIANOPERATOR_H
#define LAPLACIANOPERATOR_H

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat convolve(const cv::Mat& img, const std::vector<std::vector<int>>& kernel);
cv::Mat applyLaplacian(const cv::Mat& img);

#endif