#include "cowsay.h"
#include "includes.h"

void CmdCowsay(std::string args) {
	if (args.empty()) {
		std::cout << "Eror try [cowsay 'text']" << std::endl;
	}

    std::string top_border = "_________________";
    std::string border = "_________________";

    std::cout << " " << top_border << "\n"
        << "< " << args << " >\n"
        << " " << border << R"(
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
)" << std::endl;
}