#include "TextFile.h"

TextFile::TextFile(FileNode * filenode) {
	reset(filenode);
}

TextFile::TextFile() {
	_pathname = "";
	_readSize = 0;
	_current = 0;
	_valid = false;
	_file = nullptr;
}

TextFile::~TextFile() {
	if (_file) {
		fclose(_file);
	}
}

bool TextFile::readNextWord(std::string & result) {
	if (_current == _readSize && !readBuffer()) {
		return false;
	}
	// Build block
	int localCurrent = 0;
	while (!isSpace(_buf[_current]) && localCurrent < MAX_WORD_SIZE) {
		_tmp[localCurrent] = _buf[_current];
		_current++;
		localCurrent++;
		if (_current == _readSize && !readBuffer()) { // End of buffer
			break;
		}
	}

	// Break out space
	while (_current < _readSize && isSpace(_buf[_current])) {
		_current++;
	}

	// build string
	_tmp[localCurrent] = 0; // end of string
	result = _tmp;
	return true;
}

std::string TextFile::getPathname() {
	return _pathname;
}

void TextFile::reset(FileNode * fileNode) {
	_pathname = fileNode->getPathname();
	_fileNode = fileNode;
	_readSize = 0;
	_current = 0;
	_valid = false;
	if (_file) {
		fclose(_file);
	}
	_file = fopen(_pathname.c_str(), "rb");
	if (!_file) {
		std::cout << "Cannot open " << _pathname;
	} else {
		checkValidTextFile();
	}
}

FileNode * TextFile::getFileNode() {
	return _fileNode;
}

bool TextFile::isValidTextFile() {
	return _valid;
}

bool TextFile::readBuffer() {
	_readSize = fread(_buf, sizeof(char), BUFFER_SIZE, _file);
	_current = 0;
	if (_readSize == 0) {
		return false;
	}
	return true;
}

int TextFile::isSpace(int character)
{
	return isspace(static_cast<unsigned char>(character));
}

void TextFile::checkValidTextFile() {
	unsigned char buf[HEAD_SIZE_CHECK_BINARY]; // check some bytes first
	int size = fread(buf, sizeof(unsigned char), HEAD_SIZE_CHECK_BINARY, _file);
	rewind(_file);
	int val;
	for (int i = 0; i < size; i++) {
		val = buf[i];
		if (!((val >= 9 && val <= 13) || (val >= 32 && val <= 126))) {
			_valid = false;
			return;
		}
	}
	_valid = true;
}
