#include "includes.h"
#include "neo.h"
#include "figlet.h"
#include "PowerContor.h"
#include "cmatrix.h"
namespace fs = std::filesystem;

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

void dev_collect_all_code() {
    std::string out_name = "all_source_code.txt";
    std::ofstream out(out_name);
    if (!out) return;

    try {
        
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();

                
                if (ext == ".cpp" || ext == ".h" || ext == ".rc") {
                    std::string filename = entry.path().filename().string();

                    
                    if (filename == out_name) continue;

                    std::ifstream in(entry.path());
                    if (in) {
                       
                        out << "\n// ==================================================\n";
                        out << "// file: " << filename << "\n";
                        out << "// ==================================================\n\n";

                        std::string line;
                        while (std::getline(in, line)) {
                            out << line << "\n";
                        }
                        in.close();
                    }
                }
            }
        }
        out.close();
    }
    catch (...) {
        
    }
}


void cmd_touch(const std::string& filename) {
    if (filename.empty()) {
        std::cout << "Error: No filename specified.\n";
        return;
    }
    fs::path filePath(filename);
    try {
        if (!fs::exists(filePath)) {
            std::ofstream file(filePath);
            if (!file) {
                std::cerr << "Failed to create file: " << filename << "\n";
                return;
            }
            std::cout << "File created: " << filename << "\n";
        }
        else {
            auto currentTime = fs::file_time_type::clock::now();
            fs::last_write_time(filePath, currentTime);
            std::cout << "File modification time updated: " << filename << "\n";
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}


void cmd_ls() {
    try {
        fs::path currentDir = fs::current_path();
        if (fs::is_empty(currentDir)) {
            std::cout << "(directory is empty)\n";
            return;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (const auto& entry : fs::directory_iterator(currentDir)) {
            std::string name = entry.path().filename().string();

            if (entry.is_directory()) {
                SetConsoleTextAttribute(hConsole, 9);
                std::cout << name << "/\n";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else {
                std::cout << name << "\n";
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error reading directory: " << e.what() << "\n";
    }
}

void cmd_cat(std::string filename) {
    if (filename.empty()) {

        std::cout << "eror name file for    does not exist Try cat 'filename'!\n";
        return;
    }

    std::filesystem::path filePath(filename);

    if (std::filesystem::exists(filePath) == false) {
        std::cout << "Eror File " << filename << " not found!\n";
        return;
    }

    std::ifstream file(filePath);

    if (!file) {
        std::cout << "Eror Can not Open File\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();
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

    auto setBlue = [&]() { SetConsoleTextAttribute(hConsole, 9); };
    auto setWhite = [&]() { SetConsoleTextAttribute(hConsole, 7); };

    std::cout << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   "; setBlue(); std::cout << username; setWhite(); std::cout << "@"; setBlue(); std::cout << computername << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   ---------------------\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   OS: Windows 11 / 10 " << arch << "\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Kernel: Windows_NT\n";
    std::cout << "                    " << "   Uptime: " << uptimeHours << " hours, " << uptimeMinutes << " mins\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Shell: WindowsShell (C++)\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Memory: " << usedRAM << " MB / " << totalRAM << " MB\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   Log: touch, pwd, clear, ls, fastfetch, neo\n";
    setBlue();  std::cout << "█████████  █████████"; setWhite(); std::cout << "   \n\n";
}



std::string get_short_dir_name() {
    try {
        return fs::current_path().filename().string();
    }
    catch (...) {
        return "shell";
    }
}

void Cmd_Help() {
    std::cout << "========================================\n";
    std::cout << "           AVAILABLE COMMANDS           \n";
    std::cout << "========================================\n\n";

    std::cout << "  [POWER]\n";
    std::cout << "    - shutdown, restart, sleep\n\n";

    std::cout << "  [FILESYSTEM]\n";
    std::cout << "    - touch [file], neo [file], ls, pwd\n\n";

    std::cout << "  [CONSOLE OPTIONS]\n";
    std::cout << "    - exit, clear\n\n";

    std::cout << "  [UTILITIES]\n";
    std::cout << "    - fastfetch\n\n";

    std::cout << "========================================" << std::endl;
}

int main() {

    dev_collect_all_code();

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::string inputLine;

   

    while (true) {
        std::cout << "WindowsShell@" << get_short_dir_name() << "> ";

        
        if (!std::getline(std::cin, inputLine)) break;
        if (inputLine.empty()) continue;

        std::string command;
        std::string argument;

        
        size_t spacePos = inputLine.find(' ');
        if (spacePos != std::string::npos) {
            command = inputLine.substr(0, spacePos);
            argument = inputLine.substr(spacePos + 1);

           
            argument.erase(0, argument.find_first_not_of(" "));
        }
        else {
            command = inputLine;
        }

        
        if (command == "exit") {
            break;
        }
        else if (command == "touch") {
            cmd_touch(argument);
        }
        else if (command == "neo") {
            cmd_neo(argument);
        }
        else if (command == "pwd") {
            std::cout << fs::current_path().generic_string() << "\n";
        }
        else if (command == "clear") {
            system("cls");
        }
        else if (command == "ls") {
            cmd_ls();
        }
        else if (command == "fastfetch") {
            cmd_fastfetch();
        }
        else if (command == "shutdown") {
            ShutDownPc();
        }
        else if (command == "sleep") {
            SleepPc();
        }
        else if (command == "restart") {
            RestartPc();
        }
        else if (command == "help") {
            Cmd_Help();
        }

        else if (command == "cat") {
            cmd_cat(argument);
        }

        else if (command == "figlet") {
            cmd_figlet(argument);
        }

        else if (command == "cmatrix") {
            Cmd_Cmatrix();
        }

        else if (command == "beep") {
            Cmd_Beep(argument);
        }

        else {
            std::cout << "Command not found!.\n";
        }
    }

    return 0;
}
