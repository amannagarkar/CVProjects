#include "SobelOperator.h"

cv::Mat applySobel(const cv::Mat& img, cv::Mat& grad_x, cv::Mat& grad_y, cv::Mat& magnitude_L1, cv::Mat& magnitude_L2, cv::Mat& gradient_angle) {
    std::vector<std::vector<int>> sobel_x = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    std::vector<std::vector<int>> sobel_y = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int rows = img.rows, cols = img.cols;
    grad_x = cv::Mat(rows, cols, CV_64F, cv::Scalar(0));
    grad_y = cv::Mat(rows, cols, CV_64F, cv::Scalar(0));
    magnitude_L1 = cv::Mat(rows, cols, CV_8U);
    magnitude_L2 = cv::Mat(rows, cols, CV_8U);
    gradient_angle = cv::Mat(rows, cols, CV_8U);

    int k = 1; // Kernel size radius
    for (int i = k; i < rows - k; ++i) {
        for (int j = k; j < cols - k; ++j) {
            double gx = 0, gy = 0;
            for (int u = -k; u <= k; ++u) {
                for (int v = -k; v <= k; ++v) {
                    gx += img.at<uchar>(i + u, j + v) * sobel_x[u + k][v + k];
                    gy += img.at<uchar>(i + u, j + v) * sobel_y[u + k][v + k];
                }
            }
            grad_x.at<double>(i, j) = gx;
            grad_y.at<double>(i, j) = gy;

            double mag_L1 = abs(gx) + abs(gy);
            double mag_L2 = sqrt(gx * gx + gy * gy);
            double angle = atan2(gy, gx) * (255.0 / (2 * CV_PI));

            magnitude_L1.at<uchar>(i, j) = static_cast<uchar>(mag_L1);
            magnitude_L2.at<uchar>(i, j) = static_cast<uchar>(mag_L2);
            gradient_angle.at<uchar>(i, j) = static_cast<uchar>(angle);
        }
    }

    return magnitude_L2;
}
