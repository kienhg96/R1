#ifndef __PARSE_PARAMS__
#define __PARse_PARAMS__
#include <string>
#include <map>
#include <vector>

class ParseParams {
public:
	ParseParams(int argc, char *argv[]);
	~ParseParams();
	bool hasArgument(const std::string & key);
	std::string getArgument(const std::string & key);
	std::string getFreeArg(size_t index, const std::string defaultStr = ".");
private:
	void parseArgument(int * pIndex);
	void parseFreeArgument(int index);
private:
	std::map<std::string, std::string> _paramMap;
	std::vector<std::string> _freeParams;
	int _argc;
	char ** _argv;
};

#endif // __PARSE_PARAMS__
