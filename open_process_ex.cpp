#include <iostream>
#include <windows.h>

int main()
{
    int processID =NULL;
    std::cout<<"Give Process ID: ";
    std::cin>>processID;

    //Handle allows us to interact with files, a process
    HANDLE hprocess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    //OpenProcess() tries to get access to a running process

    if(hprocess == NULL){
        std::cout<<"Error Opening process: "<<GetLastError()<<std::endl;
        return 1;
    }

    std::cout<<"Successfully Opened process with ID: "<<processID;


    return 0;
}
/*

t> & .\'open_process_ex.exe'
Give Process ID: 9656
Successfully Opened process with ID: 9656

*/