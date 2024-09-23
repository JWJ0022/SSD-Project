#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

#include "../inc/io.h"

using namespace std;

// 속성 정의
#define LBA_SIZE 4
#define MAX_LBA 100
#define INIT_DATA "0x00000000"

int LBA_count = 0;  // 저장된 LBA의 개수

// I/O 함수 선언 (실제로 구현되지 않음, 필요 시 구현 추가)
namespace IO {
    void Read(int index) {
        // Read 함수는 실제 I/O에서 값을 읽는 기능으로 구현
	io_read(index);
    }

    void Write(int index, string data) {
        // Write 함수는 실제 I/O에 데이터를 쓰는 기능으로 구현
	io_write(index, data);
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

