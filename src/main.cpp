#include <opencv2/opencv.hpp>
#include <iostream>
#include "ColorDetector.h" 

int main() {
    cv::Mat image = cv::imread("rubiks_cube.jpg");
    if (image.empty()) {
        std::cerr << "❌ Erreur : Impossible de charger l'image !" << std::endl;
        return -1;
    }

    int width = image.cols;
    int height = image.rows;
    
    // Définir une région carrée au centre de l'image (par ex. 400x400)
    int roiSize = 1000;
    cv::Rect centerROI((width - roiSize) / 2, (height - roiSize) / 2, 1000, 900);
    cv::Mat cropped = image(centerROI).clone();  // clone() pour ne pas modifier l'image originale
    
    cv::rectangle(image, centerROI, cv::Scalar(0, 255, 0), 2);
    cv::imshow("Image avec ROI", image);
    cv::waitKey(0);
    
    ColorDetector detector;
    detector.detectColors(cropped);

    return 0;
}