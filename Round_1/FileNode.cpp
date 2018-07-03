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
	StringUtils::writeString(file, _pathname);
	char type = static_cast<int>(_type);
	fwrite(&type, sizeof(char), 1, file);
}

void FileNode::readFromFile(FILE * file) {
	StringUtils::readString(file, _pathname);
	char type;
	fread(&type, sizeof(char), 1, file);
	_type = static_cast<NodeType>(type);
}
