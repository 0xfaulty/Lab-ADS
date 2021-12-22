#include <time.h>
#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
using namespace std;

string alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя";

string aS, bS, cS, dS, eS;
list<char>* aL, * bL, * cL, * dL, * eL;
int* aU, * bU, * cU, * dU, * eU;
long long aW, bW, cW, dW, eW;

bool isAlphabetLetter(char character) {                                                      //Проверка алфавита
	return (character >= 'А' && character <= 'Я') || (character >= 'а' && character <= 'я');
}

list<char>* stringToList(const string& str) {                                                //Добавление к списку
	list<char>* result = new list<char>();
	for (char c : str) {
		result->push_back(c);
	}
	return result;
}

int* stringToUniversum(const string& str) {
	int* result = new int[alphabet.length()];
	for (int i = 0; i < alphabet.length(); ++i) {
		result[i] = 0;
		for (int j = 0; j < str.length(); ++j) {
			if (alphabet[i] == str[j]) {
				result[i] = 1;
				break;
			}
		}
	}
	return result;
}

long long stringToWord(const string& str) {                                                    //Побитовый массив
	long long result = 0;
	for (int i = 0; i < str.length(); ++i) {
		for (int j = 0; j < alphabet.length(); ++j) {
			if (str[i] == alphabet[j]) {
				result |= ((long long)1 << j);
				break;
			}
		}
	}
	return result;
}

void sortString(string& str) {
	int minIndex;
	for (int i = 0; i < str.length(); ++i) {
		minIndex = i;
		for (int j = i + 1; j < str.length(); ++j) {
			if (str[j] < str[minIndex]) {
				minIndex = j;
			}
		}
		if (i != minIndex) {
			char temp = str[i];
			str[i] = str[minIndex];
			str[minIndex] = temp;
		}
	}
}

void sortStrings() {
	sortString(aS);
	sortString(bS);
	sortString(cS);
	sortString(dS);
}

void filterString(string& str) {
	int nullCount = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (isAlphabetLetter(str[i])) {
			for (int j = i + 1; j < str.length(); ++j) {
				if (str[i] == str[j]) {
					str[j] = '0';
				}
			}
		}
		else {
			str[i] = '0';
			++nullCount;
		}
	}

	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '0') {
			for (int j = i + 1; j < str.length(); ++j) {
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

void constantStrings() {
	int seed = time(0);
	aS = "АБВабв";
	bS = "АГДагд";
	cS = "ВвДв";
	dS = "АЭЮЯ";
}

void inputStrings() {
	cout << "Введите множество A: ";
	cin >> aS;
	cout << "Введите множество B: ";
	cin >> bS;
	cout << "Введите множество C: ";
	cin >> cS;
	cout << "Введите множество D: ";
	cin >> dS;
	cout << endl;
}

string generateString(int seed) {
	string result = "";
	srand(seed);
	int length = rand() % alphabet.length();
	for (int i = 0; i < length; ++i) {
		int index;
		do {
			index = rand() % alphabet.length();
		} while (result.find(alphabet[index]) != -1);
		result.push_back(alphabet[index]);
	}
	return result;
}

void generateStrings() {
	int seed = time(0);
	aS = generateString(seed);
	bS = generateString(seed + 1);
	cS = generateString(seed + 2);
	dS = generateString(seed + 3);
}

void prepareStrings() {
	filterString(aS);
	filterString(bS);
	filterString(cS);
	filterString(dS);
	sortStrings();
}

void convertStrings() {
	aL = stringToList(aS);
	bL = stringToList(bS);
	cL = stringToList(cS);
	dL = stringToList(dS);
	eL = new list<char>();

	aU = stringToUniversum(aS);
	bU = stringToUniversum(bS);
	cU = stringToUniversum(cS);
	dU = stringToUniversum(dS);

	aW = stringToWord(aS);
	bW = stringToWord(bS);
	cW = stringToWord(cS);
	dW = stringToWord(dS);
}

void outputStrings() {
	cout << "Множество A как массив: " << aS << endl;
	cout << "Множество B как массив: " << bS << endl;
	cout << "Множество C как массив: " << cS << endl;
	cout << "Множество D как массив: " << dS << endl;
	cout << "Множество E как массив: " << eS << endl << endl;
}

void outputList(list<char>* list) {
	for (auto it = list->begin(); it != list->end(); ++it) {
		cout << *it;
	}
	cout << endl;
}

void outputLists() {
	cout << "Множество A как список: ";
	outputList(aL);
	cout << "Множество B как список: ";
	outputList(bL);
	cout << "Множество C как список: ";
	outputList(cL);
	cout << "Множество D как список: ";
	outputList(dL);
	cout << "Множество E как список: ";
	outputList(eL);
	cout << endl;
}

void outputUniversum(int* univerSum) {
	for (int i = 0; i < alphabet.length(); ++i) {
		cout << univerSum[i];
	}
	cout << " (буквы: ";
	for (int i = 0; i < alphabet.length(); ++i) {
		if (univerSum[i] == 1) {
			cout << alphabet[i];
		}
	}
	cout << ")" << endl;
}

void outputUniversums() {
	cout << "Множество A как универсум: ";
	outputUniversum(aU);
	cout << "Множество B как универсум: ";
	outputUniversum(bU);
	cout << "Множество C как универсум: ";
	outputUniversum(cU);
	cout << "Множество D как универсум: ";
	outputUniversum(dU);
	cout << "Множество E как универсум: ";
	outputUniversum(eU);
	cout << endl;
}

void outputWord(long long word) {
	for (int i = 0; i < sizeof(long long) * 8; ++i) {
		cout << ((word >> i) & 1);
	}
	cout << " (буквы: ";
	for (int i = 0; i < alphabet.length(); ++i) {
		if ((word >> i) & 1) {
			cout << alphabet[i];
		}
	}
	cout << ")" << endl;
}

void outputWords() {
	cout << "Множество A как слово: ";
	outputWord(aW);
	cout << "Множество B как слово: ";
	outputWord(bW);
	cout << "Множество C как слово: ";
	outputWord(cW);
	cout << "Множество D как слово: ";
	outputWord(dW);
	cout << "Множество E как слово: ";
	outputWord(eW);
	cout << endl;
}

void calculateStrings() {
	//Добавляем в E всё из D
	for (int i = 0; i < dS.length(); ++i) {
		eS.push_back(dS[i]);
	}
	//Добавляем в E всё из A чего нет в C и ещё нет в E (исключаем повторения)
	for (int i = 0; i < aS.length(); ++i) {
		bool found = false;
		for (int j = 0; j < cS.length(); ++j) {
			if (aS[i] == cS[j]) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		for (int j = 0; j < eS.length(); ++j) {
			if (aS[i] == eS[j]) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		eS.push_back(aS[i]);
	}
	//Добавляем в E всё из B чего нет в C и ещё нет в E (исключаем повторения)
	for (int i = 0; i < bS.length(); ++i) {
		bool found = false;
		for (int j = 0; j < cS.length(); ++j) {
			if (bS[i] == cS[j]) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		for (int j = 0; j < eS.length(); ++j) {
			if (bS[i] == eS[j]) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		eS.push_back(bS[i]);
	}
}

void calculateLists() {
	delete eL;
	eL = new list<char>();

	//Добавляем в E всё из D
	for (auto d : *dL) {
		eL->push_back(d);
	}
	//Добавляем в E всё из A чего нет в C и ещё нет в E (исключаем повторения)
	for (auto a : *aL) {
		bool found = false;
		for (auto c : *cL) {
			if (a == c) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		for (auto e : *eL) {
			if (a == e) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		eL->push_back(a);
	}
	//Добавляем в E всё из B чего нет в C и ещё нет в E (исключаем повторения)
	for (auto b : *bL) {
		bool found = false;
		for (auto c : *cL) {
			if (b == c) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		for (auto e : *eL) {
			if (b == e) {
				found = true;
				break;
			}
		}
		if (found)
			continue;
		eL->push_back(b);
	}
}

void calculateUniversums() {
	eU = new int[alphabet.length()];
	for (int i = 0; i < alphabet.length(); ++i) {
		eU[i] = ((aU[i] || bU[i]) && !cU[i]) || dU[i];
	}
}

void calculateWords() { eW = ((aW | bW) & ~cW) | dW; }

void timeTest() {
	int iterationsCount;
	clock_t start, end;

	cout << "Введите количество итераций: ";
	cin >> iterationsCount;
	cout << "Запуск тестов..." << endl << endl;

	start = clock();
	for (int i = 0; i < iterationsCount; ++i) {
		calculateStrings();
	}
	end = clock();
	cout << "Массив: " << (double)(end - start) / CLOCKS_PER_SEC << " секунд" << endl;

	start = clock();
	for (int i = 0; i < iterationsCount; ++i) {
		calculateLists();
	}
	end = clock();
	cout << "Список: " << (double)(end - start) / CLOCKS_PER_SEC << " секунд" << endl;

	start = clock();
	for (int i = 0; i < iterationsCount; ++i) {
		calculateUniversums();
	}
	end = clock();
	cout << "Универсум: " << (double)(end - start) / CLOCKS_PER_SEC << " секунд" << endl;

	start = clock();
	for (int i = 0; i < iterationsCount; ++i) {
		calculateWords();
	}
	end = clock();
	cout << "Слово: " << (double)(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char choice;
	cout << "Константы (c), Ввод (i), Генерация (g)? (c/i/g): ";
	cin >> choice;

	if (choice == 'c' || choice == 'i' || choice == 'g') {
		if (choice == 'c') {
			constantStrings();
		}
		else if (choice == 'i') {
			inputStrings();
			prepareStrings();
		}
		else {
			generateStrings();
			sortStrings();
		}

		convertStrings();

		calculateStrings();
		calculateLists();
		calculateUniversums();
		calculateWords();

		outputStrings();
		outputLists();
		outputUniversums();
		outputWords();

		cout << "Запустить временной тест? (y/n): ";
		cin >> choice;
		if (choice == 'y') {
			timeTest();
		}
	}
	delete aL, bL, cL, dL, eL;

	system("pause");
	return 0;
}