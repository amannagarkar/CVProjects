#include "LaplacianOperator.h"
#include <opencv2/opencv.hpp>
#include <vector>

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
    // Define the Laplacian kernel
    std::vector<std::vector<int>> laplacian_kernel = {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0}
    };

    // Convolve the image with the Laplacian kernel
    cv::Mat laplacian_img = convolve(img, laplacian_kernel);

    // Initialize output matrices
    cv::Mat zero_crossings = cv::Mat::zeros(img.size(), CV_8U);  // Zero-crossings image
    cv::Mat result = laplacian_img.clone();  // To store the final result (peaks marked)

    int rows = laplacian_img.rows;
    int cols = laplacian_img.cols;

    // Zero-crossing detection and peak marking
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            // Current pixel value
            double current_pixel = laplacian_img.at<double>(i, j);

            // Get neighboring pixels
            double neighbors[8] = {
                laplacian_img.at<double>(i-1, j-1), laplacian_img.at<double>(i-1, j), laplacian_img.at<double>(i-1, j+1),
                laplacian_img.at<double>(i, j-1), laplacian_img.at<double>(i, j+1),
                laplacian_img.at<double>(i+1, j-1), laplacian_img.at<double>(i+1, j), laplacian_img.at<double>(i+1, j+1)
            };

            bool is_zero_crossing = false;
            for (int k = 0; k < 8; ++k) {
                if ((current_pixel > 0 && neighbors[k] < 0) || (current_pixel < 0 && neighbors[k] > 0)) {
                    is_zero_crossing = true;
                    break;
                }
            }

            if (is_zero_crossing) {
                zero_crossings.at<uchar>(i, j) = 255;  // Mark zero-crossing as white
            }
            else if (current_pixel > 0) {
                result.at<double>(i, j) = 128;  // Mark positive peak as 128
            }
            else if (current_pixel < 0) {
                result.at<double>(i, j) = 128;  // Mark negative peak as 128
            }
        }
    }

    // Return the result (zero-crossings image or peak-marked image)
    return result;
}