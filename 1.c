#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>

//DWORD dwordlen(LPSTR str) {
//    DWORD count = 1;
//    for (LPSTR ch = str; *ch != '\0'; ch++)
//    {
//        count++;
//    }
//    return count;
//}
//
//BOOL cout(LPSTR outStr) {
//    //printf("%s", outStr);
//    DWORD bWrittenInConsole = 0;
//    HANDLE hConsole_out = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (hConsole_out == INVALID_HANDLE_VALUE) {
//        return 1;
//    }
//    if (!WriteConsole(hConsole_out, outStr, dwordlen(outStr),
//                      &bWrittenInConsole, NULL)) {
//        return 1;
//    }
//    return 0;
//}

int main(int argc, char *argv[]) {
    HANDLE hFile;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwFileSize, dwBytesRead;
    DWORD dwBytesWritten = 50;
    LPVOID lpFileBuffer;


    if (argc != 2) {
        LPSTR message = "Usage: program.exe filename";
        DWORD dwBytesWritten = 0;
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      message,
                      strlen(message),
                      &dwBytesWritten,
                      NULL);

        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "\n",
                      1,
                      &dwBytesWritten,
                      NULL);
//        WriteConsole("Usage: program.exe filename\n");
        return 1;
    }


    hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "Could not open file",
                      strlen("Could not open file"),
                      &dwBytesWritten,
                      NULL);

//        WriteConsole(hConsole, "Could not open file", 5, dwBytesWritten, NULL);
//        cout("Could not open file\n");
        return 1;
    }

    dwFileSize = GetFileSize(hFile, NULL);
    lpFileBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
    if (lpFileBuffer == NULL) {
        CloseHandle(hFile);
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "Error allocating memory",
                      strlen("Error allocating memory"),
                      &dwBytesWritten,
                      NULL);
//        WriteConsole(hConsole, "Error allocating memory", 5, dwBytesWritten, NULL);
//        cout("Error allocating memory\n");
        return 1;
    }

    if (!ReadFile(hFile, lpFileBuffer, dwFileSize, &dwBytesRead, NULL) || dwBytesRead != dwFileSize) {
        CloseHandle(hFile);
        HeapFree(GetProcessHeap(), 0, lpFileBuffer);
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                      "Error reading file",
                      strlen("Error reading file"),
                      &dwBytesWritten,
                      NULL);
//        WriteConsole(hConsole, 'Error reading file', 5, dwBytesWritten, NULL);
//        cout("Error reading file\n");
        return 1;
    }

    CloseHandle(hFile);


//    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
//                  "File size: %ld bytes : ",
//                  strlen("File size: %ld bytes"),
//                  &dwBytesWritten,
//                  NULL);
////    WriteConsole(hConsole, 'File size: %ld bytes', 5, dwBytesWritten, NULL);
////    sprintf(fileSizeStr, "File size: %ld bytes\n", dwFileSize);
    HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        cout("Error opening file: %s\n");
        return 1;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        printf("Error getting file size: %s\n");
        CloseHandle(hFile);
        return 1;
    }

    char str[100];
    sprintf(str, "%lld", fileSize.QuadPart);
    DWORD written;
//    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), str, strlen(str), &written, NULL);
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),
                  str,
                  strlen(str),
                  &written,
                  NULL);
//    WriteConsole(hConsole, fileSizeStr, 5, dwBytesWritten, NULL);
//    cout(fileSizeStr);

    HeapFree(GetProcessHeap(), 0, lpFileBuffer);

    return 0;
}
