#include "Node.h"

Node::Node(char ch, int freq)
{
    character = ch;
    frequency = freq;

    left = nullptr;
    right = nullptr;
}

Node::Node(int freq, Node* leftNode, Node* rightNode)
{
    character = '\0';
    frequency = freq;

    left = leftNode;
    right = rightNode;
}

bool Node::isLeaf()
{
    return left == nullptr && right == nullptr;
}