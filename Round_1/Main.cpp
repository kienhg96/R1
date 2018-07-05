#include <iostream>
#include <cctype>
#include "ReadDirectory.h"
#include "TextFile.h"
#include "Dict.h"
#include "ParseParams.h"
#include "TimeMeter.h"

#define INDEX_ONLY		0x00000001
#define SAVE_OUTPUT		0x00000010
#define READ_INPUT		0x00000100
#define DEFAULT_PARAMS	0x00000000

const char * help =
"Usage:\n"
"\tcoccoc \"many words\" [path to dictionary]\n"
"\tExample: coccoc \"hello, world\" ./sample_data\n\n"
"Save index data and query:\n"
"\tcoccoc \"many words\" [path to dictionary] -s <path to save index data>\n"
"\tExample: coccoc \"hello, world\" ./sample_data -s ./index.dat\n\n"
"Index only and save index data:\n"
"\tcoccoc [path to dictionary] -i <path to save index data>\n"
"\tExample: coccoc ./sample_data -i ./index.dat\n\n"
"Load index data and query:\n"
"\tcoccoc \"many words\" -r <path to saved index data>\n"
"\tExample: coccoc \"hello, world\" -r ./index.dat\n";

void showHelp() {
	std::cout << help;
}

int main(int argc, char *argv[]) {
	std::string dir, queryStr, outputFile, inputFile;
	ParseParams parser(argc, argv);
	TimeMeter timeMeter;
	int mode = DEFAULT_PARAMS;

	if (argc <= 1) {
		showHelp();
		return 0;
	}

	if (parser.hasArgument("-i")) {
		// Index only "-i <output file>"
		outputFile = parser.getArgument("-i");
		mode |= INDEX_ONLY;
	} else if (parser.hasArgument("-s")) {
		// Save index output to file "-s <output file>"
		outputFile = parser.getArgument("-s");
		mode |= SAVE_OUTPUT;
	} else if (parser.hasArgument("-r")) {
		// Read index file from input "-r <input file>"
		inputFile = parser.getArgument(("-r"));
		mode |= READ_INPUT;
	}

	if ((mode == DEFAULT_PARAMS) || (mode & SAVE_OUTPUT)) {
		queryStr = parser.getFreeArg(1);
		dir = parser.getFreeArg(2, ".");
	} else if (mode & INDEX_ONLY) {
		dir = parser.getFreeArg(1, ".");
	} else if (mode & READ_INPUT) {
		queryStr = parser.getFreeArg(1);
	}
	if (!(mode & INDEX_ONLY) && queryStr == "") {
		showHelp();
		return 0;
	}

	Dict dict;
	std::forward_list<FileNode> fileList;
	
	// Index from directory
	if ((mode & SAVE_OUTPUT) || (mode & INDEX_ONLY) || (mode == DEFAULT_PARAMS)) {
		std::cout << "Start Indexing \"" << dir << "\"...\n";
		timeMeter.start();
		TextFile document;
		// Index and save to file
		fileList = ReadDirectory::getInstance()->lsRegularFilesRecursive(dir);
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
		if (mode & (SAVE_OUTPUT | INDEX_ONLY)) {
			dict.saveToFile(outputFile);
		}
		timeMeter.end();
		std::cout << "Indexing Done.\n<Indexing time: ~" << timeMeter.getTime() << " ms>\n";
	} else if (mode & READ_INPUT) {
		std::cout << "Reading index data from " << inputFile << " ... ";
		timeMeter.start();
		if (dict.readFromFile(inputFile)) {
			timeMeter.end();
			std::cout << "OK\n<Read time: ~" << timeMeter.getTime() << " ms>\n";
		} else {
			std::cout << "Failed.\nError: Cannot open " << inputFile << "\n";
			return 0;
		}
	}

	if (!(mode & INDEX_ONLY)) {
		std::cout << "=========================\n";
		// Query mode
		timeMeter.start();
		auto queryResult = dict.query(queryStr);
		timeMeter.end();
		std::cout << "Query results for '" << queryStr << "':\n";
		if (queryResult.begin() == queryResult.end()) {
			std::cout << "[Empty]\n";
		} else {
			for (auto it = queryResult.begin(); it != queryResult.end(); it++) {
				std::cout << (*it).getPathname() << '\n';
			}
		}
		std::cout << "<Query time: ~" << timeMeter.getTime() << " ms>\n";
	}
	
	ReadDirectory::destroy();
	return 0;
}
