#ifndef HUFFMANENGINE_H
#define HUFFMANENGINE_H

#include <string>
#include <map>
#include "Node.h"

using namespace std;

class HuffmanEngine
{
private:
    map<char, int> frequencyTable;
    map<char, string> huffmanCodes;

    Node* root;

    void buildFrequencyTable(const string& text);
    Node* buildHuffmanTree();
    void generateCodes(Node* node, string code);
    void deleteTree(Node* node);

public:
    HuffmanEngine();
    ~HuffmanEngine();

    void processText(const string& text);
    void displayFrequencies();
    void displayCodes();
    string encodeText(const string& text);
    void saveEncodedFile(const string& encodedText, const string& fileName);
    void saveCompressedFile(const string& encodedText, const string& fileName);

    void decompressFile(const string& inputFileName, const string& outputFileName);
};

#endif