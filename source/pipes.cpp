#include "pipes.h"
#include "includes.h"

struct Pipe {
    int x, y;
    int dir;
    int color;
};

void cmd_pipes() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(static_cast<unsigned int>(time(nullptr)));

    const char* glyphs[4][4] = {
        { "║", "╔", "║", "╗" },
        { "╚", "═", "╔", "═" },
        { "║", "╚", "║", "╝" },
        { "╝", "═", "╗", "═" }
    };

    int screenWidth = 80;
    int screenHeight = 25;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    system("cls");

    const int maxPipes = 15;
    Pipe pipes[maxPipes];

    auto resetPipe = [&](Pipe& p) {
        p.x = rand() % screenWidth;
        p.y = rand() % screenHeight;
        p.dir = rand() % 4;
        p.color = 1 + (rand() % 14);
        if (p.color == 7 || p.color == 8) p.color = 9;
        };

    for (int i = 0; i < maxPipes; i++) {
        resetPipe(pipes[i]);
    }

    while (!_kbhit()) {
        for (int i = 0; i < maxPipes; i++) {
            int oldDir = pipes[i].dir;

            if (rand() % 4 == 0) {
                int turn = (rand() % 2 == 0) ? 1 : 3;
                pipes[i].dir = (pipes[i].dir + turn) % 4;
            }

            COORD pos = { static_cast<SHORT>(pipes[i].x), static_cast<SHORT>(pipes[i].y) };
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, pipes[i].color);
            std::cout << glyphs[oldDir][pipes[i].dir];

            if (pipes[i].dir == 0) pipes[i].y--;
            else if (pipes[i].dir == 1) pipes[i].x++;
            else if (pipes[i].dir == 2) pipes[i].y++;
            else if (pipes[i].dir == 3) pipes[i].x--;

            if (pipes[i].x < 0 || pipes[i].x >= screenWidth || pipes[i].y < 0 || pipes[i].y >= screenHeight) {
                resetPipe(pipes[i]);
            }
        }
        std::cout.flush();
        Sleep(60);
    }

    static_cast<void>(_getch());

    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    SetConsoleTextAttribute(hConsole, 7);
    system("cls");
}
