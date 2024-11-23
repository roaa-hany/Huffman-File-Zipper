#include <iostream>
#include <fstream>
#include "FileZipper.h"
using namespace std;

long getFileSize(string& inputfile) {
    ifstream file(inputfile, ios::binary | ios::ate);

    if (!file.is_open()) {
        cerr << "Error calculating the size of the file." << endl;
        return -1;
    }

    long size = file.tellg();

    file.close();
    return size;
}

int main() {
    string inputFilename, compressedFilename, decompressedFilename;

    cout << "Enter the input text file to compress: ";
    cin >> inputFilename;

    cout << "Enter the filename to save the compressed data: ";
    cin >> compressedFilename;

    cout << "Enter the filename to save the decompressed data: ";
    cin >> decompressedFilename;

    FileZipper fileZipper;

    // Compress the file
    cout << "Compressing file..." << endl;
    fileZipper.compress(inputFilename, compressedFilename);
    cout << "File compressed and saved as " << compressedFilename << endl;

    // Decompress the file
    cout << "Decompressing file..." << endl;
    fileZipper.decompress(compressedFilename, decompressedFilename);
    cout << "File decompressed and saved as " << decompressedFilename << endl;

    //Calculating the compression percentage
    long s1 = getFileSize(inputFilename);
    long s2 = getFileSize(compressedFilename);

    cout << "The size of the file before compression is: " << s1 << " bytes" << endl;
    cout << "The size of the file after compressing is: " << s2 << " bytes" << endl;
    cout << "The efficiency of compression is: " << ((s1-s2)/double(s1)) * 100 << "%" << endl;
//    // Verify decompression
//    ifstream originalFile(inputFilename);
//    ifstream decompressedFile(decompressedFilename);
//
//    if (!originalFile || !decompressedFile) {
//        cerr << "Error: Unable to open one of the files for comparison." << endl;
//        return 1;
//    }

//    string originalContent((istreambuf_iterator<char>(originalFile)),
//                                (istreambuf_iterator<char>()));
//    string decompressedContent((istreambuf_iterator<char>(decompressedFile)),
//                                     (istreambuf_iterator<char>()));
//
//    if (originalContent == decompressedContent) {
//        cout << "Success: Decompressed file matches the original file!" << endl;
//    } else {
//        cerr << "Error: Decompressed file does not match the original file." << endl;
//    }
//
//    originalFile.close();
//    decompressedFile.close();

    return 0;
}
