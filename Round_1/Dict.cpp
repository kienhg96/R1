#include "Dict.h"

Dict::Dict() {}

Dict::~Dict() {}

void Dict::addDocument(TextFile & textFile) {
	int id = _docMap.size();
	_docMap[id] = textFile.getFileNode();
	std::string word;
	while (textFile.readNextWord(word)) {
		_dictMap[word].add(id);
	}
}

std::forward_list<FileNode *> Dict::query(const std::string q) {
	std::vector<std::string> words = split(q, ' ');
	size_t size = words.size();
	DictList ** listDictList = new DictList*[size];
	int listIndex = 0;
	for (auto it = words.begin(); it != words.end(); it++) {
		auto itDict = _dictMap.find(*it);
		if (itDict == _dictMap.end()) {
			delete []listDictList;
			return std::forward_list<FileNode *>();
		} else {
			listDictList[listIndex++] = &(itDict->second);
		}
	}
	// Sort listDictList by size
	sortListDictListBySize(listDictList, 0, size - 1);

	// Find Intersection
	std::forward_list<int> resultList = *listDictList[0]->list();
	std::forward_list<int> * nextCompareList;
	for (size_t i = 1; i < size; i++) {
		nextCompareList = listDictList[i]->list();
		resultList = findDupplicateItems(&resultList, nextCompareList);
	}
	std::forward_list<FileNode *> result;
	for (auto it = resultList.begin(); it != resultList.end(); it++) {
		result.push_front(_docMap[*it]);
	}
	delete []listDictList;
	return result;
}

std::vector<std::string> Dict::split(const std::string & phrase, char delimiter) {
	std::vector<std::string> list;
	char buf[128]; // 128 characters
	size_t phraseIndex = 0;
	size_t bufIndex = 0;
	size_t length = phrase.size();
	while (phraseIndex < length) {
		if (phrase[phraseIndex] == delimiter) {
			phraseIndex++;
			if (bufIndex != 0) {
				buf[bufIndex] = 0;
				bufIndex = 0;
				list.push_back(buf);
			}
			
		} else {
			buf[bufIndex++] = phrase[phraseIndex++];;
		}
	}
	// push last buf
	if (bufIndex != 0) {
		buf[bufIndex] = 0;
		bufIndex = 0;
		list.push_back(buf);
	}

	return list;
}

void Dict::sortListDictListBySize(DictList ** listDictList, int left, int right) { // Quick sort
	int i = left, j = right;
	size_t pivot = listDictList[(left + right) / 2]->size();
	do {
		while (listDictList[i]->size() < pivot && i < right) i++;
		while (listDictList[j]->size() > pivot && j > left) j--;
		if (i <= j) {
			DictList * tmp = listDictList[i];
			listDictList[i] = listDictList[j];
			listDictList[j] = tmp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) sortListDictListBySize(listDictList, left, j);
	if (i < right) sortListDictListBySize(listDictList, i, right);
}

std::forward_list<int> Dict::findDupplicateItems(std::forward_list<int> * list1, std::forward_list<int> * list2) {
	std::forward_list<int> result;
	auto it1 = list1->begin();
	auto it2 = list2->begin();
	while (it1 != list1->end() && it2 != list2->end()) {
		if (*it1 == *it2) {
			result.push_front(*it1);
			it1++;
			it2++;
		} else if (*it1 > *it2) {
			it1++;
		} else {
			it2++;
		}
	}
	result.reverse();
	return result;
}

