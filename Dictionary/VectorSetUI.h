#pragma once
#include "VectorSet.h"
#include <string>
using namespace std;

class VectorSetUI {
private:
	void readFromFile(VectorSet<string>& words); // reads from the file the words in the dictionary
	void writeToFile(VectorSet<string>& matchWords, string& filename); // writes to the given file the matches
public:
	VectorSetUI() {}
	~VectorSetUI() {}
	void run();
};
