/*
	Contains all file's id containing same word
	(forward_list + size)
*/

#ifndef __DICT_LIST__
#define __DICT_LIST__
#include <forward_list>
#include <cstddef>

class DocIdList {
public:
	DocIdList();
	~DocIdList();

	size_t size();
	std::forward_list<int> * list();
	void add(int elem);
	int last();
	void clear();

	void saveToFile(FILE * file);
	void readFromFile(FILE * file);
private:
	size_t _size;
	std::forward_list<int> * _list;
};

#endif // __DICT_LIST__
