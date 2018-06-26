#include "TextFile.h"

TextFile::TextFile(const std::string & pathname) {
	_pathname = pathname;
	_readSize = 0;
	_current = 0;
	_file = fopen(pathname.c_str(), "rb");
	if (!_file) {
		std::cout << "Cannot open " << pathname << '\n';
	}
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
	while (!isspace(_buf[_current])) {
		_tmp[localCurrent] = _buf[_current];
		_current++;
		localCurrent++;
		if (_current == _readSize && !readBuffer()) { // End of buffer
			break;
		}
	}

	// Break out space
	while (_current < _readSize && isspace(_buf[_current])) {
		_current++;
	}

	// build string
	_tmp[localCurrent] = 0; // end of string
	result = _tmp;

	return true;
}

bool TextFile::readBuffer() {
	_readSize = fread(_buf, sizeof(char), BUFFER_SIZE, _file);
	_current = 0;
	if (_readSize == 0) {
		return false;
	}
	return true;
}
