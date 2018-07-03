#include "StringUtils.h"

bool StringUtils::isSeperateChar(int c) {
	char castC = static_cast<unsigned char>(c);
	return isspace(castC) != 0 || ispunct(castC) != 0;
}

void StringUtils::writeString(FILE * file, const std::string & str) {
	int size = str.size();
	/* String size */
	fwrite(&size, sizeof(int), 1, file);
	/* String content */
	if (size > 0) {
		fwrite(str.c_str(), size * sizeof(char), 1, file);
	}
}


void StringUtils::readString(FILE * file, std::string & str) {
	int size;
	fread(&size, sizeof(int), 1, file);
	if (size > 0) {
		char * tmp = new char[size + 1];
		fread(tmp, sizeof(char), size, file);
		tmp[size] = 0;
		str = tmp;
		delete[] tmp;
	} else {
		str = "";
	}
}
