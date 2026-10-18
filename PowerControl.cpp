#include "PowerContor.h"
#include "includes.h"

void ShutDownPc() {
    std::cout << "shutdown pc in 5 seconds!" << std::endl;
    system("shutdown /s /f /t 5");
}

void RestartPc() {
    std::cout << "reboot pc in 5 seconds!" << std::endl;
    system("shutdown /r /f /t 5");
}

void SleepPc() {
    std::cout << "sleeping pc in 5 seconds!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    system("powercfg -h off");
    system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
    system("powercfg -h on");
}