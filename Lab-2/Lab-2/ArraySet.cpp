#include "ArraySet.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void ArraySet::sortArray(char* array, int arraySize) const {
	for (int i = 0; i < arraySize - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < arraySize; ++j) {
			if (array[j] < array[minIndex]) {
				minIndex = j;
			}
		}
		if (i != minIndex) {
			char temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}

ArraySet::ArraySet(const ArraySet& prototype) {
	this->size = prototype.size;
	this->alphabet = prototype.alphabet;
	this->set = new char[size];
	for (int i = 0; i < size; ++i)
		set[i] = prototype.set[i];
	set[size] = '\0';
}

ArraySet::ArraySet(string buffer, string alphabet) {
	this->size = buffer.length();
	this->alphabet = alphabet;
	this->set = new char[size];
	for (int i = 0; i < size; ++i)
		set[i] = buffer[i];
	set[size] = '\0';
	sortArray(set, size);
}

bool ArraySet::contains(char element) const {
	for (int i = 0; i < size; ++i) {
		if (element == set[i]) {
			return true;
		}
	}
	return false;
}

void ArraySet::print(char tag) const {
	cout << "Массив " << tag << ":";
	for (int i = 0; i < size; ++i) {
		cout << " " << set[i];
	}
	cout << endl;
}

void ArraySet::clear() {
	size = 0;
	delete set;
}

ArraySet ArraySet::operator&(const ArraySet& other) const {
	char* buffer = new char[min(size, other.size)];
	int counter = 0;
	for (int i = 0; i < size; ++i) {
		if (other.contains(set[i])) {
			buffer[counter++] = set[i];
		}
	}
	buffer[counter] = '\0';
	sortArray(buffer, counter);
	ArraySet result = ArraySet(buffer, alphabet);
	return result;
}

ArraySet ArraySet::operator|(const ArraySet& other) const {
	char* buffer = new char[size + other.size];
	int counter = 0;
	for (int i = 0; i < size; ++i) {
		buffer[counter++] = set[i];
	}
	for (int i = 0; i < other.size; ++i) {
		if (!contains(other.set[i])) {
			buffer[counter++] = other.set[i];
		}
	}
	buffer[counter] = '\0';
	sortArray(buffer, counter);
	ArraySet result = ArraySet(buffer, alphabet);
	return result;
}

ArraySet ArraySet::operator~() const {
	char* buffer = new char[alphabet.length() - size];
	int counter = 0;
	for (int i = 0; i < alphabet.length(); ++i) {
		if (!contains(alphabet[i])) {
			buffer[counter++] = alphabet[i];
		}
	}
	buffer[counter] = '\0';
	ArraySet result = ArraySet(buffer, alphabet);
	return result;
}