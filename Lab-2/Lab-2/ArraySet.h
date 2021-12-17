#pragma once
#include <iostream>
using namespace std;

class ArraySet {
private:
	int size;
	char* set;
	string alphabet;

	void sortArray(char* array, int arraySize) const;

public:
	ArraySet(const ArraySet& prototype);
	ArraySet(string buffer, string alphabet);
	bool contains(char element) const;
	void print(char tag) const;
	void clear();
	ArraySet operator|(const ArraySet& other) const;
	ArraySet operator&(const ArraySet& other) const;
	ArraySet operator~() const;
};