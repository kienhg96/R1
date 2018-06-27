#include "DictList.h"

DictList::DictList() {
	_size = 0;
	_list = new std::forward_list<int>;
}

DictList::~DictList() {
	delete _list;
}

size_t DictList::size() {
	return _size;
}

std::forward_list<int> * DictList::list() {
	return _list;
}

void DictList::add(int elem) {
	if (_size == 0 || elem != last()) {
		_list->push_front(elem);
		_size++;
	}
}

int DictList::last() {
	return _list->front();
}

void DictList::clear() {
	_size = 0;
	_list->clear();
}
