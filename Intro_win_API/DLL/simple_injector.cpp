#include <windows.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // Check if correct number of arguments are provided
    if(argc < 3){
        std::cout << "Usage: Injector.exe <PID> <DLL_PATH>" << std::endl;
        return 1;
    }

    // Parse command line arguments
    DWORD pid = atoi(argv[1]);          // Convert PID string to integer
    const char* dllPath = argv[2];      // Get the path to the DLL file

    /*
    Step 1: Open the target process with full access rights
    PROCESS_ALL_ACCESS - Request all possible access rights
    FALSE - Don't inherit handle
    pid - Process ID to open
    */
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    // Step 2: Allocate memory in the target process for our DLL path
    /*
    hProcess - Target process handle
    0 - Let system decide where to allocate
    strlen(dllPath) + 1 - Size needed (string length + null terminator)
    MEM_COMMIT - Commit the memory immediately
    PAGE_READWRITE - Memory protection: readable and writable
    */
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

    /*
    Step 3: Write the DLL path to the allocated memory in target process
    hProcess - Target process handle
    pDllPath - Destination address in target process
    dllPath - Source address in our process
    strlen(dllPath) + 1 - Number of bytes to be written
    0 - Optional pointer to receive number of bytes written
    */
    WriteProcessMemory(hProcess, pDllPath, dllPath, strlen(dllPath) + 1, 0);

    /*
    Step 4: Create a remote thread in target process to load our DLL
    hProcess - Target process handle
    0 - Default security attributes
    0 - Default stack size
    GetProcAddress(...) - Address of LoadLibraryA function in kernel32.dll
    pDllPath - Parameter to pass to LoadLibraryA (our DLL path)
    0 - Creation flags (0 = run immediately)
    0 - Thread ID (not needed)
    */
    HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, 
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), 
        pDllPath, 0, 0);

    // Step 5: Wait for the remote thread to finish execution
    // hThread - Handle to the thread to wait for
    // INFINITE - Wait indefinitely until thread completes
    WaitForSingleObject(hThread, INFINITE);

    // Cleanup resources
    CloseHandle(hThread);                    // Close thread handle
    VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);  // Free allocated memory
    CloseHandle(hProcess);                   // Close process handle

    std::cout << "Injection Complete!" << std::endl;
    return 0;
}