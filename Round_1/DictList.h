#ifndef __DICT_LIST__
#define __DICT_LIST__
#include <forward_list>

class DictList {
public:
	DictList();
	~DictList();

	size_t size();
	std::forward_list<int> * list();
	void add(int elem);
	int last();
	void clear();

private:
	size_t _size;
	std::forward_list<int> * _list;
};

#endif // __DICT_LIST__
