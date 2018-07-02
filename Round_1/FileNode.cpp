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

void FileNode::readFromFile(FILE * file) {
	readString(file, _pathname);
	char type;
	fread(&type, sizeof(char), 1, file);
	_type = static_cast<NodeType>(type);
}

void FileNode::writeString(FILE * file, const std::string & str) const {
	int size = str.size();
	/* String size */
	fwrite(&size, sizeof(int), 1, file);
	/* String content */
	if (size > 0) {
		fwrite(str.c_str(), size * sizeof(char), 1, file);
	}
}

void FileNode::readString(FILE * file, std::string & str) {
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
