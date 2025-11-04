#include <windows.h>
#include <winhttp.h>
#include <iostream>
#pragma comment(lib, "winhttp.lib")

int main()
{
    // The URL parts
    LPCWSTR host = L"github.com";
    LPCWSTR path = L"/ALLann123/hugo-blog/releases/download/cNc/command.txt";

    // Open a WinHTTP session
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession)
    {
        std::cerr << "Failed to open WinHTTP session.\n";
        return 1;
    }

    // Connect to the server
    HINTERNET hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect)
    {
        std::cerr << "Failed to connect.\n";
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Create an HTTP request handle
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path,
                                            NULL, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            WINHTTP_FLAG_SECURE);

    if (!hRequest)
    {
        std::cerr << "Failed to open request.\n";
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Send the request
    if (!WinHttpSendRequest(hRequest,
                            WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                            WINHTTP_NO_REQUEST_DATA, 0,
                            0, 0))
    {
        std::cerr << "Failed to send request.\n";
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Wait for response
    if (!WinHttpReceiveResponse(hRequest, NULL))
    {
        std::cerr << "Failed to receive response.\n";
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Read the data
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    do
    {
        // Check available data
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
            break;

        if (dwSize == 0)
            break;

        // Allocate buffer and read
        char *buffer = new char[dwSize + 1];
        ZeroMemory(buffer, dwSize + 1);

        if (WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded))
        {
            std::cout << buffer; // print to console
        }

        delete[] buffer;
    } while (dwSize > 0);

    // Cleanup
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    std::cout << "\nDownload complete.\n";
    return 0;
}

/*
 g++ -Wall -Wextra -g3 "j:\Learning c++\Command_and_control\download_url.cpp" -o "j:\Learning c++\Command_and_control\output\download_url.exe" -lwinhttp

 When run:
J:\Learning c++\Command_and_control\output>download_url.exe
whoami
Download complete.

*/