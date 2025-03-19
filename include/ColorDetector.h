#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>
#include <vector>

class ColorDetector {
public:
    ColorDetector();  // Constructeur
    void detectColors(cv::Mat& img);  // Fonction de détection des couleurs

private:
    std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> color_ranges;
};

#endif