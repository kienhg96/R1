#include "ReadDirectory.h"
#include <iostream>

ReadDirectory * ReadDirectory::_instance = nullptr;

ReadDirectory::ReadDirectory() {}

ReadDirectory::~ReadDirectory() {}

ReadDirectory * ReadDirectory::getInstance() {
	if (!_instance) {
		_instance = new ReadDirectory();
	}
	return _instance;
}

void ReadDirectory::destroy() {
	delete _instance;
	_instance = nullptr;
}

std::vector<Node> ReadDirectory::ls(const std::string & pathname) {
	DIR * dir;
	struct dirent *ent;
	if ((dir = opendir(pathname.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			bool isFile = ent->d_type == DT_REG;
			if (ent->d_type == DT_REG) {
				// Files
			} else if (ent->d_type == DT_DIR) {
				 // Directory
			} else {
				// Ignore
				std::cout << "Ignore: " << join(pathname, ent->d_name) << ", type: " << ent->d_type << std::endl;
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		std::cout << "Could not open directory" << std::endl;
	}
}

std::string ReadDirectory::join(const std::string & path1, const std::string & path2) {
	char sep = '/';
	std::string tmp = path1;
#ifdef _WIN32
	sep = '\\';
#endif
	if (path1[path1.length()] != sep) { // Need to add a
		tmp += sep;                // path separator
		return tmp + path2;
	} else
		return path1 + path2;
}
