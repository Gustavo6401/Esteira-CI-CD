#include <stdio.h>
#include <stdlib.h>

void extract_with_7z(const char* filename) {
    char command[512];
    snprintf(command, sizeof(command), "7z x \"%s\" -oExtraido", filename);
    printf("Executando: %s\n", command);
    system(command);
}

int main() {
    extract_with_7z("C:\\Users\\Gustavo\\Documents\\Artigos.7z");
    return 0;
}