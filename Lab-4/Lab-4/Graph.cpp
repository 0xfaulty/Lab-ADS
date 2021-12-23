#include "Graph.h"

Graph::Graph(int vertexCount) : vertexCount_(vertexCount) 
{
	edges_ = new int* [vertexCount_];
	for (int i = 0; i < vertexCount_; i++) {
		edges_[i] = new int[vertexCount_] {};
	}
}

Graph::~Graph() 
{
	for (int i = 0; i < vertexCount_; i++) {
		delete[] edges_[i];
	}
	delete[] edges_;
}

Graph* Graph::create(int vertexCount) 
{
	Graph* graph = nullptr;
	if (vertexCount > 0) {
		graph = new Graph(vertexCount);
	}
	return graph;
}

void Graph::clear() 
{
	for (int i = 0; i < vertexCount_; i++) {
		for (int j = 0; j < vertexCount_; j++) {
			edges_[i][j] = 0;
		}
	}
}

void Graph::show() 
{
	int fieldWidth = (int)log10(vertexCount_ - 1) + 2;
	int lineLength = fieldWidth * (vertexCount_ + 1) + 2;

	cout << setw(fieldWidth) << ""
		<< " |";

	for (int i = 0; i < vertexCount_; i++) {
		cout << setw(fieldWidth) << i;
	}
	cout << endl;

	for (int i = 0; i < lineLength; i++) {
		cout << '-';
	}
	cout << endl;

	for (int i = 0; i < vertexCount_; i++) {
		cout << setw(fieldWidth) << i;
		cout << " |";
		for (int j = 0; j < vertexCount_; j++) {
			cout << setw(fieldWidth) << edges_[i][j];
		}
		cout << endl;
	}
}

void Graph::addEdge(int firstVertex, int lastVertex) 
{
	if ((firstVertex != lastVertex) &&
		(firstVertex >= 0 && firstVertex < vertexCount_) &&
		(lastVertex >= 0 && lastVertex < vertexCount_)) {
		edges_[firstVertex][lastVertex] = 1;
	}
}

void Graph::removeEdge(int firstVertex, int lastVertex) 
{
	if ((firstVertex != lastVertex) &&
		(firstVertex >= 0 && firstVertex < vertexCount_) &&
		(lastVertex >= 0 && lastVertex < vertexCount_)) {
		edges_[firstVertex][lastVertex] = 0;
	}
}

bool Graph::checkLink(int vertexFrom, int vertexTo, bool* checkedVertices)
{
	checkedVertices[vertexFrom] = true;

	for (int i = 0; i < vertexCount_; i++)
	{
		if (i == vertexFrom)
		{
			continue;
		}

		if (edges_[vertexFrom][i] == 1)
		{
			if (i == vertexTo)
			{
				return true;
			}

			if (!checkedVertices[i] && checkLink(i, vertexTo, checkedVertices))
			{
				return true;
			}
		}
	}

	return false;
}

void Graph::findComponent(int vertex, bool* checkedVertices)
{
	checkedVertices[vertex] = true;
	cout << vertex << " ";

	for (int i = 0; i < vertexCount_; i++)
	{
		if (i == vertex)
		{
			continue;
		}

		if (edges_[vertex][i] == 1)
		{
			cout << i << " ";
			checkedVertices[i] = true;
		}
	}
}

void Graph::compute() 
{
	Graph tmpGraph = Graph(vertexCount_);

	for (int i = 0; i < vertexCount_; i++)
	{
		for (int j = i + 1; j < vertexCount_; j++)
		{
			bool* checkedVertices1 = new bool[vertexCount_] {};
			bool* checkedVertices2 = new bool[vertexCount_] {};

			if (checkLink(i, j, checkedVertices1) && checkLink(j, i, checkedVertices2))
			{
				tmpGraph.addEdge(i, j);
				tmpGraph.addEdge(j, i);
			}

			delete[] checkedVertices1;
			delete[] checkedVertices2;
		}
	}

	bool* checkedVertices = new bool[vertexCount_] {};

	for (int i = 0; i < vertexCount_; i++)
	{
		if (!checkedVertices[i])
		{
			tmpGraph.findComponent(i, checkedVertices);
			cout << "\n";
		}
	}
}