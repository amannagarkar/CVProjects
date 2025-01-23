#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <opencv2/opencv.hpp>

cv::Mat convertToGrayscale(const cv::Mat& img);
cv::Mat addGaussianNoise(const cv::Mat& img, double sigma);
cv::Mat applyLoG(const cv::Mat& img, double sigma, int kernel_size);

#endif