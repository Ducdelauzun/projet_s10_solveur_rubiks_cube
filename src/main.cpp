#include <opencv2/opencv.hpp>
#include <iostream>
#include "ColorDetector.h" 

int main() {
    cv::Mat image = cv::imread("rubiks_cube.jpg");
    if (image.empty()) {
        std::cerr << "❌ Erreur : Impossible de charger l'image !" << std::endl;
        return -1;
    }

    ColorDetector detector;
    detector.detectColors(image);

    return 0;
}