#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <sstream>
#include <cstdint>

using namespace std;

// Codage 4 bits des mouvements
unordered_map<string, uint8_t> move_codes = {
    {"U",  0b1001}, {"U'", 0b0001},
    {"F",  0b1010}, {"F'", 0b0010},
    {"R",  0b1011}, {"R'", 0b0011},
    {"L",  0b1100}, {"L'", 0b0100},
    {"B",  0b1101}, {"B'", 0b0101},
    {"D",  0b1110}, {"D'", 0b0110}
};

// Encodage d'un mouvement
vector<uint8_t> encode_move(const string& move) {
    vector<uint8_t> result;

    if (move.length() == 1 || (move.length() == 2 && move[1] == '\'')) {
        result.push_back(move_codes[move]);
    } else if (move.length() == 2 && move[1] == '2') {
        string base = move.substr(0, 1);
        result.push_back(move_codes[base]);
        result.push_back(move_codes[base]);  // équivaut à 180°
    } else {
        cerr << "❌ Mouvement non reconnu : " << move << endl;
    }

    return result;
}

int main() {
    // 🔧 Chemins des fichiers définis ici
    string input_file = "data\\input\\input.txt";
    string output_file = "data\\output\\output.txt";

    ifstream infile(input_file);
    ofstream outfile(output_file);

    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Erreur d'ouverture du fichier." << endl;
        return 1;
    }

    string line;
    getline(infile, line);  // Lire la seule ligne

    stringstream ss(line);
    string move;
    while (ss >> move) {
        vector<uint8_t> encoded = encode_move(move);
        for (uint8_t code : encoded) {
            outfile << bitset<4>(code) << endl;
        }
    }

    infile.close();
    outfile.close();

    cout << "✅ Encodage terminé : " << output_file << endl;
    return 0;
}