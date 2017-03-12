#include "HashTableUI.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <time.h>

void HashTableUI::readFromFile(HashTable<string>& words) {
	ifstream file("files\\bigDictionary.txt");
	string word;
	while (getline(file, word)) {
		words.insert(word);
	}
	file.close();
}

void HashTableUI::writeToFile(HashTable<string>& matchWords, string& filename) {
	ofstream file(filename);
	for (int i = 0; i < matchWords.getCapacity(); i++) {
		if (matchWords.get(i) == "")
			continue;
		if (matchWords.isActive(i))
			file << matchWords.get(i) << endl;
	}
	file.close();
}

// char hashing
int hashForChar(char e) {
	return e - '0';
}

// string hashing
int hashForString(std::string e) {
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	for (std::size_t i = 0; i < e.length(); i++) {
		hash = hash * a + e[i];
		a = a * b;
	}
	return hash;
}

void HashTableUI::run() {
	cout << "\nprocessing file\n";
	HashTable<string> words{ hashForString };
	clock_t t1Start = clock();
	readFromFile(words);
	printf("\t Time taken: %.2fs\n", (double)(clock() - t1Start) / CLOCKS_PER_SEC);

	string givenWord;
	cout << "give the word: ";
	getline(cin, givenWord);

	HashTable<char> givenWordLetters{ hashForChar };
	clock_t t2Start = clock();
	for (char& c : givenWord) {
		givenWordLetters.insert(c);
	}
	printf("\t Time taken: %.2fs\n", (double)(clock() - t2Start) / CLOCKS_PER_SEC);

	cout << "processing match words\n";

	HashTable<string> matchWords{ hashForString };
	clock_t t3Start = clock();
	for (int i = 0; i < words.getCapacity(); i++) {
		if (words.get(i) == "")
			continue;
		bool flag = true;
		for (char& c : words.get(i)) {
			if (givenWordLetters.contains(c) == 0) {
				flag = false;
			}
		}
		if (flag == true) {
			matchWords.insert(words.get(i));
		}
	}
	printf("\t Time taken: %.2fs\n", (double)(clock() - t3Start) / CLOCKS_PER_SEC);

	string filename;
	cout << "give the filename to write the matches to: ";
	getline(cin, filename);
	clock_t t4Start = clock();
	writeToFile(matchWords, filename);
	printf("\t Time taken: %.2fs\n", (double)(clock() - t4Start) / CLOCKS_PER_SEC);
	cout << "file written - open it to see the matches\n";
}
