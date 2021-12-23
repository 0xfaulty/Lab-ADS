#include "BinaryTree.h"

Node::Node(char data, Node* parent) {
	this->data = data;
	this->parent = parent;
	left = right = nullptr;
}

Node::~Node() {
	if (left) delete left;
	if (right) delete right;
}

void Node::directVisit(string& buffer, int depth, int& result) {
	buffer += data;
	if (depth > 2)
		result++;
	if (left) left->directVisit(buffer, depth + 1, result);
	if (right) right->directVisit(buffer, depth + 1, result);
}

void Node::reverseVisit(string& buffer, int depth, int& result) {
	if (right) right->reverseVisit(buffer, depth + 1, result);
	if (left) left->reverseVisit(buffer, depth + 1, result);
	buffer += data;
	if (depth > 2)
		result++;
}

void Node::internalVisit(string& buffer, int depth, int& result) {
	if (left) left->internalVisit(buffer, depth + 1, result);
	buffer += data;
	if (depth > 2)
		result++;
	if (right) right->internalVisit(buffer, depth + 1, result);
}

int BinaryTree::fillBuffersAndGetIndex(Node* currentNode, string buffers[], int& lastDepthCounter, int currentDepth, int width) {
	int index;
	if (currentDepth == depth_) {
		index = lastDepthCounter + (lastDepthCounter / 2);
		if (currentNode) {
			buffers[currentDepth - 1][index] = currentNode->data;
		}
		++lastDepthCounter;
	}
	else {
		Node* left, * right;
		left = right = nullptr;

		if (currentNode) {
			left = currentNode->left;
			right = currentNode->right;
		}

		int position = 0;

		position = fillBuffersAndGetIndex(left, buffers, lastDepthCounter, currentDepth + 1, width);
		position += fillBuffersAndGetIndex(right, buffers, lastDepthCounter, currentDepth + 1, width);

		index = position / 2;

		if (currentNode) {
			buffers[currentDepth - 1][index] = currentNode->data;
		}
	}
	return index;
}

BinaryTree::BinaryTree() {
	root_ = nullptr;
	size_ = depth_ = 0;
}

int BinaryTree::size() { return size_; }

bool BinaryTree::empty() { return size_ == 0; }

BinaryTree::~BinaryTree() {
	if (root_) delete root_;
}

void BinaryTree::add(const string& word) {
	int wordSize = word.size();
	if (wordSize == 0)
		return;

	int index = 0;
	Node* current;

	current = root_;
	int currentDepth = 1;

	if (!root_) {
		root_ = new Node(word[index++], nullptr);
		depth_ = size_ = 1;
		current = root_;
	}

	while (index < wordSize) {
		if (word[index] < current->data) {
			if (!current->left) {
				current->left = new Node(word[index++], current);
				current = root_;
				size_++;
				currentDepth++;
				if (currentDepth > depth_) {
					depth_ = currentDepth;
				}
				currentDepth = 1;
			}
			else {
				current = current->left;
				++currentDepth;
			}
		}
		else {
			if (!current->right) {
				current->right = new Node(word[index++], current);
				current = root_;
				size_++;
				currentDepth++;
				if (currentDepth > depth_) {
					depth_ = currentDepth;
				}
				currentDepth = 1;
			}
			else {
				current = current->right;
				++currentDepth;
			}
		}
	}

}

void BinaryTree::fill_const() {
	add("614823790");
}

void BinaryTree::clear() {
	if (root_) delete root_;
	root_ = nullptr;
	size_ = depth_ = 0;
}

void BinaryTree::directPrint() {
	cout << "Прямой обход: ";
	if (root_) {
		string buffer;
		int depth = 1;
		int result = 0;
		root_->directVisit(buffer, depth, result);
		cout << buffer << ", Вершин > 2: " << result << endl;
	}
	cout << endl;
}

void BinaryTree::reversePrint() {
	cout << "Обратный обход: ";
	if (root_) {
		string buffer;
		int depth = 1;
		int result = 0;
		root_->reverseVisit(buffer, depth, result);
		cout << buffer << ", Вершин > 2: " << result << endl;
	}
	cout << endl;
}

void BinaryTree::internalPrint() {
	cout << "Внутренний обход: ";
	if (root_) {
		string buffer;
		int depth = 1;
		int result = 0;
		root_->internalVisit(buffer, depth, result);
		cout << buffer << ", Вершин > 2: " << result << endl;
	}
	cout << endl;
}

void BinaryTree::show() {
	if (root_) {
		int width = 1;
		if (depth_ > 1) {
			width = pow(2, depth_ - 1) + pow(2, depth_ - 2) - 1;
		}

		string* buffers = new string[depth_];
		int lastDepthCounter = 0;
		for (int i = 0; i < depth_; ++i) {
			for (int j = 0; j < width; ++j) {
				buffers[i] += '.';
			}
		}

		fillBuffersAndGetIndex(root_, buffers, lastDepthCounter, 1, width);

		for (int i = 0; i < depth_; ++i) {
			cout << buffers[i] << endl;
		}

		delete[] buffers;
	}
}