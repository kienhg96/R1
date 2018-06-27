#ifndef __DICT__ 
#define __DICT__
#include <map>
#include <vector>
#include "DictList.h"
#include "TextFile.h"
#include "FileNode.h"

class Dict {
public:
	Dict();
	~Dict();

	void addDocument(TextFile & textFile);
	std::forward_list<FileNode *> query(const std::string q);
private:
	std::vector<std::string> split(const std::string & phrase, char delimiter);
	void sortListDictListBySize(DictList ** listDictList, int left, int right);
	std::forward_list<int> findDupplicateItems(std::forward_list<int> * list1, std::forward_list<int> * list2);
private:
	std::map<std::string, DictList> _dictMap;
	std::map<int, FileNode*> _docMap;
};

#endif // __DICT__
