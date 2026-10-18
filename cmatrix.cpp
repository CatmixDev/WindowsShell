#include "cmatrix.h"
#include "includes.h"


void Cmd_Cmatrix() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	system("cls");
	system("color 2");

	std::string chars = "QWERTYUIOPLKJHGFDSA2346";
	int width = 160;

	
	std::vector<int> rain(width, 0);

	while (true) {
		
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			std::cout << "\nback..." << std::endl;
			system("cls");
			system("color 07");

			Sleep(500);
			return;
		}

		
		for (int i = 0; i < width; i++) {
			if (rain[i] > 0) {
				
				std::cout << chars[std::rand() % chars.length()];
				rain[i]--;
			}
			else {
				
				std::cout << ' ';

				
				if (std::rand() % 10 == 0) {
					rain[i] = 10 + std::rand() % 30;
				}
			}
		}
		std::cout << '\n';

		
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}
