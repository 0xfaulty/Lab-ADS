#include "WordSet.h"

WordSet::WordSet(const WordSet& prototype) {
	this->alphabet = prototype.alphabet;
	this->word = prototype.word;
}

WordSet::WordSet(string buffer, string alphabet) {
	this->alphabet = alphabet;
	this->word = 0;
	for (int i = 0; i < buffer.length(); ++i) {
		int index = alphabet.find(buffer[i]);
		word |= ((long long)1 << index);
	}
}

bool WordSet::contains(char element) const {
	return (word >> (alphabet.find(element))) & (long long)1;
}

void WordSet::print(char tag) const {
	cout << "Машинное слово " << tag << ":";
	for (int i = 0; i < alphabet.length(); ++i) {
		cout << " " << ((word >> i) & (long long)1);
	}
	cout << endl;
}

WordSet WordSet::operator&(const WordSet& other) const {
	WordSet result(*this);
	result.word = word & other.word;
	return result;
}

WordSet WordSet::operator|(const WordSet& other) const {
	WordSet result(*this);
	result.word = word | other.word;
	return result;
}

WordSet WordSet::operator~() const {
	WordSet result(*this);
	result.word = ~word;
	return result;
}