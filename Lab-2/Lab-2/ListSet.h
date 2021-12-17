#pragma once
#include <iostream>
using namespace std;

struct Node {
	char data;
	Node* next;

	Node(char data) {
		this->next = nullptr;
		this->data = data;
	}
};

class ListSet {
private:
	int size;
	Node* head;
	string alphabet;

	void sortArray(char* buffer, int bufferSize) const;
	void pushBack(char newElement);

public:
	ListSet(const ListSet& prototype);
	ListSet(string buffer, string alphabet);
	bool contains(char element) const;
	void print(char tag) const;
	void clear();
	ListSet operator&(const ListSet& other) const;
	ListSet operator|(const ListSet& other) const;
	ListSet operator~() const;
};