#include <iostream>
#include <vector>
#include <Shlwapi.h> // PathFileExists
#include "../../Core/MemWarsCore.h"
#include "../../Core/MemWarsServicesCore.h"
#include "ThreadHijack.h"

using namespace std;

void ThreadHijackTest() {
    
    system("start /B memoryTestApp.exe");
    HANDLE hProcess = NULL;
    while (hProcess == NULL) {
        hProcess = (HANDLE)GetProcessByName("memoryTestApp.exe");
    }

    vector<DWORD> pids = GetPIDsOfProcess(L"memoryTestApp.exe");
    if (pids.empty()) {
        cout << "ThreadHijackTest() failed. Pids not found" << endl;
        system("taskkill /IM memoryTestApp.exe /F >nul");
        return;
    }
    DWORD pid = pids[0];
    vector<DWORD> tids = GetTIDChronologically(pid);
    if (tids.empty()) {
        cout << "ThreadHijackTest() failed. Tids not found" << endl;
        system("taskkill /IM memoryTestApp.exe /F >nul");
        return;
    }
    DWORD tid = tids[0];
    
    int ret = ThreadHijack(hProcess, tid);
    if (ret != 0) {
        cout << "ThreadHijackTest() failed: " << ret << endl;
        goto Exit;
    }

    TCHAR filename[MAX_PATH];
    GetTempPath(MAX_PATH, filename);
    lstrcatA(filename, "hijackConfirmationFile");

    if (!PathFileExists(filename)) {
        cout << "ThreadHijackTest() failed" << endl;
        goto Exit;
    } else {
        cout << "ThreadHijackTest() success" << endl;
        system("taskkill /IM memoryTestApp.exe /F >nul");
        DeleteFile(filename);
        return;
    }
    
    Exit:
    system("taskkill /IM memoryTestApp.exe /F >nul");
}

int main() {
    ThreadHijackTest();
}