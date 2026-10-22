#include "ShellComand.h"
#include "includes.h"

void SetsColor(std::string args) {
    if (args.empty()) {
        std::cout << "Eror Try 'color [number]'" << std::endl;
    }



    std::string command = "color " + args;

    system(command.c_str());
}

void Cmd_Beep(std::string arguments) {



    const char* spacePtr = strchr(arguments.c_str(), ' ');


    if (spacePtr == nullptr) {
        std::cout << "USE 'beep [power] [timer]'\n";
        return;
    }

    int power = atoi(arguments.c_str());
    int timer = atoi(strchr(arguments.c_str(), ' '));

    Beep(power * 100, timer * 1000);
}

void Cmd_Ping(std::string args) {
    if (args.empty()) {
        std::cout << "Error try 'ping example.com'" << std::endl;
    }

    std::string command = "ping " + args;

    system(command.c_str());
}

void Cmd_Echo(std::string args) {
    if (args.empty()) {
        std::cout << "Eror Try echo 'text'" << std::endl;
        return;
    }

    std::cout  << args << "\n";
    ShellExecuteA(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOW);
}

