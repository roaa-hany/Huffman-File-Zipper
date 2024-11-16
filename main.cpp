#include "huffman.h"
#include <iostream>
#include<stdexcept>
#include<fstream>

using namespace std;
long getfilesize(string& inputfile) {
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
    try {
        char choice;
        do {
            string input;
            cout<<"Kindly enter the location of your input file: "<<endl;
            cin>>input;
            cout<<"Enter c if you want to compress this file, or d if you want to decompress it, e to exit: "<<endl;
            cin>>choice;
            if(choice=='c') {
                string compressedFile = "compressed.txt";
                writeCompressedFile(input, compressedFile);
                cout << "File compressed successfully :\")" << endl;
                long s1=getfilesize(input);
                long s2=getfilesize(compressedFile);
                cout <<"The size of the file before compressing is: "<<s1 <<" bytes"<<endl;
                cout<<"The size of the file after compressing is: "<<s2<<" bytes"<<endl;
                cout<<"The efficiency of compression is: "<<((s1-s2)/double(s1))*100 <<"%"<<endl;
            }
            else if(choice=='d') {
                string outputFile = "output.txt";
                decompressFile(input, outputFile);
                cout << "File decompressed successfully :\")" << endl;
            }
        }
        while(choice!='e');

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
