#pragma once
#include <set>
#include <string>
using namespace std;

class STLSetUI {
private:
	void readFromFile(std::set<string>& words); // reads from the file the words in the dictionary
	void writeToFile(std::set<string>& matchWords, string& filename); // writes to the given file the matches
public:
	STLSetUI() {}
	~STLSetUI() {}
	void run();
};
