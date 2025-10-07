#include <iostream>
#include <windows.h>

int main()
{
    //create a registery key
    HKEY hkey;
    DWORD Disposition;
    long status=RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\MyKey", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &Disposition)


    if(status==ERROR_SUCCESS){
        //do something here
        long RegS
    }


    return 0;
}