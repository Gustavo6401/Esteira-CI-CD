__declspec(dllimport) int __stdcall WriteFile(void* hFile, const void* lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, void* lpOverlapped);
__declspec(dllimport) void* __stdcall GetStdHandle(int nStdHandle);
__declspec(dllimport) void __stdcall ExitProcess(int uExitCode);

#define STD_OUTPUT_HANDLE (-11)

void _start() {
    char helloWorld[] = "Hello World\n";
    unsigned long bytesWritten;

    void* hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteFile(hStdOut, helloWorld, sizeof(helloWorld) - 1, &bytesWritten, 0);

    ExitProcess(0);
}

int main() {
    _start();
    return 0;
}