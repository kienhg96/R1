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
