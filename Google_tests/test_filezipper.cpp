#include "gtest/gtest.h"
#include "FileZipper.h"
#include <fstream>
#include <string>

// Helper function to write data to a file
void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

// Test case for file compression and decompression
TEST(FileZipperTest, CompressDecompressFile) {
    // Arrange: Create a sample input file
    std::string inputFilename = "test_input.txt";
    std::string compressedFilename = "test_compressed.bin";
    std::string decompressedFilename = "test_decompressed.txt";

    std::string inputContent = "This is a test file for compression and decompression.";
    writeToFile(inputFilename, inputContent);

    FileZipper fileZipper;

    // Act: Compress and decompress the file
    fileZipper.compress(inputFilename, compressedFilename);
    fileZipper.decompress(compressedFilename, decompressedFilename);

    // Assert: Verify that the decompressed file matches the original content
    std::ifstream decompressedFile(decompressedFilename);
    std::string decompressedContent((std::istreambuf_iterator<char>(decompressedFile)),
                                     (std::istreambuf_iterator<char>()));

    EXPECT_EQ(inputContent, decompressedContent);

    // Cleanup: Remove test files
    std::remove(inputFilename.c_str());
    std::remove(compressedFilename.c_str());
    std::remove(decompressedFilename.c_str());
}

// Test case for empty file handling
TEST(FileZipperTest, EmptyFile) {
    // Arrange: Create an empty input file
    std::string inputFilename = "empty_input.txt";
    std::string compressedFilename = "empty_compressed.bin";
    std::string decompressedFilename = "empty_decompressed.txt";

    writeToFile(inputFilename, "");

    FileZipper fileZipper;

    // Act: Compress and decompress the file
    fileZipper.compress(inputFilename, compressedFilename);
    fileZipper.decompress(compressedFilename, decompressedFilename);

    // Assert: Verify that the decompressed file is also empty
    std::ifstream decompressedFile(decompressedFilename);
    std::string decompressedContent((std::istreambuf_iterator<char>(decompressedFile)),
                                     (std::istreambuf_iterator<char>()));

    EXPECT_EQ("", decompressedContent);

    // Cleanup: Remove test files
    std::remove(inputFilename.c_str());
    std::remove(compressedFilename.c_str());
    std::remove(decompressedFilename.c_str());
}

// Test case for handling binary files
TEST(FileZipperTest, BinaryFile) {
    // Arrange: Create a binary input file
    std::string inputFilename = "binary_input.dat";
    std::string compressedFilename = "binary_compressed.bin";
    std::string decompressedFilename = "binary_decompressed.dat";

    // Creating some binary content (e.g., a simple byte array)
    std::string binaryContent = "\x01\x02\x03\x04\x05\x06\x07\x08";
    writeToFile(inputFilename, binaryContent);

    FileZipper fileZipper;

    // Act: Compress and decompress the binary file
    fileZipper.compress(inputFilename, compressedFilename);
    fileZipper.decompress(compressedFilename, decompressedFilename);

    // Assert: Verify that the decompressed file matches the original binary content
    std::ifstream decompressedFile(decompressedFilename, std::ios::binary);
    std::string decompressedContent((std::istreambuf_iterator<char>(decompressedFile)),
                                     (std::istreambuf_iterator<char>()));

    EXPECT_EQ(binaryContent, decompressedContent);

    // Cleanup: Remove test files
    std::remove(inputFilename.c_str());
    std::remove(compressedFilename.c_str());
    std::remove(decompressedFilename.c_str());
}


// Test case for compression efficiency
TEST(FileZipperTest, CompressionEfficiency) {
    // Arrange: Create a sample input file
    std::string inputFilename = "efficiency_input.txt";
    std::string compressedFilename = "efficiency_compressed.bin";

    std::string inputContent = "This is a test file to check compression efficiency.";
    writeToFile(inputFilename, inputContent);

    FileZipper fileZipper;


    // Act: Compress the file
    fileZipper.compress(inputFilename, compressedFilename);

    // Assert: Verify that the compressed file is smaller than the original
    std::ifstream originalFile(inputFilename, std::ios::binary | std::ios::ate);
    std::ifstream compressedFile(compressedFilename, std::ios::binary | std::ios::ate);

    long originalSize = originalFile.tellg();
    long compressedSize = compressedFile.tellg();

    EXPECT_LT(compressedSize, originalSize); // Ensure compression reduces file size

    // Cleanup: Remove test files
    std::remove(inputFilename.c_str());
    std::remove(compressedFilename.c_str());
}


