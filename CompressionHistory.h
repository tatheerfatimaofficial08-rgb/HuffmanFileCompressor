#ifndef COMPRESSIONHISTORY_H
#define COMPRESSIONHISTORY_H

#include <string>
using namespace std;

class CompressionHistory
{
public:
    void saveRecord(
        const string& fileName,
        long originalSize,
        long compressedSize
    );

    void displayHistory();
};

#endif