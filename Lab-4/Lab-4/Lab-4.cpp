#include <Windows.h>

#include <iostream>

#include "Graph.h"
using namespace std;

const string CREATE_COMMAND = "create";
const string CONST1_COMMAND = "const1";
const string CONST2_COMMAND = "const2";
const string CLEAR_COMMAND = "clear";
const string COMPUTE_COMMAND = "compute";
const string ADD_COMMAND = "add";
const string REMOVE_COMMAND = "remove";
const string SHOW_COMMAND = "show";
const string EXIT_COMMAND = "exit";

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	string command;
	Graph* graph = nullptr;

	while (true) {
		cin >> command;
		if (command == CREATE_COMMAND) {
			cout << "Введите число вершин графа: ";

			int vertexCount;
			cin >> vertexCount;

			if (graph) {
				delete graph;
			}
			graph = Graph::create(vertexCount);

		}
		else if (command == CONST1_COMMAND) {
			if (graph) {
				delete graph;
			}
			graph = Graph::create(10);
			graph->addEdge(2, 3);
			graph->addEdge(3, 4);
			graph->addEdge(4, 2);
			graph->addEdge(3, 8);
			graph->addEdge(8, 7);
			graph->addEdge(7, 8);
			graph->addEdge(9, 7);
			graph->addEdge(6, 5);
			cout << "Граф создан\n";
		}
		else if (command == CONST2_COMMAND) {
			if (graph) {
				delete graph;
			}
			graph = Graph::create(8);
			graph->addEdge(0, 1);
			graph->addEdge(1, 4);
			graph->addEdge(4, 0);
			graph->addEdge(1, 5);
			graph->addEdge(4, 5);
			graph->addEdge(5, 6);
			graph->addEdge(6, 5);
			graph->addEdge(2, 6);
			graph->addEdge(7, 6);
			graph->addEdge(3, 7);
			graph->addEdge(7, 3);
			graph->addEdge(3, 2);
			graph->addEdge(2, 3);
			graph->addEdge(1, 2);
			cout << "Граф создан\n";
		}
		else if (command == CLEAR_COMMAND) {
			if (graph) {
				graph->clear();
			}
		}
		else if (command == COMPUTE_COMMAND) {
			if (graph) {
				graph->compute();
			}
		}
		else if (command == ADD_COMMAND) {
			if (graph) {
				cout << "Введите через пробел первую и вторую вершины: ";

				int firstVertex, lastVertex;
				cin >> firstVertex >> lastVertex;

				graph->addEdge(firstVertex, lastVertex);
			}
		}
		else if (command == REMOVE_COMMAND) {
			if (graph) {
				cout << "Введите через пробел первую и вторую вершины: ";

				int firstVertex, lastVertex;
				cin >> firstVertex >> lastVertex;

				graph->removeEdge(firstVertex, lastVertex);
			}
		}
		else if (command == SHOW_COMMAND) {
			if (graph) {
				graph->show();
			}
		}
		else if (command == EXIT_COMMAND) {
			break;
		}
	}

	if (graph) {
		delete graph;
	}
}