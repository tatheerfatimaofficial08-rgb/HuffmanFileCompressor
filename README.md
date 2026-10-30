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

Possible Huffman codes (exact codes depend on how ties are broken):
A = 0
B = 10
N = 11

Encoded BANANA = 10 0 11 0 11 0 = 100110110 (9 bits, instead of 48 bits in ASCII)
```

---

## Project Structure

| File | Purpose |
|------|---------|
| `main.cpp` | Menu-driven interface |
| `HuffmanEngine.cpp / .h` | Frequency table, Huffman tree, encoding, file saving, decompression |
| `Node.cpp / .h` | Huffman tree node |
| `CompressionHistory.cpp / .h` | Stores and displays past compression results |
| `input.txt` | Sample input file |
| `Makefile` | Build and run commands |

---

## Build and Run

Requirements: a C++17 compiler (such as `g++`) and `make`.

```bash
git clone https://github.com/tatheerfatimaofficial08-rgb/HuffmanFileCompressor.git
cd HuffmanFileCompressor
make          # build
./main        # run  (or: make run)
make clean    # remove build files
```

Without `make`:

```bash
g++ -std=c++17 -O2 main.cpp HuffmanEngine.cpp Node.cpp CompressionHistory.cpp -o main
```

### Usage

1. Choose **1** to compress, then enter an input file (for example `input.txt`) and a name for the compressed file (for example `compressed.huff`).
2. Choose **2** to decompress, then enter the `.huff` file and a name for the restored file.
3. Choose **3** to view the compression history.

---

## Example Result

Compressing the included `input.txt`:

| Original size | Compressed size | Space saved |
|---------------|-----------------|-------------|
| 917 bytes | 682 bytes | 25.63% |

The decompressed file was compared with the original and matched exactly, which confirms the compression is lossless.

Note: the compressed file also stores the character frequency table (used to rebuild the Huffman tree when decompressing), so very small files may not shrink much.

---

## Author

Tatheer Fatima, BS Computer Science student, Air University Multan
