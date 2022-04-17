#include <iostream>
#include "bus.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Arch's Gameboy Emulator!" << std::endl;

    Bus gb;

    gb.write(0x3A0A, 0x45);
    std::cout << std::to_string(gb.read(0x3A0A)) << std::endl;
    gb.clock();

    return 0;
}