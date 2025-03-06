#include <stdio.h>
#include <stdlib.h>

void extract_with_tar(const char* filename) {
    char command[512];
    snprintf(command, sizeof(command), "tar -xf \"%s\"", filename);
    printf("Executando: %s\n", command);
    system(command);
}

int main() {
    extract_with_tar("C:\\Users\\Gustavo\\Documents\\Artigos.tar");
    return 0;
}