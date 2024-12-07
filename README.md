# FileZipper Program

## Overview

The **FileZipper** program is a file compression and decompression utility that uses **Huffman Coding** to compress text files. It also provides an optional encryption feature using XOR encryption/decryption with a specified encryption key to protect the compressed data.

### Features
- **Compression**: Compresses text files by applying Huffman coding and saves the result in a compressed binary file.
- **Decompression**: Decompresses previously compressed files using Huffman coding and restores the original content.
- **Encryption**: Uses XOR encryption for securing the compressed file after compression and decrypts the file before decompression.

---

## File Structure

The project contains the following files:
- **FileZipper.h**: Header file for the FileZipper class.
- **FileZipper.cpp**: Source file containing the implementation of the FileZipper class.
- **LinkedList.h**: Header file for the LinkedList class, used to manage the frequency data.
- **HuffmanTree.h**: Header file for the HuffmanTree class, used for constructing and managing the Huffman Tree.
- **priority_queue.h**: Header file for the PriorityQueue class, used to prioritize nodes based on frequency for building the Huffman Tree.
- **HuffmanNode.h**: Header file for the HuffmanNode class, representing the nodes of the Huffman Tree.
- **main.cpp**: The entry point for the program, where the compression and decompression operations are invoked.

## Usage

### Compress a File

To compress a text file, use the following command format:

```bash
./FileZipper compress <input_filename> <compressed_filename>
```

### Decompress a File

To decompress a previously compressed file, use the following command format:

```bash
./FileZipper decompress <compressed_filename> <output_filename>
```

## Key Concepts

### Huffman Coding
A lossless data compression algorithm that encodes data based on the frequency of characters. Frequent characters are assigned shorter codes, while less frequent characters are assigned longer codes.

### XOR Encryption
A simple encryption technique that performs the bitwise XOR operation between the content and a key. The same key is used for both encryption and decryption.

## Error Handling

- If the program encounters an error while opening files for reading or writing, an error message will be displayed, and the operation will terminate.
- If the Huffman code for a character is not found or there are issues with padding bits, an error message will be displayed.

## Conclusion

The **FileZipper** program offers an easy-to-use solution for compressing, encrypting, and decompressing text files using Huffman coding. It is efficient for handling large text files while providing a simple way to secure compressed data.



