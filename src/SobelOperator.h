#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H

#include <opencv2/opencv.hpp>

cv::Mat applySobel(const cv::Mat& img, cv::Mat& grad_x, cv::Mat& grad_y, cv::Mat& magnitude_L1, cv::Mat& magnitude_L2, cv::Mat& gradient_angle);

#endif