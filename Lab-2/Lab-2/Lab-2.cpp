#include <Windows.h>
#include <conio.h>

#include <iostream>
#include <thread>

#include "ArraySet.h";
#include "ListSet.h"
#include "UniversumSet.h"
#include "WordSet.h"
using namespace std;

const string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя";

string aS, bS, cS, dS;

int testIterationsCount;

ArraySet* aArraySet, * bArraySet, * cArraySet, * dArraySet;
ListSet* aListSet, * bListSet, * cListSet, * dListSet;
UniversumSet* aUniversumSet, * bUniversumSet, * cUniversumSet, * dUniversumSet;
WordSet* aWordSet, * bWordSet, * cWordSet, * dWordSet;

bool isAlphabetLetter(char character) {
	return alphabet.find(character) != -1;
}

bool containsInArray(char element, char* array, int size) {
	for (int i = 0; i < size; ++i) {
		if (element == array[i]) {
			return true;
		}
	}
	return false;
}

string generateBuffer(char tag, int seed) {
	cout << "Введите размер множества " << tag << ": ";
	int size;
	while (true) {
		cin >> size;
		if (size < 0 || size > alphabet.length()) {
			cout << "Введите корректный размер: ";
		}
		else {
			break;
		}
	}

	srand(seed);
	string result = "";
	for (int i = 0; i < size; ++i) {
		int index;
		do {
			index = rand() % alphabet.length();
		} while (result.find(alphabet[index]) != -1);
		result.push_back(alphabet[index]);
	}

	return result;
}

void filterString(string& str) {
	int nullCount = 0;
	for (int i = 0; i < str.length(); i++) {
		if (isAlphabetLetter(str[i])) {
			for (int j = i + 1; j < str.length(); j++) {
				if (str[i] == str[j]) {
					str[j] = '0';
					++nullCount;
				}
			}
		}
		else {
			str[i] = '0';
			++nullCount;
		}
	}

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '0') {
			for (int j = i + 1; j < str.length(); j++) {
				if (str[j] != '0') {
					str[i] = str[j];
					str[j] = '0';
					break;
				}
			}
		}
	}
	str.resize(str.length() - nullCount);
}

string inputBuffer(char tag) {
	string buffer = "";
	cout << "Введите множество " << tag << ": ";
	cin >> buffer;
	filterString(buffer);
	return buffer;
}

void initializeSets() {
	aArraySet = new ArraySet(aS, alphabet);
	bArraySet = new ArraySet(bS, alphabet);
	cArraySet = new ArraySet(cS, alphabet);
	dArraySet = new ArraySet(dS, alphabet);

	aListSet = new ListSet(aS, alphabet);
	bListSet = new ListSet(bS, alphabet);
	cListSet = new ListSet(cS, alphabet);
	dListSet = new ListSet(dS, alphabet);

	aUniversumSet = new UniversumSet(aS, alphabet);
	bUniversumSet = new UniversumSet(bS, alphabet);
	cUniversumSet = new UniversumSet(cS, alphabet);
	dUniversumSet = new UniversumSet(dS, alphabet);

	aWordSet = new WordSet(aS, alphabet);
	bWordSet = new WordSet(bS, alphabet);
	cWordSet = new WordSet(cS, alphabet);
	dWordSet = new WordSet(dS, alphabet);

	cout << endl;
}

void printSets() {
	aArraySet->print('A');
	bArraySet->print('B');
	cArraySet->print('C');
	dArraySet->print('D');
	ArraySet eArraySet = ((*aArraySet | *bArraySet) & ~*cArraySet) | *dArraySet;
	eArraySet.print('E');
	cout << endl;

	aListSet->print('A');
	bListSet->print('B');
	cListSet->print('C');
	dListSet->print('D');
	ListSet eListSet = ((*aListSet | *bListSet) & ~*cListSet) | *dListSet;
	eListSet.print('E');
	cout << endl;

	aUniversumSet->print('A');
	bUniversumSet->print('B');
	cUniversumSet->print('C');
	dUniversumSet->print('D');
	UniversumSet eUniversumSet = ((*aUniversumSet | *bUniversumSet) & ~*cUniversumSet) | *dUniversumSet;
	eUniversumSet.print('E');
	cout << endl;

	aWordSet->print('A');
	bWordSet->print('B');
	cWordSet->print('C');
	dWordSet->print('D');
	WordSet eWordSet = ((*aWordSet | *bWordSet) & ~*cWordSet) | *dWordSet;
	eWordSet.print('E');
	cout << endl;
}

void timeTestArrays() {
	time_t start, end;
	start = clock();
	for (int i = 0; i < testIterationsCount; ++i) {
		((*aArraySet | *bArraySet) & ~*cArraySet) | *dArraySet;
	}
	end = clock();
	cout << "Массивы: " << difftime(end, start) / CLOCKS_PER_SEC << " с" << endl;
}

void timeTestLists() {
	time_t start, end;
	start = clock();
	for (int i = 0; i < testIterationsCount; ++i) {
		((*aListSet | *bListSet) & ~*cListSet) | *dListSet;
	}
	end = clock();
	cout << "Списки: " << difftime(end, start) / CLOCKS_PER_SEC << " с" << endl;
}

void timeTestUniversums() {
	time_t start, end;
	start = clock();
	for (int i = 0; i < testIterationsCount; ++i) {
		((*aUniversumSet | *bUniversumSet) & ~*cUniversumSet) | *dUniversumSet;
	}
	end = clock();
	cout << "Универсумы: " << difftime(end, start) / CLOCKS_PER_SEC << " с" << endl;
}

void timeTestWords() {
	time_t start, end;
	start = clock();
	for (int i = 0; i < testIterationsCount; ++i) {
		((*aWordSet | *bWordSet) & ~*cWordSet) | *dWordSet;
	}
	end = clock();
	cout << "Машинные слова: " << difftime(end, start) / CLOCKS_PER_SEC << " с" << endl;
}

void timeTest() {
	thread testThreads[]{ thread(timeTestArrays), thread(timeTestLists),
						 thread(timeTestUniversums), thread(timeTestWords) };
	for (int i = 0; i < 4; ++i) {
		testThreads[i].join();
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char choice;
	cout << "Константы (c), Ввод (i), Генерация (g)? (c/i/g): ";
	cin >> choice;

	if (choice == 'c') {
		aS = "АБВабв";
		bS = "БГДагд";
		cS = "ВДвд";
		dS = "АЭЮЯ";
	}
	else if (choice == 'i') {
		aS = inputBuffer('A');
		bS = inputBuffer('B');
		cS = inputBuffer('C');
		dS = inputBuffer('D');
	}
	else {
		int seed = (int)time(0);
		aS = generateBuffer('A', seed);
		bS = generateBuffer('B', seed + 1);
		cS = generateBuffer('C', seed + 2);
		dS = generateBuffer('D', seed + 3);
	}

	initializeSets();
	printSets();

	cout << "Запустить временной тест? (y/n): ";
	cin >> choice;
	if (choice == 'y') {
		cout << "Введите число итераций теста: ";
		cin >> testIterationsCount;
		cout << endl;
		timeTest();
	}

	delete aArraySet, bArraySet, cArraySet, dArraySet;
	delete aListSet, bListSet, cListSet, dListSet;
	delete aUniversumSet, bUniversumSet, cUniversumSet, dUniversumSet;
	delete aWordSet, bWordSet, cWordSet, dWordSet;

	_getch();
}