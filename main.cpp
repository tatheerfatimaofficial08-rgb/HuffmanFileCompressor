#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanEngine.h"
#include "CompressionHistory.h"

using namespace std;

long getFileSize(const string& fileName)
{
    ifstream file(fileName, ios::binary | ios::ate);

    if (!file)
    {
        return 0;
    }

    return file.tellg();
}

int main()
{
    HuffmanEngine engine;
    CompressionHistory history;

    int choice;

    do
    {
        cout << endl;
        cout << "======================================" << endl;
        cout << "       HUFFMAN FILE COMPRESSOR        " << endl;
        cout << "======================================" << endl;
        cout << "1. Compress File" << endl;
        cout << "2. Decompress File" << endl;
        cout << "3. Display Compression History" << endl;
        cout << "4. Exit" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1)
        {
            string inputFileName;
            string compressedFileName;

            cout << "Enter input file name: ";
            cin >> inputFileName;

            cout << "Enter compressed file name: ";
            cin >> compressedFileName;

            ifstream inputFile(inputFileName);

            if (!inputFile)
            {
                cout << "Error opening input file!" << endl;
                continue;
            }

            string text;
            string line;

            while (getline(inputFile, line))
            {
                text += line;

                if (!inputFile.eof())
                {
                    text += '\n';
                }
            }

            inputFile.close();

            if (text.empty())
            {
                cout << "Input file is empty!" << endl;
                continue;
            }

            engine.processText(text);

            string encodedText = engine.encodeText(text);

            engine.displayFrequencies();
            engine.displayCodes();

            engine.saveCompressedFile(
                encodedText,
                compressedFileName
            );

            long originalSize =
                getFileSize(inputFileName);

            long compressedSize =
                getFileSize(compressedFileName);

            double spaceSaved = 0;

            if (originalSize > 0)
            {
                spaceSaved =
                    (1.0 -
                    (double)compressedSize / originalSize)
                    * 100;
            }

            cout << endl;
            cout << "Original Size: "
                 << originalSize
                 << " bytes" << endl;

            cout << "Compressed Size: "
                 << compressedSize
                 << " bytes" << endl;

            cout << "Space Saved: "
                 << spaceSaved
                 << "%" << endl;

            history.saveRecord(
                inputFileName,
                originalSize,
                compressedSize
            );
        }

        else if (choice == 2)
        {
            string compressedFileName;
            string outputFileName;

            cout << "Enter compressed file name: ";
            cin >> compressedFileName;

            cout << "Enter output file name: ";
            cin >> outputFileName;

            engine.decompressFile(
                compressedFileName,
                outputFileName
            );
        }

        else if (choice == 3)
        {
            history.displayHistory();
        }

        else if (choice == 4)
        {
            cout << endl;
            cout << "Program closed." << endl;
        }

        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 4);

    return 0;
}