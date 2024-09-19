#include "io.cpp"

int main() {
    io_write(3, "0xAAAABBBB");  
    io_read(3);        
    io_write(6, "0xAAAABBBB");  
    io_read(6);     

    cout << "DONE\n";
    return 0;
}
