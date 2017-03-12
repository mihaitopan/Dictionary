#include "STLSetUI.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void STLSetUI::readFromFile(set<string>& words) {
	ifstream file("files\\bigDictionary.txt");
	string word;
	while (getline(file, word)) {
		words.insert(word);
	}
	file.close();
}

void STLSetUI::writeToFile(set<string>& matchWords, string& filename) {
	ofstream file(filename);
	for (auto word : matchWords) {
		file << word << endl;
	}
	file.close();
}

void STLSetUI::run() {
	cout << "\nprocessing file\n";
	set<string> words;
	clock_t t1Start = clock();
	readFromFile(words);
	printf("\t Time taken: %.2fs\n", (double)(clock() - t1Start) / CLOCKS_PER_SEC);

	string givenWord;
	cout << "give the word: ";
	getline(cin, givenWord);

	set<char> givenWordLetters;
	clock_t t2Start = clock();
	for (char& c : givenWord) {
		givenWordLetters.insert(c);
	}
	printf("\t Time taken: %.2fs\n", (double)(clock() - t2Start) / CLOCKS_PER_SEC);

	cout << "processing match words\n";

	set<string> matchWords;
	clock_t t3Start = clock();
	for (auto probeWord : words) {
		bool flag = true;
		for (char& c : probeWord) {
			if (givenWordLetters.find(c) == givenWordLetters.end()) {
				flag = false;
			}
		}
		if (flag == true) {
			matchWords.insert(probeWord);
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
