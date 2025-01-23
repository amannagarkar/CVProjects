#include "app.h"
#include "ImageProcessing.h"
#include "SobelOperator.h"
#include "LaplacianOperator.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    std::string input_dir = "res/images";
    std::string output_dir = "res/processed_images";
    fs::create_directory(output_dir);

    for (const auto& entry : fs::directory_iterator(input_dir)) {
        if (entry.is_regular_file()) {
            cv::Mat img = cv::imread(entry.path().string());
            if (img.empty()) {
                std::cerr << "Failed to load " << entry.path() << std::endl;
                continue;
            }

            // Grayscale Conversion
            cv::Mat gray = convertToGrayscale(img);

            // Sobel Operator
            cv::Mat grad_x, grad_y, magnitude_L1, magnitude_L2, gradient_angle;
            applySobel(gray, grad_x, grad_y, magnitude_L1, magnitude_L2, gradient_angle);

            // Laplacian Operator
            cv::Mat laplacian = applyLaplacian(gray);

            // Add Gaussian Noise
            cv::Mat noisy_img_5 = addGaussianNoise(gray, 5);
            cv::Mat noisy_img_10 = addGaussianNoise(gray, 10);

            // Apply Laplacian on Noisy Images
            cv::Mat laplacian_noisy_5 = applyLaplacian(noisy_img_5);
            cv::Mat laplacian_noisy_10 = applyLaplacian(noisy_img_10);

            // Apply LoG Operator
            cv::Mat log_1_0_7x7 = applyLoG(gray, 1.0, 7);
            cv::Mat log_1_5_11x11 = applyLoG(gray, 1.5, 11);

            // Save Outputs
            std::string base_name = entry.path().stem().string();
            cv::imwrite(output_dir + "/" + base_name + "_gray.png", gray);
            cv::imwrite(output_dir + "/" + base_name + "_magnitude_L1.png", magnitude_L1);
            cv::imwrite(output_dir + "/" + base_name + "_magnitude_L2.png", magnitude_L2);
            cv::imwrite(output_dir + "/" + base_name + "_gradient_angle.png", gradient_angle);
            cv::imwrite(output_dir + "/" + base_name + "_laplacian.png", laplacian);
            cv::imwrite(output_dir + "/" + base_name + "_noisy_5.png", noisy_img_5);
            cv::imwrite(output_dir + "/" + base_name + "_noisy_10.png", noisy_img_10);
            cv::imwrite(output_dir + "/" + base_name + "_laplacian_noisy_5.png", laplacian_noisy_5);
            cv::imwrite(output_dir + "/" + base_name + "_laplacian_noisy_10.png", laplacian_noisy_10);
            cv::imwrite(output_dir + "/" + base_name + "_log_1_0_7x7.png", log_1_0_7x7);
            cv::imwrite(output_dir + "/" + base_name + "_log_1_5_11x11.png", log_1_5_11x11);
        }
    }

    return 0;
}