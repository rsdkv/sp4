#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(int argc, char *argv[]) {

    DWORD dwBytesWritten = 50;
    if (argc != 2) {
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "Error: Invalid number of arguments",
                      strlen("Error: Invalid number of arguments"),
                      &dwBytesWritten,
                      NULL);
//        cout("Error: Invalid number of arguments\n");
//        cout("Usage: ./program <existing filename> <unsigned long>\n");
        return 1;
    }

    HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "Could not open file",
                      strlen("Could not open file"),
                      &dwBytesWritten,
                      NULL);
        return 1;
    }

    LARGE_INTEGER fileSize;

    if (!GetFileSizeEx(hFile, &fileSize)) {
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "\"Error getting file size",
                      strlen("\"Error getting file size"),
                      &dwBytesWritten,
                      NULL);
//        cout("Error getting file size: %s\n");
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);

    char str[100];
    sprintf(str, "%lld", fileSize.QuadPart);//форматирует и сохраняет набор символов и значений в buffer
    DWORD written;
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                  str,
                  strlen(str),
                  &written,
                  NULL);
//    WriteConsole(hConsole,
//                 str,
//                 strlen(str),
//                 &written,
//                 NULL);

    return 0;
}
