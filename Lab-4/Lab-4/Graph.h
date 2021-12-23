#pragma once

#include <Windows.h>

#include <iomanip>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
private:
	int vertexCount_;
	int** edges_;

	Graph() {};
	Graph(int vertexCount);

public:
	~Graph();

	static Graph* create(int vertexCount);

	void clear();
	void show();
	void addEdge(int firstVertex, int lastVertex);
	void removeEdge(int firstVertex, int lastVertex);
	bool checkLink(int vertexFrom, int vertexTo, bool* checkedVertices = nullptr);
	void findComponent(int vertex, bool* checkedVertices);
	void compute();
};