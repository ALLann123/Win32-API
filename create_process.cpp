#include <iostream>
#include <windows.h>

int main()
{
    //Create Process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    //fill the memories with zero
    ZeroMemory(&si, sizeof(si));
    si.cb=sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcessA(NULL,"C:/windows/system32/calc.exe", NULL, NULL,FALSE, 0, NULL, NULL, &si, &pi);


    return 0;
}