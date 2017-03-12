#pragma once
#include <string>
#include <cmath>
#include <functional>

// HashTable
template <typename TElement>
class HashTable {
public:
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry {
		TElement element;
		EntryType info;
		HashEntry(TElement e = TElement(), EntryType i = EMPTY) : element(e), info(i) {}
	};
	HashEntry* entries;
	int size, capacity, activeSize;
	int findPosition(TElement& e); // position getter
	std::function<int(TElement)> hashFunction; // hash parent function
	void rehash(double factor = 2);
public:
	int nextPrime(int n);
	HashTable(std::function<int(TElement)> hashFct, int capacity = 101); // constructor
	~HashTable(); // destructor
	bool isEmpty(); // is empty validator
	int getCapacity(); // capacity getter
	int getSize(); // size getter
	int getActualSize(); // size getter (with deleted)
	bool isActive(int it);
	bool contains(TElement& e); // contains function
	bool insert(TElement& e); // adder
	bool erase(int it); // remover (by iterator)
	bool remove(TElement& e); // remover (by value)
	TElement& get(int it); // element getter (by iterator)
};

// nextPrime for quadratic probing
template <typename TElement>
int HashTable<TElement>::nextPrime(int n) {
	int i, j, flag;
	for (i = n + 1; ; i++) {
		flag = 0;
		for (j = 2; j < i / 2; j++) {
			if (i%j == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			return i;
		}
	}
}

template <typename TElement>
HashTable<TElement>::HashTable(std::function<int(TElement)> hashFct, int capacity = 101) : hashFunction{ hashFct } {
	this->capacity = nextPrime(capacity);
	this->size = 0; this->activeSize = 0;
	this->entries = new HashEntry[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->entries[i] = HashEntry{};
	}
}

template <typename TElement>
HashTable<TElement>::~HashTable() {
	delete[] this->entries;
}

template <typename TElement>
void HashTable<TElement>::rehash(double factor = 2) {
	int oldCapacity = this->capacity;
	this->capacity = nextPrime(oldCapacity*2);
	HashEntry* oldEntries = entries;
	this->entries = new HashEntry[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->entries[i] = HashEntry{};
	}
	this->size = 0; this->activeSize = 0;
	for (int i = 0; i < oldCapacity; i++) {
		this->insert(oldEntries[i].element);
	}
	delete[] oldEntries;
}

template <typename TElement>
bool HashTable<TElement>::isActive(int pos) { 
	return this->entries[pos].info == ACTIVE;
}

template <typename TElement>
int HashTable<TElement>::findPosition(TElement& e) {
	int offset = 1, pos = std::abs(this->hashFunction(e)) % this->capacity;
	while (this->entries[pos].info != EMPTY && this->entries[pos].element != e) {
		pos += offset*offset;
		offset++;
		if (pos >= this->capacity) {
			pos -= this->capacity;
		}
	}
	return pos;
}

template <typename TElement>
bool HashTable<TElement>::isEmpty() {
	return (this->activeSize == 0);
}

template <typename TElement>
int HashTable<TElement>::getCapacity() {
	return this->capacity;
}

template <typename TElement>
int HashTable<TElement>::getSize() {
	return this->activeSize;
}

template <typename TElement>
int HashTable<TElement>::getActualSize() {
	return this->size;
}

template <typename TElement>
bool HashTable<TElement>::contains(TElement& e) {
	return isActive(findPosition(e));
}

template <typename TElement>
bool HashTable<TElement>::insert(TElement& e) {
	int pos = this->findPosition(e);
	if (this->isActive(pos)) {
		return false;
	}
	this->entries[pos] = HashEntry(e, ACTIVE);
	this->size++; this->activeSize++;
	if (this->size >= this->capacity / 2)
		this->rehash();
	return true;
}

template <typename TElement>
bool HashTable<TElement>::erase(int pos) {
	this->entries[pos].info = DELETED;
	this->activeSize--;
	return true;
}

template <typename TElement>
bool HashTable<TElement>::remove(TElement& e) {
	int pos = this->findPosition(e);
	if (!this->isActive(pos)) {
		return false;
	}
	this->entries[pos].info = DELETED;
	this->activeSize--;
	return true;
}

template <typename TElement>
TElement& HashTable<TElement>::get(int pos) {
	return this->entries[pos].element;
}


// ITERTOR
template <typename TElement>
class IteratorHashTable {
private:
	HashTable<TElement>& mySet;
public:
	IteratorHashTable(HashTable<TElement>& s) : mySet{ s } {}; // constructor
	TElement* begin(); // iterator begin()
	TElement* end(); // iterator end()
	bool isValid(int it); // iterator validator
	void next(int it); // iterator increaser
};

template <typename TElement>
TElement* IteratorHashTable<TElement>::begin() {
	return this->mySet.entries;
}

template <typename TElement>
TElement* IteratorHashTable<TElement>::end() {
	return this->mySet.entries + this->mySet.getActualSize();
}

template <typename TElement>
bool IteratorHashTable<TElement>::isValid(int it) {
	if (this->mySet.getSize() == 0)
		return false;
	if (it >= 0 && it < this->mySet.getCapacity())
			return true;
	return false;
}

template <typename TElement>
void IteratorHashTable<TElement>::next(int it) {
	if (it == this->end())
		it = this->begin();
	else
		it += sizeof(TElement);
}
