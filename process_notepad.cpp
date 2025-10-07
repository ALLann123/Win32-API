#include <windows.h>
#include <iostream>

int main()
{
    //structures required to start a new process
    STARTUPINFO si;   //holds information about how the new process should appear
    PROCESS_INFORMATION pi;   //Receives information about the newly created process

    //clear the memory of both structures to avoid garbage data
    ZeroMemory(&si, sizeof(si));  //Fill STARTUPINFO with zeros
    si.cb = sizeof(si);    // Set the size of the structure(required by windows)
    ZeroMemory(&pi, sizeof(pi));   //Fill PROCESS_INFORMATION with zeros

    //create a new process- Here we launch notepad
    CreateProcessA(
        NULL,  //Application name(NULL means use cmd name)
        "C:/windows/system32/notepad.exe",  //Command line path(Notepad)
        NULL,   //process security attributes
        NULL,    //Thread security attributes
        false,     //Inherit handles(FALSE =don't)
        0,  //creation flags
        NULL,   //Use parent's environment variables
        NULL,    //Use parents current directory
        &si,    //Pointer to STARTUPINFO structure
        &pi     //pointer to PROCESS_INFORMATION structure
    );

    //At this point notepad is running as a separate process
    //Our program will continue and end, while Notepad keeps running

    return 0;
}