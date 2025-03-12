#include "uncompact.h"
#include <stdlib.h>
#include <string.h>

/// @brief unzip e untar fazem a mesma coisa...
/// @param filename 
/// @return 
int unzip(const char* filename) {
    char command[512];
    snprintf(command, sizeof(command), "tar -xf \"%s\"", filename);

    printf("Executando: %s\n", command);
    int response = system(command);

    return response;
}

int un7z(const char* filename) {
    char command[512];
    snprintf(command, sizeof(command), "7z x \"%s\" -o Extraído", filename);

    printf("Executando: %s\n", command);
    int response = system(command);

    return response;
}

int has_extension(const char* filename, const char* ext) {
    printf("Nome do Arquivo: %s\n", filename);
    size_t len_filename = strlen(filename);
    size_t len_ext = strlen(ext);

    if (len_filename >= len_ext) {
        return(strcmp(filename + (len_filename - len_ext), ext) == 0);
    }

    return 0;
}

void verify_extension(const char* filename) {
    if (has_extension(filename, ".zip") || has_extension(filename, ".tar")) {
        unzip(filename);
    }
    else if (has_extension(filename, ".7z"))
    {
        un7z(filename);
    }    
}

int uncompact_file(const char *path) {
    verify_extension(path);

    return 0;
}