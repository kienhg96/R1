#ifndef __READ_DIRECTORY__
#define __READ_DIRECTORY__
#include <forward_list>
#include <dirent.h>
#include <cstring>
#include "FileNode.h"

class ReadDirectory {
private:
	ReadDirectory();
public:
	~ReadDirectory();
	static ReadDirectory * getInstance();
	static void destroy();

	std::string join(const std::string & path1, const std::string & path2);
	std::forward_list<FileNode> ls(const std::string & pathname = ".");
	std::forward_list<FileNode> lsRegularFilesRecursive(const std::string & pathname = ".");
private:
	static ReadDirectory * _instance;
};

#endif // __READ_DIRECTORY__
