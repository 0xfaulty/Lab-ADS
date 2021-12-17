#pragma once
#include <iostream>
using namespace std;

class UniversumSet {
private:
	bool* universum;
	string alphabet;

public:
	UniversumSet(const UniversumSet& prototype);
	UniversumSet(string buffer, string alphabet);
	bool contains(char element) const;
	void print(char tag) const;
	UniversumSet operator&(const UniversumSet& other) const;
	UniversumSet operator|(const UniversumSet& other) const;
	UniversumSet operator~() const;
};