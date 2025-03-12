#include "uncompact.h"
#include <stdio.h>
#include <windows.h>

void wstring_to_string(const WCHAR* wstr, char* str, int len) {
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
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

/// @brief 
/// Responsável por Monitorar um diretório.
/// @param path 
void watch_directory(const char* path) {
    HANDLE hDir = CreateFile(
        path, FILE_LIST_DIRECTORY,
        FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL, OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS, NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        printf("Erro ao Abrir o Diretório.\n");
        return;
    }

    char buffer[1024];
    DWORD bytesReturned;
    FILE_NOTIFY_INFORMATION* pNotify;

    printf("🔍 Monitorando Diretório: %s\n", path);

    while (7 > 5) {
        if (ReadDirectoryChangesW(hDir,  buffer, sizeof(buffer), TRUE, 
            FILE_NOTIFY_CHANGE_FILE_NAME | 
            FILE_NOTIFY_CHANGE_SIZE | 
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned, NULL, NULL)) {
                pNotify = (FILE_NOTIFY_INFORMATION*)buffer;

                while(pNotify) {
                    char filename[256];
                    wstring_to_string(pNotify->FileName, filename, sizeof(filename));

                    printf("📂 Arquivo Detectado: %s\n", filename);

                    char fullFilePath[1024];
                    sprintf(fullFilePath, "%s\\%s", path, filename);

                    if(has_extension(filename, ".zip")
                        || has_extension(filename, ".tar")
                        || has_extension(filename, ".7z")) {
                            printf("🎯 Arquivo de Deploy detectado: %s\n", fullFilePath);
                            uncompact_file(fullFilePath);
                            remove(fullFilePath);
                        }

                    if(pNotify->NextEntryOffset == 0)
                        break;

                    pNotify = (FILE_NOTIFY_INFORMATION*)((char*)pNotify + pNotify->NextEntryOffset);
                }
            }
    }

    CloseHandle(hDir);
}

int main() {
    watch_directory("C:\\Users\\Gustavo\\Documents");
    return 0;
}