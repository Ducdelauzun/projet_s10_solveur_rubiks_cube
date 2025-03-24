#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int main() {
    const char* cube = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
    const char* cache_dir = "./cache";
    char* result = solution((char*)cube, 21, 5, 1, cache_dir);

    if (result != NULL) {
        printf("✅ Solution : %s\n", result);
        free(result);
    } else {
        printf("❌ Erreur : cube invalide ou résolution impossible.\n");
    }

    return 0;
}
