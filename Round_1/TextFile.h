#ifndef __TEXT_FILE__
#define __TEXT_FILE__
#include <string>
#include <iostream>
#include <cstdio>
#include "FileNode.h"

#define BUFFER_SIZE 4096 // 4MiB
#define MAX_WORD_SIZE 20
#define HEAD_SIZE_CHECK_BINARY 128 // 128 bytes

class TextFile {
public:
	TextFile(FileNode * filenode);
	TextFile();
	~TextFile();

	bool readNextWord(std::string & result);
	std::string getPathname();
	void reset(FileNode * filenode);
	FileNode * getFileNode();
	bool isValidTextFile();
private:
	bool readBuffer();
	int isSpace(int character);
	void checkValidTextFile();
private:
	char _buf[BUFFER_SIZE];
	std::string _pathname;
	size_t _readSize;
	size_t _current;
	FILE * _file;
	char _tmp[MAX_WORD_SIZE];
	FileNode * _fileNode;
	bool _valid;
};

#endif
