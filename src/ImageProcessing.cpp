#include "ImageProcessing.h"

Mat convertToGreyScale(const Mat& img){
    Mat gray_img(img.rows, img.cols, CV_8UC1);
            for(int i = 0; i < img.rows; ++i){
                for(int j = 0; j < img.cols; ++j){
                    Vec3b pixel = img.at<Vec3b>(i,j);
                    double G = (0.2126*pixel[2]) + (0.7152*pixel[1]) + (0.0722*pixel[0]);
                    gray_img.at<uchar>(i,j) = static_cast<uchar>(G);
                }
            }
    return gray_img;
}

cv::Mat convolve(const cv::Mat& img, const std::vector<std::vector<int>>& kernel) {
    int k = kernel.size() / 2;
    cv::Mat output(img.rows, img.cols, CV_64F, cv::Scalar(0));
    for (int i = k; i < img.rows - k; ++i) {
        for (int j = k; j < img.cols - k; ++j) {
            double sum = 0.0;
            for (int u = -k; u <= k; ++u) {
                for (int v = -k; v <= k; ++v) {
                    sum += img.at<uchar>(i + u, j + v) * kernel[u + k][v + k];
                }
            }
            output.at<double>(i, j) = sum;
        }
    }
    return output;
}