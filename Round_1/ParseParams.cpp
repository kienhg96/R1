#include "ParseParams.h"

ParseParams::ParseParams(int argc, char *argv[]) {
	_argc = argc;
	_argv = argv;
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			parseArgument(&i);
		} else {
			parseFreeArgument(i);
		}
	}
}

ParseParams::~ParseParams() {}

bool ParseParams::hasArgument(const std::string & key) {
	if (_paramMap.find(key) != _paramMap.end()) {
		return true;
	}
	return false;
}

std::string ParseParams::getArgument(const std::string & key) {
	return _paramMap[key];
}

std::string ParseParams::getFreeArg(size_t index, const std::string defaultStr) {
	if (index < _freeParams.size()) {
		return _freeParams.at(index);
	}
	return defaultStr;
}

void ParseParams::parseArgument(int * pIndex) {
	int index = *pIndex;
	std::string arg = _argv[index];
	if (index < (_argc - 1) && _argv[index + 1][0] != '-') {
		_paramMap[arg] = _argv[index + 1];
		(*pIndex)++;
	} else {
		_paramMap[arg] = "";
	}
}

void ParseParams::parseFreeArgument(int index) {
	std::string arg = _argv[index];
	_freeParams.push_back(arg);
}
