#ifndef __READ_DIRECTORY__
#define __READ_DIRECTORY__
#include <vector>
#include <dirent.h>
#include "Node.h"

class ReadDirectory {
private:
	ReadDirectory();
public:
	~ReadDirectory();
	static ReadDirectory * getInstance();
	static void destroy();

	std::vector<Node> ls(const std::string & pathname = ".");
	std::string join(const std::string & path1, const std::string & path2);
private:
	static ReadDirectory * _instance;
};

#endif // __READ_DIRECTORY__
