#pragma once
#include <iostream>
using namespace std;

class WordSet {
private:
	long long word;
	string alphabet;

public:
	WordSet(const WordSet& prototype);
	WordSet(string buffer, string alphabet);
	bool contains(char element) const;
	void print(char tag) const;
	WordSet operator&(const WordSet& other) const;
	WordSet operator|(const WordSet& other) const;
	WordSet operator~() const;
};