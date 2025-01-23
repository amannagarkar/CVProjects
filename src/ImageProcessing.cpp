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

cv::Mat computeGradientAngle(const cv::Mat& grad_x, const cv::Mat& grad_y) {
    cv::Mat angle(grad_x.size(), CV_8U);

    for (int i = 0; i < grad_x.rows; ++i) {
        for (int j = 0; j < grad_x.cols; ++j) {
            double gx = grad_x.at<double>(i, j);
            double gy = grad_y.at<double>(i, j);

            // Compute angle in radians
            double theta = atan2(gy, gx);

            // Scale angle to [0, 255]
            angle.at<uchar>(i, j) = static_cast<uchar>((theta + CV_PI) * (255.0 / (2 * CV_PI)));
        }
    }

    return angle;
}

cv::Mat addGaussianNoise(const cv::Mat& img, double sigma) {
    cv::Mat noisy_img = img.clone();
    cv::Mat noise = cv::Mat(img.size(), img.type());
    cv::randn(noise, 0, sigma);  // Generate Gaussian noise
    noisy_img += noise;  // Add noise to the original image

    // Clip pixel values to [0, 255]
    cv::normalize(noisy_img, noisy_img, 0, 255, cv::NORM_MINMAX, CV_8U);

    return noisy_img;
}

cv::Mat applyLoG(const cv::Mat& img, double sigma, int kernel_size) {
    // Generate Gaussian Kernel
    cv::Mat kernel = cv::getGaussianKernel(kernel_size, sigma, CV_64F);
    kernel = kernel * kernel.t();  // Create 2D Gaussian kernel

    // Generate Laplacian of Gaussian (LoG) kernel
    cv::Mat log_kernel = kernel - (1.0 / (M_PI * sigma * sigma)) * (1 - kernel);

    // Convolve the image with the LoG kernel
    cv::Mat log_output;
    cv::filter2D(img, log_output, CV_64F, log_kernel);

    // Find zero-crossings and label them
    cv::Mat zero_crossings = cv::Mat::zeros(img.size(), CV_8U);
    for (int i = 1; i < log_output.rows - 1; ++i) {
        for (int j = 1; j < log_output.cols - 1; ++j) {
            double current_pixel = log_output.at<double>(i, j);
            double neighbors[8] = {
                log_output.at<double>(i-1, j-1), log_output.at<double>(i-1, j), log_output.at<double>(i-1, j+1),
                log_output.at<double>(i, j-1), log_output.at<double>(i, j+1),
                log_output.at<double>(i+1, j-1), log_output.at<double>(i+1, j), log_output.at<double>(i+1, j+1)
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
        }
    }

    return zero_crossings;
}