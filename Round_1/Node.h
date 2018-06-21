#ifndef __NODE__
#define __NODE__
#include <string>

class Node {
public:
	enum class NodeType { DIR, REG };
	Node();
	Node(std::string pathname, NodeType type);
	~Node();
private:
	std::string _pathname;
	NodeType _type;
};

#endif
