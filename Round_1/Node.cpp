#include "Node.h"

Node::Node() {
	_pathname = "";
	_type = NodeType::REG;
}

Node::Node(std::string pathname, NodeType type) {
	_pathname = pathname;
	_type = type;
}

Node::~Node() {}
