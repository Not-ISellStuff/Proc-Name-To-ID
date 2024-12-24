#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

DWORD procid(const std::string& proc) {
    PROCESSENTRY32 proce;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hsnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    proce.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &proce)) {
        while (Process32Next(hsnap, &proce)) {
            if (proc == proce.szExeFile) {
                CloseHandle(hsnap);
                return proce.th32ProcessID;
            }
        }
    }

    CloseHandle(hsnap);
    return 0;
}

int main() {
    std::string proc = "Notepad.exe";
    DWORD pid = procid(proc);

    if (pid != 0) {
        std::cout << pid;
    } else {
        std::cout << "Failed to get pid";
    }
}
