#include "fastfetch.h"
#include "includes.h"
#include <winreg.h>

std::string getRegistryString(HKEY hKeyParent, const char* subKey, const char* valueName) {
    HKEY hKey;
    char value[256];
    DWORD value_length = sizeof(value);
    if (RegOpenKeyExA(hKeyParent, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, valueName, NULL, NULL, (LPBYTE)value, &value_length) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return std::string(value);
        }
        RegCloseKey(hKey);
    }
    return "Unknown";
}

void cmd_fastfetch() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(username, &username_len);

    char computername[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computername_len = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(computername, &computername_len);

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::string arch = "Unknown";
    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) arch = "x86_64";
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) arch = "x86";
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) arch = "ARM64";

    ULONGLONG uptimeMs = GetTickCount64();
    int uptimeHours = (int)(uptimeMs / (1000 * 60 * 60));
    int uptimeMinutes = (int)((uptimeMs / (1000 * 60)) % 60);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalRAM = memInfo.ullTotalPhys / (1024 * 1024);
    DWORDLONG freeRAM = memInfo.ullAvailPhys / (1024 * 1024);
    DWORDLONG usedRAM = totalRAM - freeRAM;
    int memPercent = (int)((usedRAM * 100) / totalRAM);

    std::string cpuName = getRegistryString(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString");
    size_t first = cpuName.find_first_not_of(' ');
    if (std::string::npos != first) cpuName = cpuName.substr(first);

    std::string gpuName = getRegistryString(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT", "PrimaryAdapterString");
    if (gpuName == "Unknown") {
        gpuName = getRegistryString(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", "DriverDesc");
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    auto setBlue = [&]() { SetConsoleTextAttribute(hConsole, 9); };
    auto setWhite = [&]() { SetConsoleTextAttribute(hConsole, 7); };

    std::cout << "\n";

    
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   "; setBlue();  std::cout << username; setWhite(); std::cout << "@"; setBlue(); std::cout << computername << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   -------------------\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   OS: Windows 11 / 10 " << arch << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Kernel: Windows_NT\n";

    
    std::cout << "                   " << "   "; std::cout << " Uptime: " << uptimeHours << " hours, " << uptimeMinutes << " mins\n";

    
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Shell: WindowsShell (C++)\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Display: " << screenWidth << "x" << screenHeight << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   CPU: " << cpuName << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   GPU: " << gpuName << "\n";

    
    std::cout << "                   " << "   "; std::cout << " Memory: " << usedRAM << " MB / " << totalRAM << " MB (" << memPercent << "%)\n";
    std::cout << "                   " << "   "; std::cout << "\n";

    
    std::cout << "                   " << "   ";
    for (int i = 0; i < 8; i++) {
        SetConsoleTextAttribute(hConsole, i);
        std::cout << "██";
    }
    std::cout << "\n                   " << "   ";
    for (int i = 8; i < 16; i++) {
        SetConsoleTextAttribute(hConsole, i);
        std::cout << "██";
    }

    setWhite();
    std::cout << "\n\n";
}