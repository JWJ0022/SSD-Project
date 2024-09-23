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

int LBA_count = 0;  // 저장된 LBA의 개수

const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";

// I/O 함수 선언 (실제로 구현되지 않음, 필요 시 구현 추가)
namespace IO {
    void Read(int index, uint32_t data) {
        // Read 함수는 실제 I/O에서 값을 읽는 기능으로 구현
    }

    void Write(int index, string data) {
        // Write 함수는 실제 I/O에 데이터를 쓰는 기능으로 구현
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
    uint32_t data = 0;
    IO::Read(index, data);

    ofstream resultFile(RESULT_FILE);
    resultFile << "0x" << hex << setw(8) << setfill('0') << data << endl;
    cout << "Result written to " << RESULT_FILE << endl;
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
