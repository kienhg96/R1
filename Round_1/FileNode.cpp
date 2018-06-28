#include "FileNode.h"

FileNode::FileNode() {
	_pathname = "";
	_type = NodeType::REG;
}

FileNode::FileNode(std::string pathname, NodeType type) {
	_pathname = pathname;
	_type = type;
}

FileNode::~FileNode() {}

bool FileNode::isRegularFile() const {
	return _type == NodeType::REG;
}

bool FileNode::isDirectory() const {
	return _type == NodeType::DIR;
}

std::string FileNode::getPathname() const {
	return _pathname;
}

void FileNode::saveToFile(FILE * file) const {
	writeString(file, _pathname);
	char type = static_cast<int>(_type);
	fwrite(&type, sizeof(char), 1, file);
}

void FileNode::writeString(FILE * file, const std::string & str) const {
	int size = str.size();
	/* String size */
	fwrite(&size, sizeof(int), 1, file);
	/* String content */
	fwrite(str.c_str(), size * sizeof(char), 1, file);
}
