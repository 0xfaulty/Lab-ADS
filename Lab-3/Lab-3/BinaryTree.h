#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* parent;
    Node* left, * right;
    Node(char data, Node* parent);
    ~Node();

    void directVisit(string& buffer, int depth, int& result);
    void reverseVisit(string& buffer, int depth, int& result);
    void internalVisit(string& buffer, int depth, int& result);
};

class BinaryTree {
private:
    Node* root_;
    int size_;
    int depth_;

    int fillBuffersAndGetIndex(Node* currentNode, string buffers[],
        int& lastDepthCounter, int currentDepth,
        int width);

public:
    BinaryTree();
    ~BinaryTree();

    int size();
    bool empty();
    void add(const string& word);
    void fill_const();
    void clear();
    void directPrint();
    void reversePrint();
    void internalPrint();
    void show();
};