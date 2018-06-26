#ifndef __TEXT_FILE__
#define __TEXT_FILE__
#include <string>
#include <iostream>
#include <cstdio>

#define BUFFER_SIZE 4096 // 4MiB
#define MAX_WORD_SIZE 50

class TextFile {
public:
	TextFile(const std::string & pathname);
	~TextFile();

	bool readNextWord(std::string & result);
private:
	bool readBuffer();
private:
	char _buf[BUFFER_SIZE];
	std::string _pathname;
	size_t _readSize;
	size_t _current;
	FILE * _file;
	char _tmp[MAX_WORD_SIZE];
};

#endif
