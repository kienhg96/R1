#include <iostream>
#include <cctype>
#include <chrono>
#include "ReadDirectory.h"
#include "TextFile.h"
#include "Dict.h"

void showHelp() {
	std::cout << "Usage:\n\t" << "coccoc \"many words\" [path to dictionary]\n";
}

int main(int argc, char *argv[]) {
	std::string dir = ".";
	std::string queryStr;
	if (argc <= 1) {
		showHelp();
		return 0;
	} else if (argc == 2) {
		queryStr = argv[1];
	} else {
		queryStr = argv[1];
		dir = argv[2];
	}
	auto timeStart = std::chrono::steady_clock::now();
	// Start indexing
	std::cout << "Start Indexing "<< dir << '\n';
	auto fileList = ReadDirectory::getInstance()->lsRegularFilesRecursive(dir);
	TextFile document;
	Dict dict;
	for (auto it = fileList.begin(); it != fileList.end(); ++it) {
		std::cout << "Reading: " << it->getPathname() << " ... ";
		document.reset(&(*it));
		if (document.isValidTextFile()) {
			std::cout << " [OK]\n";
			dict.addDocument(document);
		} else {
			std::cout << " [Ignore] Binary file \n";
		}
	}
	auto timeEnd = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeStart);
	std::cout << "Indexing Done.\nIndexing time: " << duration.count() << " ms\n";

	// Start query
	std::cout << "===========================" << '\n';
	timeStart = std::chrono::steady_clock::now();
	auto queryResult = dict.query(queryStr);
	std::cout << "Result for '" << queryStr << "':\n";
	for (auto it = queryResult.begin(); it != queryResult.end(); it++) {
		std::cout << (*it)->getPathname() << '\n';
	}
	ReadDirectory::destroy();

	timeEnd = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeStart);
	std::cout << "===========================\nQuery time: " << duration.count() << " ms\n";
	return 0;
}
