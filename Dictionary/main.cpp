#include "HashTableUI.h"
#include "STLSetUI.h"
#include "VectorSetUI.h"
#include <iostream>

int main() {
	while (true) {
		cout << "\nOptions:\n";
		cout << "\t dv - dynamic vector\n";
		cout << "\t ht - hash table\n";
		cout << "\t stl - stl set\n";
		cout << "\t q - quit\n";
		std::string command;
		cout << "Enter command: ";
		cin >> command;
		cin.ignore();
		while ((command != "dv") && (command != "ht") && (command != "stl") && (command != "q")) {
			cout << "Invalid option! Choose 'dv', 'ht, 'stl' or 'q'\n";
			cout << "Enter command: ";
			cin >> command;
			cin.ignore();
		}
		if (command == "dv") {
			VectorSetUI SetUI = VectorSetUI{};
			SetUI.run();
		} else if (command == "ht") {
			HashTableUI SetUI = HashTableUI{};
			SetUI.run();
		} else if (command == "stl") {
			STLSetUI SetUI = STLSetUI{};
			SetUI.run();
		} else  {
			break;
		}
	}

	cout << endl;
	system("pause");
	return 0;
}
