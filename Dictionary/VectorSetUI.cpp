#include "VectorSetUI.h"
#include <iostream>
#include <fstream>
#include <time.h>

void VectorSetUI::readFromFile(VectorSet<string>& words) {
	ifstream file("files\\bigDictionary.txt");
	string word;
	while (getline(file, word)) {
		words.insert(word);
	}
	file.close();
}

void VectorSetUI::writeToFile(VectorSet<string>& matchWords, string& filename) {
	ofstream file(filename);
	for (int i = 0; i < matchWords.getSize(); i++) {
		if (matchWords.get(i) == "")
			continue;
		file << matchWords.get(i) << endl;
	}
	file.close();
}

void VectorSetUI::run() {
	cout << "\nprocessing file\n";
	VectorSet<string> words{ 10000 };

	clock_t t1Start = clock();
	readFromFile(words);
	printf("\t Time taken: %.2fs\n", (double)(clock() - t1Start) / CLOCKS_PER_SEC);

	string givenWord;
	cout << "give the word: ";
	getline(cin, givenWord);

	VectorSet<char> givenWordLetters;
	clock_t t2Start = clock();
	for (char& c : givenWord) {
		givenWordLetters.insert(c);
	}
	printf("\t Time taken: %.2fs\n", (double)(clock() - t2Start) / CLOCKS_PER_SEC);

	cout << "processing match words\n";

	VectorSet<string> matchWords;
	clock_t t3Start = clock();
	for (int i = 0; i < words.getSize(); i++) {
		if (words.get(i) == "")
			continue;
		bool flag = true;
		for (char& c : words.get(i)) {
			if (!givenWordLetters.contains(c)) {
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
