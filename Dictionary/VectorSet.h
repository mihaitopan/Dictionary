#pragma once

// VECTORSET
template <typename TElement>
class VectorSet {
private:
	TElement* elems;
	int size;
	int capacity;
	void resize(double factor = 2);
public:
	VectorSet(int capacity = 10); // constructor
	VectorSet(VectorSet& S); // copy constructor
	~VectorSet(); // destructor
	VectorSet& operator=(VectorSet& S); // assignment operator
	TElement& operator[](int pos); // position operator
	bool isEmpty(); // is empty validator
	int getSize(); // size getter
	bool contains(TElement& e); // contains function
	bool insert(TElement& e); // adder
	bool erase(int it); // remover (by iterator)
	bool remove(TElement& e); // remover (by value)
	TElement& get(int it); // element getter (by iterator)
	TElement* getAll(); // elements getter
};

template <typename TElement>
VectorSet<TElement>::VectorSet(int capacity) {
	this->size = 0;
	this->capacity = capacity;
	this->elems = new TElement[capacity];
}

template <typename TElement>
VectorSet<TElement>::VectorSet(VectorSet& v) {
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename TElement>
VectorSet<TElement>::~VectorSet() {
	delete[] this->elems;
}

template <typename TElement>
void VectorSet<TElement>::resize(double factor) {
	this->capacity *= int(factor);
	TElement* aux = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		aux[i] = this->elems[i];
	delete[] this->elems;
	this->elems = aux;
}

template <typename TElement>
VectorSet<TElement>& VectorSet<TElement>::operator=(VectorSet& v) {
	if (this == &v)
		return *this; // assigning a shit to itself - not good :)
	this->size = v.size;
	this->capacity = v.capacity;
	delete[] this->elems;
	this->elems = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
	return *this;
}

template<typename TElement>
TElement& VectorSet<TElement>::operator[](int pos) {
	return this->elems[pos]; // must be a valid position
}

template <typename TElement>
bool VectorSet<TElement>::isEmpty() {
	return (this->size == 0);
}

template <typename TElement>
int VectorSet<TElement>::getSize() {
	return this->size;
}

template <typename TElement>
bool VectorSet<TElement>::contains(TElement& e) {
	int it = 0;
	while (it != this->size) {
		if (e == elems[it])
			return true;
		else
			it++;
	}
	return false;
}

template <typename TElement>
bool VectorSet<TElement>::insert(TElement& e) {
	if (this->size == this->capacity)
		this->resize();
	if (this->contains(e)) {
		return false;
	}
	this->elems[this->size] = e;
	this->size++;
	return true;
}

template <typename TElement>
bool VectorSet<TElement>::erase(int it) {
	for (int i = it; i < this->size - 1; i++) {
		this->elems[i] = this->elems[i + 1];
	}
	this->size--;
	return true;
}

template <typename TElement>
bool VectorSet<TElement>::remove(TElement& e) {
	int it = 0, pos = -1;
	while (it != this->size) {
		if (e == elems[it]) {
			pos = it;
			break;
		}
		it++;
	}
	if (pos == -1) {
		return false;
	}
	for (int i = pos; i < this->size - 1; i++) {
		this->elems[i] = this->elems[i + 1];
	}
	this->size--;
	return true;
}

template <typename TElement>
TElement& VectorSet<TElement>::get(int it) {
	return this->elems[it];
}

template <typename TElement>
TElement* VectorSet<TElement>::getAll() {
	return this->elems;
}


// ITERTOR
template <typename TElement>
class IteratorVectorSet {
private:
	VectorSet<TElement>& mySet;
public:
	IteratorVectorSet(VectorSet<TElement>& s) : mySet{ s } {}; // constructor
	TElement* begin(); // iterator begin()
	TElement* end(); // iterator end()
	bool isValid(int it); // iterator validator
	void next(int it); // iterator increaser
};

template <typename TElement>
TElement* IteratorVectorSet<TElement>::begin() {
	return this->mySet.elems;
}

template <typename TElement>
TElement* IteratorVectorSet<TElement>::end() {
	return this->mySet.elems + this->mySet.size; // iterator end() points after the end of the thing
}

template <typename TElement>
bool IteratorVectorSet<TElement>::isValid(int it) {
	if (this->mySet.getSize() == 0)
		return false;
	if (it >= 0 && it < this->mySet.getSize())
		return true;
	return false;
}

template <typename TElement>
void IteratorVectorSet<TElement>::next(int it) {
	if (it == this->end())
		it = this->begin();
	else
		it += sizeof(TElement);
}
