#include <iostream>
#include <regex>

#include "../inc/ssd.h"

using namespace std;

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

    void Full_Read()
    {
        fullread();
    }

    void Full_Write(string data)
    {
        fullwrite(data);
    }
}

// Read 함수
void ssd_read(int index) {
    if (index < 0 || index >= MAX_LBA) {
        cout << "ERROR: INVALID LBA INDEX" << endl;
        return;
    }

    IO::Read(index);
}

// Write 함수
void ssd_write(int index, string data) {
    if (index < 0 || index >= MAX_LBA) {
        cout << "ERROR: INVALID LBA INDEX" << endl;
        return;
    }

    // 데이터 형식 유효성 검사 (10자리 16진수인지 확인)
    regex hexPattern(REGEX_PATTERN);
    if (!regex_match(data, hexPattern)) {
        cout << "ERROR: INVALID DATA FORMAT. EXPECTED 0xXXXXXXXX" << endl;
        return;
    }

    // I/O에 데이터 쓰기
    IO::Write(index, data);
}

void ssd_full_write(string data)
{
    // 데이터 형식 유효성 검사 (10자리 16진수인지 확인)
    regex hexPattern(REGEX_PATTERN);
    if (!regex_match(data, hexPattern)) {
        cout << "ERROR: INVALID DATA FORMAT. EXPECTED 0xXXXXXXXX" << endl;
        return;
    }

    IO::Full_Write(data);
}

void ssd_full_read()
{
    IO::Full_Read();
}

