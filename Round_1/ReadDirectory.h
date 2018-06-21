#ifndef __READ_DIRECTORY__
#define __READ_DIRECTORY__
#include <vector>

class ReadDirectory
{
private:
	ReadDirectory();
public:
	~ReadDirectory();
	static ReadDirectory * getInstance();
	static void destroy();

	std::vector<std::string> ls(std::string dir = ".");
private:
	static ReadDirectory * _instance;
};

#endif // __READ_DIRECTORY__
