#include <iostream>
#include "bus.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Arch's Gameboy Emulator!" << std::endl;

    Bus gb;

    gb.write(0xC53F, 0x45); // fyi, if you wondering, this is just an arbitrary address i'm using for testing
    std::cout << std::to_string(gb.read(0xC53F)) << std::endl;
    gb.clock();

    gb.testCPU();

    return 0;
}