#include "bus.hpp"

Bus::Bus() {
    // cpu = new CPU();
    for (auto &i : ram) i = 0x00;
    cpu.ConnectBus(this);
}

Bus::~Bus() {
    
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0x7FFF)
        ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr) {
    if (addr >= 0x0000 && addr <= 0x7FFF)
        return ram[addr];

    return 0x00;
}

void Bus::clock() {
    cpu.clock();
}