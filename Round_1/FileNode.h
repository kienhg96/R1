#ifndef __NODE__
#define __NODE__
#include <string>
#include "StringUtils.h"

class FileNode {
public:
	enum class NodeType { DIR, REG };
	FileNode();
	FileNode(std::string pathname, NodeType type);
	~FileNode();

public:
	bool isRegularFile() const;
	bool isDirectory() const;
	std::string getPathname() const;

	void saveToFile(FILE * file) const;
	void readFromFile(FILE * file);
private:
	std::string _pathname;
	NodeType _type;
};

#endif
