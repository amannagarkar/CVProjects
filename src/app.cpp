#include "app.h"

int main() {
    string input_dir = "res/images";
    string output_dir = "res/processed_images";
    fs::create_directory(output_dir);

    for (const auto& entry : fs::directory_iterator(input_dir)) {
        if (entry.is_regular_file()) {
            Mat img = imread(entry.path().string());
            if (img.empty()) {
                cerr << "Failed to load " << entry.path() << endl;
                continue;
            }

            // Grayscale Conversion
            Mat gray = convertToGrayscale(img);

            // Sobel Operator
            Mat grad_x, grad_y, magnitude_L1, magnitude_L2, gradient_angle;
            applySobel(gray, grad_x, grad_y, magnitude_L1, magnitude_L2, gradient_angle);

            // Laplacian Operator
            Mat laplacian = applyLaplacian(gray);

            // Save Outputs
            string base_name = entry.path().stem().string();
            imwrite(output_dir + "/" + base_name + "_gray.png", gray);
            imwrite(output_dir + "/" + base_name + "_magnitude_L1.png", magnitude_L1);
            imwrite(output_dir + "/" + base_name + "_magnitude_L2.png", magnitude_L2);
            imwrite(output_dir + "/" + base_name + "_gradient_angle.png", gradient_angle);
            imwrite(output_dir + "/" + base_name + "_laplacian.png", laplacian);
        }
    }

    return 0;
}
