#include "LaplacianOperator.h"

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

cv::Mat applyLaplacian(const cv::Mat& img) {
    std::vector<std::vector<int>> laplacian_kernel = {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0}
    };

    return convolve(img, laplacian_kernel);
}
