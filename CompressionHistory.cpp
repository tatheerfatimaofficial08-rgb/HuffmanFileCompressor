#include "CompressionHistory.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void CompressionHistory::saveRecord(
    const string& fileName,
    long originalSize,
    long compressedSize
)
{
    ofstream historyFile("history.txt", ios::app);

    if (!historyFile)
    {
        cout << "Error opening history file!" << endl;
        return;
    }

    double spaceSaved = 0;

    if (originalSize > 0)
    {
        spaceSaved =
            (1.0 - (double)compressedSize / originalSize) * 100;
    }

    historyFile << "File Name: " << fileName << endl;
    historyFile << "Original Size: " << originalSize << " bytes" << endl;
    historyFile << "Compressed Size: " << compressedSize << " bytes" << endl;

    historyFile << fixed << setprecision(2);
    historyFile << "Space Saved: " << spaceSaved << "%" << endl;

    historyFile << "--------------------------------------" << endl;

    historyFile.close();
}

void CompressionHistory::displayHistory()
{
    ifstream historyFile("history.txt");

    if (!historyFile)
    {
        cout << endl;
        cout << "No compression history found." << endl;
        return;
    }

    string line;

    cout << endl;
    cout << "========== COMPRESSION HISTORY ==========" << endl;

    while (getline(historyFile, line))
    {
        cout << line << endl;
    }

    historyFile.close();
}