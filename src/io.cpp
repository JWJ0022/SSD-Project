#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../inc/io.h"

using namespace std;

void handle_file_error(const string &filename) {
    cerr << "Error: Could not open " << filename << endl;
}

void io_read(int idx) {
    ifstream nandFile(NAND_FILE);
    fstream resultFile(RESULT_FILE, ios::in | ios::out | ios::ate);

    if (!nandFile.is_open()) {
        handle_file_error(NAND_FILE);
        return;
    }

    if (!resultFile.is_open()) {
        handle_file_error(RESULT_FILE);
        return;
    }

    string line = "0x00000000"; 
    int currentLine = 0;

    while (getline(nandFile, line)) {
        if (currentLine++ == idx) break;
    }

    resultFile.clear();
    resultFile.seekg(0, ios::beg);  
    resultFile << line << endl;

    nandFile.close();
    resultFile.close();
}

void io_write(int index, string data) {
    ifstream nandFile(NAND_FILE);
    ofstream tempFile(TEMP_FILE);

    if (!tempFile.is_open()) {
        handle_file_error(TEMP_FILE);
        return;
    }

    if (!nandFile.is_open()) {
        handle_file_error(NAND_FILE);
        return;
    }

    string line;
    int currentLine = 0;

    while (getline(nandFile, line) || currentLine < MAX_LINES) {
        if (currentLine == index) tempFile << data << endl;
        else tempFile << (nandFile ? line : "0x00000000") << endl;
        ++currentLine;
    }

    nandFile.close();
    tempFile.close();

    ifstream tempInput(TEMP_FILE);
    ofstream nandOutput(NAND_FILE);

    if (!tempInput.is_open()) {
        handle_file_error(TEMP_FILE);
        return;
    }

    if (!nandOutput.is_open()) {
        handle_file_error(NAND_FILE);
        return;
    }

    nandOutput << tempInput.rdbuf();

    tempInput.close();
    nandOutput.close();
}

void fullwrite(string data) {
    ofstream nandFile(NAND_FILE);

    if (!nandFile.is_open()) {
        handle_file_error(NAND_FILE);
        return;
    }

    for (int i = 0; i < MAX_LINES; i++) {
        nandFile << data << endl;
    }

    nandFile.close();
}

void fullread() {
    ifstream nandFile(NAND_FILE);
    ofstream resultFile(RESULT_FILE);

    if (!nandFile.is_open()) {
        handle_file_error(NAND_FILE);
        return;
    }

    if (!resultFile.is_open()) {
        handle_file_error(RESULT_FILE);
        return;
    }

    string line;
    
    while (getline(nandFile, line)) {
        resultFile << line << endl;
    }

    nandFile.close();
    resultFile.close();
}

