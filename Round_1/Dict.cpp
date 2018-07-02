#include "Dict.h"

Dict::Dict() {}

Dict::~Dict() {}

void Dict::addDocument(TextFile & textFile) {
	int id = _docMap.size();
	_docMap[id] = *textFile.getFileNode();
	std::string word;
	while (textFile.readNextWord(word)) {
		_docIdListMap[word].add(id);
	}
}

std::forward_list<FileNode> Dict::query(const std::string q) {
	std::vector<std::string> words = split(q, ' ');
	size_t size = words.size();
	DocIdList ** listDictList = new DocIdList*[size];
	int listIndex = 0;
	for (auto it = words.begin(); it != words.end(); it++) {
		auto itDict = _docIdListMap.find(*it);
		if (itDict == _docIdListMap.end()) {
			delete []listDictList;
			return std::forward_list<FileNode>();
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
	std::forward_list<FileNode> result;
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

void Dict::sortListDictListBySize(DocIdList ** listDictList, int left, int right) { // Quick sort
	int i = left, j = right;
	size_t pivot = listDictList[(left + right) / 2]->size();
	do {
		while (listDictList[i]->size() < pivot && i < right) i++;
		while (listDictList[j]->size() > pivot && j > left) j--;
		if (i <= j) {
			DocIdList * tmp = listDictList[i];
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

bool Dict::saveToFile(const std::string & path) {
	FILE * file;
	file = fopen(path.c_str(), "wb");
	if (!file) {
		std::cout << "Cannot open " << path << '\n';
		return false;
	}
	// Write DocId list map
	writeDocIdListMap(file, _docIdListMap);
	// Write Doc map
	writeDocMap(file, _docMap);

	fclose(file);
	return true;
}

bool Dict::readFromFile(const std::string & path) {
	FILE * file;
	file = fopen(path.c_str(), "rb");
	if (!file) {
		return false;
	}
	// Read DocId list map
	readDocIdListMap(file, _docIdListMap);
	// Read Doc map
	readDocMap(file, _docMap);

	fclose(file);
	return true;
}

void Dict::writeDocIdListMap(FILE * file, std::map<std::string, DocIdList>& docIdListMap) {
	/* Size of Dict map */
	int size = docIdListMap.size();
	fwrite(&size, sizeof(int), 1, file);
	for (auto it = docIdListMap.begin(); it != docIdListMap.end(); it++) {
		writeString(file, it->first);
		it->second.saveToFile(file); // Write Doc'id list to file
	}
}

void Dict::writeDocMap(FILE * file, std::map<int, FileNode> & docMap) {
	int size = docMap.size();
	/* Doc map size */
	fwrite(&size, sizeof(int), 1, file);
	int key;
	for (auto it = docMap.begin(); it != docMap.end(); it++) {
		key = it->first;
		fwrite(&key, sizeof(int), 1, file);
		it->second.saveToFile(file);
	}
}

void Dict::writeString(FILE * file, const std::string & str) {
	int size = str.size();
	/* String size */
	fwrite(&size, sizeof(int), 1, file);
	/* String content */
	if (size > 0) {
		fwrite(str.c_str(), size * sizeof(char), 1, file);
	}
}

void Dict::readDocIdListMap(FILE * file, std::map<std::string, DocIdList> & docIdListMap) {
	int size;
	std::string key;
	// Read size of doc id list map
	fread(&size, sizeof(int), 1, file);
	for (int i = 0; i < size; i++) {
		readString(file, key); // Read key
		docIdListMap[key].readFromFile(file);
	}
}

void Dict::readDocMap(FILE * file, std::map<int, FileNode> & docMap) {
	int size;
	fread(&size, sizeof(int), 1, file);
	int key;
	for (int i = 0; i < size; i++) {
		fread(&key, sizeof(int), 1, file);
		docMap[key].readFromFile(file);
	}
}

void Dict::readString(FILE * file, std::string & str) {
	int size;
	fread(&size, sizeof(int), 1, file);
	if (size > 0) {
		char * tmp = new char[size + 1];
		fread(tmp, sizeof(char), size, file);
		tmp[size] = 0;
		str = tmp;
		delete[] tmp;
	} else {
		str = "";
	}
}
