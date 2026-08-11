#ifndef NODE_H
#define NODE_H

class Node
{
public:
    char character;
    int frequency;

    Node* left;
    Node* right;

    Node(char ch, int freq);
    Node(int freq, Node* leftNode, Node* rightNode);

    bool isLeaf();
};

#endif