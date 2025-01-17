#ifndef SOBEL_OPERATOR_H
#define SOBEL_OPERATOR_H

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat applySobel(const cv::Mat& img, cv::Mat& grad_x, cv::Mat& grad_y, cv::Mat& magnitude_L1, cv::Mat& magnitude_L2, cv::Mat& gradient_angle);

#endif // SOBEL_OPERATOR_H
