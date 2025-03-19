#include "ColorDetector.h"

// 📌 Constructeur : Initialise les plages de couleurs HSV
ColorDetector::ColorDetector() {
    color_ranges = {
        {"Rouge",  {cv::Scalar(167, 100, 100), cv::Scalar(180, 255, 255)}},  
        {"Bleu",   {cv::Scalar(97, 100, 100), cv::Scalar(103, 255, 255)}},  
        {"Jaune",  {cv::Scalar(24, 100, 100), cv::Scalar(37, 255, 255)}},  
        {"Vert",   {cv::Scalar(42, 100, 100), cv::Scalar(75, 255, 255)}},  
        {"Orange", {cv::Scalar(10, 100, 100), cv::Scalar(16, 250, 250)}},  
        {"Blanc",  {cv::Scalar(0, 0, 200), cv::Scalar(180, 50, 255)}}  
    };
}

// 📌 Détection des couleurs dans l'image
void ColorDetector::detectColors(cv::Mat& img) {
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat mask;
    for (const auto& color_range : color_ranges) {
        std::string color_name = color_range.first;
        cv::inRange(hsv, color_range.second.first, color_range.second.second, mask);
        cv::Mat kernal = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
        cv::dilate(mask, mask, kernal);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            if (area > 500) {  // Éviter les petites zones parasites
                cv::Rect rect = cv::boundingRect(contour);
                cv::rectangle(img, rect, cv::Scalar(255, 255, 255), 2);
                cv::putText(img, color_name, cv::Point(rect.x, rect.y - 5),
                            cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
            }
        }
    }

    // 📌 Affichage de l'image annotée
    cv::imshow("Détection de couleurs", img);
    cv::waitKey(0);
}