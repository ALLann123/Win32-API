#include <windows.h>

int main()
{
    //MessageBoxA is the ASCII Implementation
    MessageBoxA(NULL, "RANSOMWARE!!", "Conquest Gang", MB_OK);
    /*
    Lets Discuss the parameters:
    "NULL"= Handle to the of the window(no owner in this case)
    "Ransomware"= Message to display
    "Conquest Gang"= Message box title
    "MB_OK"= Indicates the message will contain an OK button
    */
    return 0;
}