#include <stdio.h>
#include <stdlib.h>

void extract_zip(const char* filename) {
    char command[512];
    snprintf(command, sizeof(command), "tar -xf \"%s\"", filename);
    printf("Executando: %s\n", command);
    system(command);
}

int main() {
    extract_zip("C:\\Users\\Gustavo\\Documents\\Artigos.tar");
    return 0;
}