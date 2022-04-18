#include "bus.hpp"

Bus::Bus() {
    // cpu = new CPU();
    for (auto &i : ram) i = 0x00;
    cpu.ConnectBus(this);
}

Bus::~Bus() {
    
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr >= 0xC000 && addr <= 0xCFFF)
        ram[addr - 0xC000] = data;

    if (addr == 0xFF0F)
        intFlag.value = data;

    if (addr == 0xFFFF)
        intEnable.value = data;
}

uint8_t Bus::read(uint16_t addr) {
    if (addr >= 0xC000 && addr <= 0xCFFF)
        return ram[addr - 0xC000];

    if (addr == 0xFF0F)
        return intFlag.value;

    if (addr == 0xFFFF)
        return intEnable.value;
    return 0x00;
}

void Bus::clock() {
    cpu.clock();
}

void Bus::testCPU() {
    cpu.testCPU();
}