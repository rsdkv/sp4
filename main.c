#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

DWORD dwordlen(LPSTR str) {
    DWORD count = 1;
    for (LPSTR ch = str; *ch != '\0'; ch++)
    {
        count++;
    }
    return count;
}

BOOL cout(LPSTR outStr) {
//printf("%s", outStr);
    DWORD bWrittenInConsole = 0;
    HANDLE hConsole_out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole_out == INVALID_HANDLE_VALUE) {
        return 1;
    }
    if (!WriteConsole(hConsole_out, outStr, dwordlen(outStr),
                      &bWrittenInConsole, NULL)) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout("Error: Invalid number of arguments\n");
        cout("Usage: ./program <existing filename> <unsigned long>\n");
        return 1;
    }

    HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        cout("Error opening file: %s\n");
        return 1;
    }

    LARGE_INTEGER fileSize;

    if (!GetFileSizeEx(hFile, &fileSize)) {
        cout("Error getting file size: %s\n");
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);

    char str[100];
    sprintf(str, "%lld", fileSize.QuadPart);
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(hConsole,
                 str,
                 strlen(str),
                 &written,
                 NULL);

    return 0;
}
