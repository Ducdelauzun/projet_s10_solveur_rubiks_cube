#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>

// 📌 Définition des plages de couleurs HSV
std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> color_ranges = {
    {"Rouge",  {cv::Scalar(0, 50, 40), cv::Scalar(10, 255, 255)}},  
    {"Rouge2", {cv::Scalar(155, 40, 30), cv::Scalar(180, 255, 255)}},  
    {"Orange", {cv::Scalar(5, 40, 50), cv::Scalar(25, 255, 255)}},  
    {"Jaune",  {cv::Scalar(20, 50, 50), cv::Scalar(40, 255, 255)}},  
    {"Vert",   {cv::Scalar(40, 60, 40), cv::Scalar(85, 255, 255)}},  
    {"Bleu",   {cv::Scalar(90, 50, 30), cv::Scalar(140, 255, 255)}},  
    {"Blanc",  {cv::Scalar(0, 0, 200), cv::Scalar(180, 30, 255)}}  
};

// 📌 Détection avec `cv2.inRange()`
std::string detectColorUsingMask(cv::Mat hsv, int x, int y) {
    cv::Vec3b pixel = hsv.at<cv::Vec3b>(y, x);
    int h = pixel[0];
    int s = pixel[1];
    int v = pixel[2];

    if (s < 20 && v < 200) return "Inconnu";

    for (const auto& color : color_ranges) {
        cv::Mat mask;
        cv::inRange(hsv, color.second.first, color.second.second, mask);
        if (mask.at<uchar>(y, x) > 0) {
            return color.first;
        }
    }

    // 📌 Correction pour Orange et Jaune mal détectés
    if (h >= 5 && h <= 40 && s > 20) {
        return (h < 25) ? "Orange" : "Jaune";
    }

    return "Inconnu";
}

int main() {
    cv::Mat image = cv::imread("rubiks_cube.jpg");
    if (image.empty()) {
        std::cerr << "❌ Erreur : Impossible de charger l'image !" << std::endl;
        return -1;
    }

    cv::resize(image, image, cv::Size(500, 500));

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    std::cout << "📌 Résultat de la détection des couleurs :\n";
    int width = image.cols;
    int height = image.rows;
    int cell_x = width / 3;
    int cell_y = height / 3;

    std::vector<std::pair<int, int>> debug_pixels = {
        {0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}
    };

    for (auto [row, col] : debug_pixels) {
        int x = col * cell_x + cell_x / 2;  
        int y = row * cell_y + cell_y / 2;  

        std::string color_name = detectColorUsingMask(hsv, x, y);

        std::cout << "[" << row << "," << col << "] → " << color_name << "\n";
        std::cout << "[DEBUG] Pixel [" << row << "," << col << "] HSV → H:" 
                  << hsv.at<cv::Vec3b>(y, x)[0]
                  << ", S:" << hsv.at<cv::Vec3b>(y, x)[1]
                  << ", V:" << hsv.at<cv::Vec3b>(y, x)[2] << "\n";

        cv::Scalar color = (color_name == "Rouge" || color_name == "Rouge2") ? cv::Scalar(0, 0, 255) :
                           (color_name == "Jaune") ? cv::Scalar(0, 255, 255) :
                           (color_name == "Vert") ? cv::Scalar(0, 255, 0) :
                           (color_name == "Bleu") ? cv::Scalar(255, 0, 0) :
                           (color_name == "Orange") ? cv::Scalar(255, 165, 0) : cv::Scalar(255, 255, 255);

        cv::circle(image, cv::Point(x, y), 20, color, -1);
    }

    cv::imshow("Detected Colors", image);
    cv::waitKey(0);

    return 0;
}