#include <iostream>
#include <fstream>

#include "testapp.h"
#include "../inc/ssd.h"

void testSuccess(int test_num) {
    printf("TEST %d : SUCCESS\n", test_num);
}

void testFail(int test_num) {
    printf("TEST %d : FAIL\n", test_num);
}

void test_app1() {
    string data = TEST_DATA_1;
    ssd_full_write(data);

    ssd_full_read();

    ifstream readFile;
    std::string line;

    readFile.open(RESULT_FILE);
    if(!readFile.is_open()) {
	std::cout << "testapp1 : cannot open file\n"; 
	return;
    }

    bool test_flag = true;
    while (getline(readFile, line)) {
	if(line != TEST_DATA_1) test_flag = false;
    }

    readFile.close();
    
    ssd_full_write(INIT_DATA);

    if(test_flag) testSuccess(1);
    else testFail(1);
}

void test_app2() {
    for(int i = 0; i < 30; i++) {
	ssd_write(i%6, TEST_DATA_1);
    }

    for(int i = 0; i < 6; i++) {
	ssd_write(i, TEST_DATA_2);
    }

    ifstream readFile;

    bool test_flag = true;
    for(int i = 0; i < 6; i++) {
	ssd_read(i);

	readFile.open(RESULT_FILE);
        if(!readFile.is_open()) {
	    std::cout << "testapp2 : cannot open file\n"; 
	    return;
        }

	std::string line;
	getline(readFile, line);

	readFile.close();

	if(line != TEST_DATA_2) test_flag = false;

    }

    ssd_full_write(INIT_DATA);

    if(test_flag) testSuccess(2);
    else testFail(2);
}
