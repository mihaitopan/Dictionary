#pragma once
#include "HashTable.h"
#include <string>
using namespace std;

class HashTableUI {
private:
	void readFromFile(HashTable<string>& words); // reads from the file the words in the dictionary
	void writeToFile(HashTable<string>& matchWords, string& filename); // writes to the given file the matches
public:
	HashTableUI() {}
	~HashTableUI() {}
	void run();
};
