#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

using namespace std;

// 속성 정의
#define LBA_SIZE 4
#define MAX_LBA 100
#define INIT_DATA "0x00000000"
#define TEMP_FILE "temp.txt"

int LBA_count = 0;  // 저장된 LBA의 개수

const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";

// I/O 함수 구현
namespace IO {
    void handle_file_error(const string& filename) {
        cerr << "Error: Could not open " << filename << endl;
    }

    // Read 함수: nand.txt 파일에서 지정된 index의 데이터를 읽고 result.txt 파일에 기록
    void Read(int idx) {
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

        if (currentLine <= idx && line.empty()) {
            line = "0x00000000";
        }

        resultFile.seekg(0, ios::beg);
        currentLine = 0;
        string resultLine;

        while (getline(resultFile, resultLine)) {
            currentLine++;
        }

        while (currentLine <= idx) {
            resultFile.clear();
            resultFile.seekp(0, ios::end);
            resultFile << "0x00000000" << endl;
            currentLine++;
        }

        resultFile.clear();
        resultFile.seekg(0, ios::beg);
        currentLine = 0;

        while (getline(resultFile, resultLine)) {
            if (currentLine == idx) {
                resultFile.clear();
                resultFile.seekp(static_cast<streamoff>(resultFile.tellg()) - static_cast<streamoff>(resultLine.size()) - 1);  // Move to the start of the line
                resultFile << line << endl;
                break;
            }
            currentLine++;
        }

        nandFile.close();
        resultFile.close();
    }

    // Write 함수: nand.txt 파일에 데이터를 쓰고 temp.txt 파일을 통해 업데이트
    void Write(int index, string data) {
        ifstream nandFile(NAND_FILE);
        ofstream tempFile(TEMP_FILE);

        if (!nandFile.is_open()) {
            handle_file_error(NAND_FILE);
            return;
        }

        if (!tempFile.is_open()) {
            handle_file_error(TEMP_FILE);
            return;
        }

        string line;
        int currentLine = 0;

        while (getline(nandFile, line) || currentLine < MAX_LBA) {
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
}

// SSD 초기화 함수
void init() {
    ofstream nandFile(NAND_FILE);
    for (int i = 0; i < MAX_LBA; i++) {
        nandFile << INIT_DATA << endl;
    }
    nandFile.close();
    LBA_count = 0;
}

// Read 함수
void ssd_read(int index) {
    if (index < 0 || index >= MAX_LBA) {
        cout << "ERROR: INVALID LBA INDEX" << endl;
        return;
    }

    // 실제 I/O에서 값을 읽음
    IO::Read(index);
}

// Write 함수
void ssd_write(int index, string data) {
    if (index < 0 || index >= MAX_LBA) {
        cout << "ERROR: INVALID LBA INDEX" << endl;
        return;
    }

    if (LBA_count >= MAX_LBA) {
        cout << "ERROR: MAXIMUM LBA COUNT REACHED" << endl;
        return;
    }

    // 데이터 형식 유효성 검사 (10자리 16진수인지 확인)
    regex hexPattern("^0x[0-9A-Fa-f]{8}$");
    if (!regex_match(data, hexPattern)) {
        cout << "ERROR: INVALID DATA FORMAT. EXPECTED 0xXXXXXXXX" << endl;
        return;
    }

    // I/O에 데이터 쓰기
    IO::Write(index, data);

    LBA_count++;
}

// 명령어 처리 함수
void processCommand(const string& command) {
    stringstream ss(command);
    string cmd;
    ss >> cmd;

    if (cmd == "W") {  // Write 명령어
        int lba;
        string value;
        ss >> lba >> value;
        ssd_write(lba, value);
    }
    else if (cmd == "R") {  // Read 명령어
        int lba;
        ss >> lba;
        ssd_read(lba);
    }
    else if (cmd == "init") {  // 초기화 명령어
        init();
        cout << "SSD Initialized" << endl;
    }
    else {
        cout << "INVALID COMMAND" << endl;
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ssd [command]" << endl;
        return 1;
    }
    string command;
    for (int i = 1; i < argc; i++) {
        command += string(argv[i]) + " ";
    }
    processCommand(command);
    return 0;
}
