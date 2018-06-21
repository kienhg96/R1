#include "ReadDirectory.h"

ReadDirectory * ReadDirectory::_instance = nullptr;

ReadDirectory::ReadDirectory() {}

ReadDirectory::~ReadDirectory() {}

ReadDirectory * ReadDirectory::getInstance()
{
	if (!_instance) {
		_instance = new ReadDirectory();
	}
	return _instance;
}

void ReadDirectory::destroy()
{
	delete _instance;
	_instance = nullptr;
}
