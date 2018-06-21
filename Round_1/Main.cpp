#include <iostream>
#include <dirent.h>
#include "ReadDirectory.h"

using namespace std;

int main() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("C:")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			bool isFile = ent->d_type == DT_REG;
			cout << ent->d_name << " , isFile: " << isFile << endl;
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		cout << "Could not open directory" << endl;
		return -1;
	}
	ReadDirectory * readInstance = ReadDirectory::getInstance();
	ReadDirectory::destroy();
	return 0;
}
