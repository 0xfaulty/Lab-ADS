#include "ListSet.h"

void ListSet::sortArray(char* array, int arraySize) const {
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

void ListSet::pushBack(char newElement) {
	Node* newNode = new Node(newElement);
	if (!head) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}
}

ListSet::ListSet(const ListSet& prototype) {
	this->size = prototype.size;
	this->alphabet = prototype.alphabet;
	this->head = nullptr;
	if (prototype.head) {
		this->head = new Node(prototype.head->data);
		Node* currentPrototypeNode = prototype.head->next;
		Node* currentThisNode = head;
		while (currentPrototypeNode) {
			currentThisNode->next = new Node(currentPrototypeNode->data);
			currentThisNode = currentThisNode->next;
			currentPrototypeNode = currentPrototypeNode->next;
		}
	}
}

ListSet::ListSet(string buffer, string alphabet) {
	head = nullptr;
	this->size = buffer.length();
	this->alphabet = alphabet;
	char* privateBuffer = new char[size];
	for (int i = 0; i < size; ++i)
		privateBuffer[i] = buffer[i];
	privateBuffer[size] = '\0';
	sortArray(privateBuffer, size);
	if (size > 0) {
		head = new Node(privateBuffer[0]);
		Node* current = head;
		for (int i = 1; i < size; ++i) {
			current->next = new Node(privateBuffer[i]);
			current = current->next;
		}
	}
}

bool ListSet::contains(char element) const {
	Node* current = head;
	while (current) {
		if (element == current->data) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void ListSet::print(char tag) const {
	cout << "Список " << tag << ":";
	Node* current = head;
	while (current) {
		cout << " " << current->data;
		current = current->next;
	}
	cout << endl;
}

void ListSet::clear() {
	size = 0;
	Node* current = head;
	while (head) {
		current = current->next;
		delete head;
		head = current;
	}
}

ListSet ListSet::operator&(const ListSet& other) const {
	ListSet result(*this);
	result.clear();

	char* buffer = new char[min(size, other.size)];
	int counter = 0;

	Node* currentThisNode = head;
	while (currentThisNode) {
		if (other.contains(currentThisNode->data)) {
			buffer[counter++] = currentThisNode->data;
		}
		currentThisNode = currentThisNode->next;
	}

	sortArray(buffer, counter);
	result.size = counter;

	if (counter > 0) {
		result.head = new Node(buffer[0]);
		Node* current = result.head;
		for (int i = 1; i < result.size; ++i) {
			current->next = new Node(buffer[i]);
			current = current->next;
		}
	}

	delete[] buffer;
	return result;
}

ListSet ListSet::operator|(const ListSet& other) const {
	ListSet result(*this);
	result.clear();

	char* buffer = new char[size + other.size];
	int counter = 0;

	Node* currentThisNode = head;
	while (currentThisNode) {
		buffer[counter++] = currentThisNode->data;
		currentThisNode = currentThisNode->next;
	}

	currentThisNode = other.head;
	while (currentThisNode) {
		if (!contains(currentThisNode->data)) {
			buffer[counter++] = currentThisNode->data;
		}
		currentThisNode = currentThisNode->next;
	}

	sortArray(buffer, counter);
	result.size = counter;

	if (counter > 0) {
		result.head = new Node(buffer[0]);
		Node* current = result.head;
		for (int i = 1; i < result.size; ++i) {
			current->next = new Node(buffer[i]);
			current = current->next;
		}
	}

	delete[] buffer;
	return result;
}

ListSet ListSet::operator~() const {
	char* buffer = new char[alphabet.length() - size];
	int counter = 0;
	for (int i = 0; i < alphabet.length(); ++i) {
		if (!contains(alphabet[i])) {
			buffer[counter++] = alphabet[i];
		}
	}
	return *new ListSet(buffer, alphabet);
}