#include "HashTable.h"
#include "VectorSet.h"
#include <string>
#include <assert.h>

int hash(std::string e) {
	// we consider TElement == string
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	for (std::size_t i = 0; i < e.length(); i++) {
		hash = hash * a + e[i];
		a = a * b;
	}
	return (hash % 101);
}

int tests() {
	std::string s1 = "bull"; std::string s2 = "gull"; std::string s3 = "swan";

	// testing Vector Implementation
	VectorSet<std::string> MyVectorSet = VectorSet<std::string>{};
	IteratorVectorSet<std::string> MyVectorSetIterator = IteratorVectorSet<std::string>{ MyVectorSet };
	assert(MyVectorSet.isEmpty());
	MyVectorSet.insert(s1);
	assert(MyVectorSet.contains(s1));
	assert(MyVectorSet.contains(s2) == 0);
	MyVectorSet.insert(s2);
	assert(MyVectorSetIterator.isValid(0));
	assert(MyVectorSetIterator.isValid(1));
	assert(MyVectorSetIterator.isValid(2) == 1);
	MyVectorSet.insert(s3);
	assert(MyVectorSet.getSize() == 3);
	assert(MyVectorSet.get(0) == "bull");
	assert(MyVectorSet.get(1) == "gull");
	assert(MyVectorSet.get(2) == "swan");
	MyVectorSet.erase(0);
	assert(MyVectorSet.getSize() == 2);
	assert(MyVectorSet.get(0) == "gull");
	assert(MyVectorSet.get(1) == "swan");
	MyVectorSet.remove(s2);
	assert(MyVectorSet.getSize() == 1);
	assert(MyVectorSet.get(0) == "swan");

	// testing Hash Table Implementation
	HashTable<std::string> MyHashTableSet = HashTable<std::string>{ hash };
	IteratorHashTable<std::string> MyHashTableSetIterator = IteratorHashTable<std::string>{ MyHashTableSet };
	assert(MyHashTableSet.isEmpty());
	MyHashTableSet.insert(s1);
	assert(MyHashTableSet.contains(s1));
	assert(MyHashTableSet.contains(s2) == 0);
	MyHashTableSet.insert(s2);
	MyHashTableSet.insert(s3);
	assert(MyHashTableSet.getSize() == 3);
	assert(MyHashTableSetIterator.isValid(24));
	assert(MyHashTableSetIterator.isValid(96));
	assert(MyHashTableSetIterator.isValid(103) == 0);
	assert(MyHashTableSet.get(96) == "bull");
	assert(MyHashTableSet.get(24) == "swan");
	assert(MyHashTableSet.get(27) == "gull");
	assert(MyHashTableSet.contains(s2));
	assert(MyHashTableSet.contains(s3));
	MyHashTableSet.erase(0);
	assert(MyHashTableSet.getSize() == 2);
	MyHashTableSet.remove(s2);
	assert(MyHashTableSet.getSize() == 1);

	return 0;
}
