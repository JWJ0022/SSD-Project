#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "../inc/ssd.h"
#include "../src/ssd.cpp"
#include "../inc/io.h"

#define INIT "init"
#define WRITE "write"
#define READ "read"
#define EXIT "exit"
#define HELP "help"
#define FULL_WRITE "fullwrite"
#define FULL_READ "fullread"

#define TESTAPP1 "testapp1"
#define TESTAPP2 "testapp2"

const int max_argc = 3;
const std::string helpFilePath = "../data/help.txt";

int main() {
    int argc;
    std::string argv[max_argc+1];

    while(1) {
	std::cout << "ssd >> ";
	std::string input; getline(std::cin, input);

	std::istringstream iss(input);
	std::string buffer;

	argc = 0;
	while(iss >> buffer) {
	    if(argc >= max_argc) {
		break;
	    }

	    argv[++argc] = buffer; 
	}

	if(argc == 1) {
	    if(argv[1] == EXIT) {
		return 0;
	    } else if(argv[1] == HELP) {
		std::ifstream openFile(helpFilePath.data());
		if(openFile.is_open()) {
		    std::string line;
		    while(getline(openFile, line)) {
			std::cout << line << '\n';
		    }
		    openFile.close();
		}
	    } else if(argv[1] == FULL_READ) {
		// ssd_fullread();
	    } else if(argv[1] == INIT) {
		// ssd_init();
	    } else if(argv[1] == TESTAPP1) {
		// test_app1();
	    } else if(argv[1] == TESTAPP2) {
		// test_app2();
	    } else {
		std::cout << "error : invalid command\n";	
	    }
	} else if(argc == 2) {
	    if(argv[1] == READ) {
		int index = stoi(argv[2]);
		ssd_read(index);
	    } else if(argv[1] == FULL_WRITE) {
		std::string data = argv[2];
		// ssd_fullwrite(data);
	    } else {
		std::cout << "error : invalid command\n";	
	    }
	} else if(argc == 3) {
	    if(argv[1] == WRITE) {
		int index = stoi(argv[2]);
		std::string data = argv[3];	
		ssd_write(index, data);
	    } else {
		std::cout << "error : invalid command\n";	
	    }
	} else {
	    std::cout << "error : invalid command\n";	
	}
    }

    return 0;
}
