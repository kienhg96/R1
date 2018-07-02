#include "DocIdList.h"

DocIdList::DocIdList() {
	_size = 0;
	_list = new std::forward_list<int>;
}

DocIdList::~DocIdList() {
	delete _list;
}

size_t DocIdList::size() {
	return _size;
}

std::forward_list<int> * DocIdList::list() {
	return _list;
}

void DocIdList::add(int elem) {
	if (_size == 0 || elem != last()) {
		_list->push_front(elem);
		_size++;
	}
}

int DocIdList::last() {
	return _list->front();
}

void DocIdList::clear() {
	_size = 0;
	_list->clear();
}

void DocIdList::saveToFile(FILE * file) {
	/* size of map */
	fwrite(&_size, sizeof(size_t), 1, file);
	int val;
	for (auto it = _list->begin(); it != _list->end(); it++) {
		val = *it;
		fwrite(&val, sizeof(int), 1, file);
	}
}

void DocIdList::readFromFile(FILE * file) {
	fread(&_size, sizeof(size_t), 1, file);
	int val;
	for (size_t i = 0; i < _size; i++) {
		fread(&val, sizeof(int), 1, file);
		_list->push_front(val);
	}
	_list->reverse();
}
