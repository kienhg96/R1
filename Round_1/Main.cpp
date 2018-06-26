#include <iostream>
#include "ReadDirectory.h"
#include <forward_list>

using namespace std;

int main() {
	ReadDirectory * readInstance = ReadDirectory::getInstance();
	ReadDirectory::destroy();

	return 0;
}
