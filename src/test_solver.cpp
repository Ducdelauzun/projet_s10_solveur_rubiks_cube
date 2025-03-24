#include <iostream>
#include "CubeParser.hpp"
#include "Solver.hpp"

int main() {
    // Cube en entrée : chaîne par face (lettres = couleurs)
    std::string faces[6] = {
        "U:DRLUUBFBR",  // face Up
        "R:BLURRLRUB",  // face Right
        "F:LRDDFDLFU",  // face Front
        "D:FUFFDBRDU",  // face Down
        "L:BRUFLLFDD",  // face Left
        "B:BFLUBLRBD"   // face Back
    };

    FaceletCube faceletCube;
    CubeParser parser;
    RubiksCube cube;
    Solver solver;

    int result = parser.parseFacelets(faces, faceletCube);
    if (result != CubeParser::VALID) {
        std::cout << "❌ Erreur de parsing : " << parser.ErrorText(result) << std::endl;
        return 1;
    }

    result = faceletCube.Validate(cube);
    if (result != FaceletCube::VALID) {
        std::cout << "❌ Cube invalide : " << faceletCube.ErrorText(result) << std::endl;
        return 1;
    }

    solver.InitializeTables();
    result = solver.Solve(cube);

    if (result == Solver::FOUND || result == Solver::OPTIMUM_FOUND) {
        std::cout << "✅ Solution trouvée :\n";
        solver.PrintSolution();
    } else {
        std::cout << "❌ Échec de résolution.\n";
    }

    return 0;
}