#ifndef __NODE__
#define __NODE__
class Node
{
public:
	enum class NodeType { DIR, REG };
	Node();
	~Node();
};

#endif