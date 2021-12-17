#include "UniversumSet.h"

UniversumSet::UniversumSet(const UniversumSet& prototype) {
	this->alphabet = prototype.alphabet;
	this->universum = new bool[prototype.alphabet.length()];
	copy(prototype.universum, prototype.universum + prototype.alphabet.length(), universum);
}

UniversumSet::UniversumSet(string buffer, string alphabet) {
	this->alphabet = alphabet;
	this->universum = new bool[alphabet.length()]{};
	for (int i = 0; i < alphabet.length(); ++i) {
		universum[i] = false;
		for (int j = 0; j < buffer.length(); ++j) {
			if (alphabet[i] == buffer[j]) {
				universum[i] = true;
				break;
			}
		}
	}
}

bool UniversumSet::contains(char element) const {
	return universum[alphabet[0] - element];
}

void UniversumSet::print(char tag) const {
	cout << "Универсум " << tag << ":";
	for (int i = 0; i < alphabet.length(); ++i) {
		cout << " " << universum[i];
	}
	cout << endl;
}

UniversumSet UniversumSet::operator&(const UniversumSet& other) const {
	UniversumSet result(*this);
	for (int i = 0; i < alphabet.length(); ++i) {
		result.universum[i] = universum[i] && other.universum[i];
	}
	return result;
}

UniversumSet UniversumSet::operator|(const UniversumSet& other) const {
	UniversumSet result(*this);
	for (int i = 0; i < alphabet.length(); ++i) {
		result.universum[i] = universum[i] || other.universum[i];
	}
	return result;
}

UniversumSet UniversumSet::operator~() const {
	UniversumSet result(*this);
	for (int i = 0; i < alphabet.length(); ++i) {
		result.universum[i] = !universum[i];
	}
	return result;
}