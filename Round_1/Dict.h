#ifndef __DICT__ 
#define __DICT__
#include <map>
#include "DictList.h"

class Dict {
public:
	Dict();
	~Dict();
private:
	std::map<std::string, DictList> _dictMap;
};

#endif // __DICT__
