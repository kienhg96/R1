CPP = g++
CFLAGS = -O3 -std=c++11 -Wno-unused-result
CPP_FILES = Round_1/Dict.cpp Round_1/DocIdList.cpp Round_1/FileNode.cpp Round_1/Main.cpp Round_1/ParseParams.cpp Round_1/ReadDirectory.cpp Round_1/StringUtils.cpp Round_1/TextFile.cpp Round_1/TimeMeter.cpp

all: coccoc

coccoc:
	$(CPP) $(CFLAGS) -o $@ $(CPP_FILES)
clean:
	rm coccoc

