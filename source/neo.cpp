#include "neo.h" 
#include "includes.h"

void cmd_neo(std::string filename) {
    if (filename.empty()) {
        std::cout << "Error: No filename specified. Usage: neo [filename]\n";
        return;
    }

    std::filesystem::path filePath(filename);
    std::string text = "";

    if (std::filesystem::exists(filePath)) {
        std::ifstream inFile(filePath);
        if (inFile) {
            std::string line;
            while (std::getline(inFile, line)) {
                text = text + line + "\n";
            }
        }
        inFile.close();
    }

    system("cls");
    std::cout << "=== NEO Editor (File: " << filename << ") ===\n";
    std::cout << "[ Hotkeys: Ctrl+S - Save | Esc - Exit ]\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << text;

    while (true) {
        int ch = _getch();

        if (ch == 19) {
            std::ofstream outFile(filePath);
            if (outFile) {
                outFile << text;
                outFile.close();
                std::cout << "\n[Saved!]";
                std::this_thread::sleep_for(std::chrono::milliseconds(600));
            }
            system("cls");
            std::cout << "=== NEO Editor (File: " << filename << ") ===\n";
            std::cout << "[ Hotkeys: Ctrl+S - Save | Esc - Exit ]\n";
            std::cout << "--------------------------------------------------\n";
            std::cout << text;
        }
        else if (ch == 27) {
            break;
        }
        else if (ch == 13) {
            text = text + "\n";
            std::cout << "\n";
        }
        else if (ch == 8) {
            if (text.empty() == false) {
                text.pop_back();
                system("cls");
                std::cout << "=== NEO Editor (File: " << filename << ") ===\n";
                std::cout << "[ Hotkeys: Ctrl+S - Save | Esc - Exit ]\n";
                std::cout << "--------------------------------------------------\n";
                std::cout << text;
            }
        }
        else if (ch >= 32) {
            text = text + (char)ch;
            std::cout << (char)ch;
        }
    }

    system("cls");
}
