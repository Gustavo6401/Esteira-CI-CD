#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define ZIP_SIGNATURE 0x04034b50

#pragma pack(push, 1) // Evita alinhamento de bytes
typedef struct {
    unsigned int signature;
    unsigned short version;
    unsigned short flags;
    unsigned short compression;
    unsigned short mod_time;
    unsigned short mod_date;
    unsigned int crc32;
    unsigned int compressed_size;
    unsigned int uncompressed_size;
    unsigned short filename_length;
    unsigned short extra_length;
} ZipHeader;
#pragma pack(pop)

void extract_zip(const char* filename) {
    FILE *zipFile = fopen(filename, "rb");
    if (!zipFile) {
        printf("Erro ao abrir o arquivo ZIP!\n");
        return;
    }

    ZipHeader header;
    while (fread(&header, sizeof(ZipHeader), 1, zipFile)) {
        if (header.signature != ZIP_SIGNATURE) break;

        char filename[256];
        fread(filename, 1, header.filename_length, zipFile);
        filename[header.filename_length] = '\0';

        printf("📂 Extraindo: %s (Tamanho: %d bytes)\n", filename, header.uncompressed_size);

        unsigned char *compressed_data = (unsigned char*)malloc(header.compressed_size);
        fread(compressed_data, 1, header.compressed_size, zipFile);

        unsigned char *uncompressed_data = (unsigned char*)malloc(header.uncompressed_size);

        z_stream 

        fseek(zipFile, header.compressed_size + header.extra_length, SEEK_CUR);
    }

    fclose(zipFile);
}

int main() {
    extract_zip("C:\\Users\\Gustavo\\Documents\\Xadrez.zip");
    return 0;
}