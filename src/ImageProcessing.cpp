#include "ImageProcessing.h"

cv::Mat convertToGrayscale(const cv::Mat& img) {
    cv::Mat gray(img.rows, img.cols, CV_8UC1);
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            gray.at<uchar>(i, j) = static_cast<uchar>(
                0.2126 * pixel[2] + 0.7152 * pixel[1] + 0.0722 * pixel[0]);
        }
    }
    return gray;
}


