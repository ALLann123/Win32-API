#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

void ListProcesses()
{
    // Declare a handle that will store the snapshot of all processes
    HANDLE hProcessSnap;

    // Declare a structure that wil hold information about each process
    PROCESSENTRY32 pe32;

    /*
    1) Take a Snapshot of all processes currently runing in the system
    2)TH32CS_SNAPPROCESS specifies that we want to include process information
    3)The second Arg (0) means we are taking a snapshot of all processes
    */
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // check if the snapshot handle is valid
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cerr << "CreateToolhelp32Snapshot failed!!" << "\n";
        return; // Exit the function if snapshot creation failed
    }

    // set the size of the PROCESSENTRY32 structure before using it
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process in the snapshot
    if (!Process32First(hProcessSnap, &pe32))
    {
        // If the call fails, close the snapshot handle and report error
        CloseHandle(hProcessSnap);
        std::cerr << "Process32First Failed!" << std::endl;
    }

    // loop throufh all process in the snapshot
    do
    {
        /*
        Print the name and the iD of the current process
        szExeFile contains the name of the executable file for the process
        th32ProcessID contains the process identifier
        */
        std::wcout << L"Process name: "<<pe32.szExeFile << L"\nProcess ID: " << pe32.th32ProcessID << std::endl;

    } while (Process32Next(hProcessSnap, &pe32));

    // close the snapshot handle to free system resources
    CloseHandle(hProcessSnap);
}



int main()
{
    // display all running processes
    ListProcesses();
    return 0;
}


/*
Process name: [System Process]
Process ID: 0
Process name: System
Process ID: 4
Process name: Secure System   
Process ID: 56
Process name: Registry        
Process ID: 104
Process name: smss.exe        
Process ID: 480
Process name: csrss.exe
Process ID: 572
Process name: wininit.exe
Process ID: 680
Process name: csrss.exe
Process ID: 700
Process name: winlogon.exe
Process ID: 796
Process name: services.exe
Process ID: 832
Process name: LsaIso.exe
Process ID: 864
Process name: lsass.exe
Process ID: 872
Process name: svchost.exe
Process ID: 1004
Process name: fontdrvhost.exe
Process ID: 352
Process name: fontdrvhost.exe
Process ID: 460
Process name: WUDFHost.exe
Process ID: 640
Process name: svchost.exe
Process ID: 896
Process name: svchost.exe
Process ID: 1040
Process name: svchost.exe
Process ID: 1120
Process name: svchost.exe
Process ID: 1148
Process name: svchost.exe
Process ID: 1228
Process name: svchost.exe
Process ID: 1276
Process name: svchost.exe
Process ID: 1336
Process name: svchost.exe
Process ID: 1532
Process name: svchost.exe
Process ID: 1580
Process name: svchost.exe
Process ID: 1644
Process name: dwm.exe
Process ID: 1652
Process name: svchost.exe
Process ID: 1664
Process name: svchost.exe
Process ID: 1696
Process name: svchost.exe
Process ID: 1704
Process name: svchost.exe
Process ID: 1724
Process name: Memory Compression
Process ID: 1852
Process name: svchost.exe
Process ID: 1876
Process name: svchost.exe
Process ID: 1888
Process name: svchost.exe
Process ID: 1928
Process name: svchost.exe
Process ID: 1960
Process name: svchost.exe
Process ID: 1624
Process name: svchost.exe
Process ID: 2060
Process name: igfxCUIService.exe
Process ID: 2068
Process name: svchost.exe
Process ID: 2084
Process name: svchost.exe
Process ID: 2156
Process name: svchost.exe
Process ID: 2176
Process name: svchost.exe
Process ID: 2216
Process name: svchost.exe
Process ID: 2324
Process name: svchost.exe
Process ID: 2368
Process name: svchost.exe
Process ID: 2428
Process name: svchost.exe
Process ID: 2556
Process name: svchost.exe
Process ID: 2568
Process name: helperservice.exe
Process ID: 2588
Process name: svchost.exe
Process ID: 2636
Process name: conhost.exe
Process ID: 2944
Process name: svchost.exe
Process ID: 2976
Process name: svchost.exe
Process ID: 2260
Process name: svchost.exe
Process ID: 2288
Process name: svchost.exe
Process ID: 2768
Process name: svchost.exe
Process ID: 2968
Process name: svchost.exe
Process ID: 3148
Process name: svchost.exe
Process ID: 3216
Process name: svchost.exe
Process ID: 3264
Process name: svchost.exe
Process ID: 3352
Process name: svchost.exe
Process ID: 3412
Process name: svchost.exe
Process ID: 3456
Process name: svchost.exe
Process ID: 3492
Process name: svchost.exe
Process ID: 3496
Process name: spoolsv.exe
Process ID: 3680
Process name: svchost.exe
Process ID: 3736
Process name: svchost.exe
Process ID: 3744
Process name: IQOptionUpdater.exe
Process ID: 3788
Process name: sqlwriter.exe
Process ID: 3816
Process name: MpDefenderCoreService.exe
Process ID: 3828
Process name: SynTPEnhService.exe
Process ID: 3844
Process name: MsMpEng.exe
Process ID: 3872
Process name: wslservice.exe
Process ID: 3888
Process name: vmcompute.exe
Process ID: 3996
Process name: svchost.exe
Process ID: 4060
Process name: svchost.exe
Process ID: 4068
Process name: svchost.exe
Process ID: 4076
Process name: svchost.exe
Process ID: 4084
Process name: svchost.exe
Process ID: 3040
Process name: svchost.exe
Process ID: 3236
Process name: svchost.exe
Process ID: 3200
Process name: svchost.exe
Process ID: 4228
Process name: svchost.exe
Process ID: 4376
Process name: svchost.exe
Process ID: 4544
Process name: dasHost.exe
Process ID: 4704
Process name: svchost.exe
Process ID: 4792
Process name: svchost.exe
Process ID: 5012
Process name: svchost.exe
Process ID: 4408
Process name: SearchIndexer.exe
Process ID: 5328
*/