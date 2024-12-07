#include <iostream>
#include <fstream>
#include "FileZipper.h"

using namespace std;

// Function to get the size of a file
// This function opens the file in binary mode and returns its size
long getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);  // Open file in binary mode and move the pointer to the end
    if (!file.is_open()) {  // Check if the file opens successfully
        cerr << "Error calculating the size of the file." << endl;
        return -1;
    }
    long size = file.tellg();  // Get the current position of the pointer (i.e., the size of the file)
    file.close();  // Close the file
    return size;
}

int main() {
    // Declare variables to hold the file names
    string inputFilename, compressedFilename, decompressedFilename;

    // Prompt the user for input file, compressed file, and decompressed file names
    cout << "Enter the input text file to compress: ";
    cin >> inputFilename;

    cout << "Enter the filename to save the compressed and encrypted data: ";
    cin >> compressedFilename;

    cout << "Enter the filename to save the decompressed data: ";
    cin >> decompressedFilename;

    // Create an instance of the FileZipper class
    FileZipper fileZipper;

    // Step 1: Compress and encrypt the file
    cout << "Compressing and encrypting file..." << endl;
    fileZipper.compress(inputFilename, compressedFilename);
    cout << "File compressed, encrypted, and saved as " << compressedFilename << endl;

    // Step 2: Calculate and display the file sizes and compression efficiency
    long s1 = getFileSize(inputFilename);  // Get the original file size
    long s2 = getFileSize(compressedFilename);  // Get the compressed file size

    cout << "The size of the file before compression is: " << s1 << " bytes" << endl;
    cout << "The size of the file after compressing is: " << s2 << " bytes" << endl;
    cout << "The efficiency of compression is: " << ((s1 - s2) / double(s1)) * 100 << "%" << endl;

    // Step 3: Decrypt and decompress the file
    cout << "Decrypting and decompressing file..." << endl;
    fileZipper.decompress(compressedFilename, decompressedFilename);
    cout << "File decrypted, decompressed, and saved as " << decompressedFilename << endl;

    // Step 4: Verify if the decompressed file matches the original file
    ifstream originalFile(inputFilename, ios::binary);  // Open the original file for comparison
    ifstream decompressedFile(decompressedFilename, ios::binary);  // Open the decompressed file for comparison

    if (!originalFile || !decompressedFile) {  // Check if either file fails to open
        cerr << "Error: Unable to open one of the files for comparison." << endl;
        return 1;
    }

    // Read the contents of both files into strings
    string originalContent((istreambuf_iterator<char>(originalFile)), istreambuf_iterator<char>());
    string decompressedContent((istreambuf_iterator<char>(decompressedFile)), istreambuf_iterator<char>());

    // Step 5: Compare the contents of the original and decompressed files
    if (originalContent == decompressedContent) {
        cout << "Success: Decompressed file matches the original file!" << endl;
    } else {
        cerr << "Error: Decompressed file does not match the original file." << endl;
    }

    // Close the file streams
    originalFile.close();
    decompressedFile.close();

    return 0;  // Program finished successfully
}
