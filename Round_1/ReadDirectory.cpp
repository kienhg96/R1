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
	if (_instance) {
		delete _instance;
	}
	_instance = nullptr;
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

std::forward_list<FileNode> ReadDirectory::ls(const std::string & pathname) {
	DIR * dir;
	struct dirent * ent;
	std::forward_list<FileNode> result;
	if ((dir = opendir(pathname.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			bool isFile = ent->d_type == DT_REG;
			if (ent->d_type == DT_REG) {
				// Files
				FileNode file(join(pathname, ent->d_name), FileNode::NodeType::REG);
				result.push_front(file);
			} else if (ent->d_type == DT_DIR) {
				 // Directory
				if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) { // Exclude current and parent dirs
					FileNode file(join(pathname, ent->d_name), FileNode::NodeType::DIR);
					result.push_front(file);
				}
			} else {
				// Ignore
				std::cout << "Ignore: " << join(pathname, ent->d_name) << ", type: " << ent->d_type << '\n';
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		std::cout << "Could not open directory" << '\n';
	}
	return result;
}

std::forward_list<FileNode> ReadDirectory::lsRegularFilesRecursive(const std::string & pathname) {
	std::forward_list<FileNode> result;
	std::forward_list<FileNode> queue;
	FileNode root(pathname, FileNode::NodeType::DIR); // Create root dir
	queue.push_front(root); // Push root to queue
	size_t queueSize = 1;

	while (queueSize) {
		FileNode dir = queue.front();
		queue.pop_front();
		queueSize--;
		std::forward_list<FileNode> files = ls(dir.getPathname());

		for (auto it = files.begin(); it != files.end(); ++it) {
			if (it->isRegularFile()) {
				// is Files
				result.push_front(*it);
			} else {
				// is Dir
				queue.push_front(*it);
				queueSize++;
			}
		}
	}
	return result;
}
