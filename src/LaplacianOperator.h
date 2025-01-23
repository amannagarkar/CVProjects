#ifndef LAPLACIAN_OPERATOR_H
#define LAPLACIAN_OPERATOR_H

#include <opencv2/opencv.hpp>

cv::Mat applyLaplacian(const cv::Mat& img);
cv::Mat convolve(const cv::Mat& img, const std::vector<std::vector<int>>& kernel);

#endif // LAPLACIAN_OPERATOR_H
