#include "HuffmanEngine.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct CompareNodes
{
    bool operator()(Node* first, Node* second)
    {
        return first->frequency > second->frequency;
    }
};

HuffmanEngine::HuffmanEngine()
{
    root = nullptr;
}

HuffmanEngine::~HuffmanEngine()
{
    deleteTree(root);
}

void HuffmanEngine::deleteTree(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void HuffmanEngine::buildFrequencyTable(const string& text)
{
    frequencyTable.clear();

    for (int i = 0; i < text.length(); i++)
    {
        frequencyTable[text[i]]++;
    }
}

Node* HuffmanEngine::buildHuffmanTree()
{
    priority_queue<Node*, vector<Node*>, CompareNodes> pq;

    for (auto item : frequencyTable)
    {
        Node* newNode = new Node(item.first, item.second);
        pq.push(newNode);
    }

    while (pq.size() > 1)
    {
        Node* leftNode = pq.top();
        pq.pop();

        Node* rightNode = pq.top();
        pq.pop();

        int combinedFrequency =
            leftNode->frequency + rightNode->frequency;

        Node* parent =
            new Node(
                combinedFrequency,
                leftNode,
                rightNode
            );

        pq.push(parent);
    }

    return pq.top();
}

void HuffmanEngine::generateCodes(Node* node, string code)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->isLeaf())
    {
        if (code == "")
        {
            code = "0";
        }

        huffmanCodes[node->character] = code;
        return;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

void HuffmanEngine::processText(const string& text)
{
    deleteTree(root);
    root = nullptr;

    buildFrequencyTable(text);

    root = buildHuffmanTree();

    huffmanCodes.clear();

    generateCodes(root, "");
}

void HuffmanEngine::displayFrequencies()
{
    cout << endl;
    cout << "Character Frequencies:" << endl;

    for (auto item : frequencyTable)
    {
        cout << item.first
             << " = "
             << item.second
             << endl;
    }
}

void HuffmanEngine::displayCodes()
{
    cout << endl;
    cout << "Huffman Codes:" << endl;

    for (auto item : huffmanCodes)
    {
        cout << item.first
             << " = "
             << item.second
             << endl;
    }
}

string HuffmanEngine::encodeText(const string& text)
{
    string encodedText = "";

    for (int i = 0; i < text.length(); i++)
    {
        encodedText += huffmanCodes[text[i]];
    }

    return encodedText;
}

void HuffmanEngine::saveEncodedFile(
    const string& encodedText,
    const string& fileName
)
{
    ofstream outputFile(fileName);

    if (!outputFile)
    {
        cout << "Error creating compressed file!" << endl;
        return;
    }

    outputFile << encodedText;

    outputFile.close();

    cout << endl;
    cout << "Compressed file created successfully!" << endl;
}

void HuffmanEngine::saveCompressedFile(
    const string& encodedText,
    const string& fileName
)
{
    ofstream outputFile(fileName, ios::binary);

    if (!outputFile)
    {
        cout << "Error creating compressed file!" << endl;
        return;
    }

    int uniqueCharacters = frequencyTable.size();

    outputFile.write(
        reinterpret_cast<char*>(&uniqueCharacters),
        sizeof(uniqueCharacters)
    );

    for (auto item : frequencyTable)
    {
        char character = item.first;
        int frequency = item.second;

        outputFile.write(
            &character,
            sizeof(character)
        );

        outputFile.write(
            reinterpret_cast<char*>(&frequency),
            sizeof(frequency)
        );
    }

    int totalBits = encodedText.length();

    outputFile.write(
        reinterpret_cast<char*>(&totalBits),
        sizeof(totalBits)
    );

    unsigned char currentByte = 0;
    int bitCount = 0;

    for (int i = 0; i < encodedText.length(); i++)
    {
        currentByte = currentByte << 1;

        if (encodedText[i] == '1')
        {
            currentByte = currentByte | 1;
        }

        bitCount++;

        if (bitCount == 8)
        {
            outputFile.write(
                reinterpret_cast<char*>(&currentByte),
                sizeof(currentByte)
            );

            currentByte = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0)
    {
        currentByte =
            currentByte << (8 - bitCount);

        outputFile.write(
            reinterpret_cast<char*>(&currentByte),
            sizeof(currentByte)
        );
    }

    outputFile.close();

    cout << endl;
    cout << "File compressed successfully!" << endl;
}

void HuffmanEngine::decompressFile(
    const string& inputFileName,
    const string& outputFileName
)
{
    ifstream inputFile(
        inputFileName,
        ios::binary
    );

    if (!inputFile)
    {
        cout << "Error opening compressed file!" << endl;
        return;
    }

    deleteTree(root);
    root = nullptr;

    frequencyTable.clear();

    int uniqueCharacters;

    inputFile.read(
        reinterpret_cast<char*>(&uniqueCharacters),
        sizeof(uniqueCharacters)
    );

    for (int i = 0; i < uniqueCharacters; i++)
    {
        char character;
        int frequency;

        inputFile.read(
            &character,
            sizeof(character)
        );

        inputFile.read(
            reinterpret_cast<char*>(&frequency),
            sizeof(frequency)
        );

        frequencyTable[character] = frequency;
    }

    int totalBits;

    inputFile.read(
        reinterpret_cast<char*>(&totalBits),
        sizeof(totalBits)
    );

    root = buildHuffmanTree();

    string decodedText = "";

    Node* currentNode = root;

    int bitsRead = 0;

    unsigned char currentByte;

    while (
        bitsRead < totalBits &&
        inputFile.read(
            reinterpret_cast<char*>(&currentByte),
            sizeof(currentByte)
        )
    )
    {
        for (
            int bitPosition = 7;
            bitPosition >= 0 &&
            bitsRead < totalBits;
            bitPosition--
        )
        {
            int bit =
                (currentByte >> bitPosition) & 1;

            if (bit == 0)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode = currentNode->right;
            }

            bitsRead++;

            if (
                currentNode != nullptr &&
                currentNode->isLeaf()
            )
            {
                decodedText +=
                    currentNode->character;

                currentNode = root;
            }
        }
    }

    inputFile.close();

    ofstream outputFile(outputFileName);

    if (!outputFile)
    {
        cout << "Error creating decompressed file!" << endl;
        return;
    }

    outputFile << decodedText;

    outputFile.close();

    cout << endl;
    cout << "File decompressed successfully!" << endl;
    cout << "Decoded Text: "
         << decodedText
         << endl;
}