#include <opencv2/opencv.hpp>
#include <iostream>

// 📌 Fonction pour détecter la couleur en fonction du pixel HSV
std::string detectColor(cv::Vec3b hsv_pixel) {
    int h = hsv_pixel[0];  // Teinte
    int s = hsv_pixel[1];  // Saturation
    int v = hsv_pixel[2];  // Valeur

    if (h >= 0 && h <= 10) return "Rouge";
    if (h >= 20 && h <= 30) return "Jaune";
    if (h >= 35 && h <= 85) return "Vert";
    if (h >= 90 && h <= 140) return "Bleu";
    if (h >= 15 && h <= 25) return "Orange";
    return "Blanc";  // Par défaut
}

int main() {
    // Charger l'image
    cv::Mat image = cv::imread("rubiks_cube.jpg");
    if (image.empty()) {
        std::cerr << "❌ Erreur : Impossible de charger l'image !" << std::endl;
        return -1;
    }

    // Redimensionner pour standardiser
    cv::resize(image, image, cv::Size(500, 500));

    // Convertir en HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // 📌 Boucle pour détecter les couleurs sur une grille 3x3
    std::cout << "📌 Résultat de la détection des couleurs :\n";
    for (int row = 0, y = 100; row < 3; row++, y += 100) {
        for (int col = 0, x = 100; col < 3; col++, x += 100) {
            cv::Vec3b hsv_pixel = hsv.at<cv::Vec3b>(y, x);
            std::string color_name = detectColor(hsv_pixel);
            std::cout << "[" << row << "," << col << "] → " << color_name << " (H:" 
                      << (int)hsv_pixel[0] << ", S:" << (int)hsv_pixel[1] 
                      << ", V:" << (int)hsv_pixel[2] << ")\n";

            // Afficher la couleur détectée sur l'image
            cv::Scalar color;
            if (color_name == "Rouge") color = cv::Scalar(0, 0, 255);
            else if (color_name == "Jaune") color = cv::Scalar(0, 255, 255);
            else if (color_name == "Vert") color = cv::Scalar(0, 255, 0);
            else if (color_name == "Bleu") color = cv::Scalar(255, 0, 0);
            else if (color_name == "Orange") color = cv::Scalar(255, 165, 0);
            else color = cv::Scalar(255, 255, 255);  // Blanc

            cv::circle(image, cv::Point(x, y), 20, color, -1);
        }
    }

    // Afficher l'image avec couleurs détectées
    cv::imshow("Detected Colors", image);
    cv::waitKey(0);

    return 0;
}