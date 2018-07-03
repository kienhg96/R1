#ifndef __STRING_UTILS__
#define __STRING_UTILS__
#include <cctype>
#include <string>
#include <cstdlib>

class StringUtils {
public:
	static bool isSeperateChar(int c);
	static void writeString(FILE * file, const std::string & str);
	static void StringUtils::readString(FILE * file, std::string & str);
};

#endif // __STRING_UTILS__
