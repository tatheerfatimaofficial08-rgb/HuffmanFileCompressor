# Huffman File Compressor

A C++ based file compression and decompression project that implements the Huffman Coding algorithm.

The program analyzes character frequencies, builds a Huffman Tree, generates variable-length binary codes, compresses text into a binary `.huff` file, and reconstructs the original file without losing any data.

---

## Features

- Compress text files using Huffman Coding
- Decompress `.huff` files
- Lossless file reconstruction
- Character frequency analysis
- Huffman Tree generation
- Binary encoding
- Binary file storage
- Compression percentage calculation
- Compression history
- Menu-driven interface
- Multi-line text file support

---

## How Huffman Coding Works

Huffman Coding is a lossless data compression algorithm.

Characters that appear frequently are assigned shorter binary codes, while less frequent characters receive longer codes.

For example:

```text
Text: BANANA

Frequency:
A = 3
B = 1
N = 2