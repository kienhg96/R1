#ifndef __DICT__ 
#define __DICT__
#include <map>
#include <vector>
#include "DocIdList.h"
#include "TextFile.h"
#include "FileNode.h"

class Dict {
public:
	Dict();
	~Dict();

	void addDocument(TextFile & textFile);
	std::forward_list<FileNode *> query(const std::string q);

	void saveToFile(const std::string path);
private:
	std::vector<std::string> split(const std::string & phrase, char delimiter);
	void sortListDictListBySize(DocIdList ** listDictList, int left, int right);
	std::forward_list<int> findDupplicateItems(std::forward_list<int> * list1, std::forward_list<int> * list2);

	void writeDocIdListMap(FILE * file, std::map<std::string, DocIdList> & docIdListMap);
	void writeDocMap(FILE * file, std::map<int, FileNode*> & docMap);

	void writeString(FILE * file, std::string str);
private:
	// Mapping word to list of documentIDs
	std::map<std::string, DocIdList> _docIdListMap;
	// Mapping documentID to documentFile
	std::map<int, FileNode*> _docMap;
};

#endif // __DICT__
