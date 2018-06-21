#include <iostream>
#include "ReadDirectory.h"

using namespace std;

int main() {
	ReadDirectory * readInstance = ReadDirectory::getInstance();
	ReadDirectory::destroy();
	return 0;
}
