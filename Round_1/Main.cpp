#include <iostream>
#include <cctype>
#include "ReadDirectory.h"
#include "TextFile.h"

using namespace std;

int main() {
	auto result = ReadDirectory::getInstance()->lsRegularFilesRecursive(".");
	for (auto it = result.begin(); it != result.end(); ++it) {
		std::cout << it->getPathname() << '\n';
	}
	ReadDirectory::destroy();

	TextFile text("D:\\Pass_Wifi.txt");
	std::string tmp;
	while (text.readNextWord(tmp)) {
		std::cout << "Next: " << tmp << '\n';
	}

	// getchar();
	return 0;
}
