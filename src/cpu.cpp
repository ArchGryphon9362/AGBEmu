#include "cpu.hpp"
#include "bus.hpp"
#include <iostream>

CPU::CPU() {
    using a = CPU;
    using b = CPU::ARG;
    lookup = {
        { "NOP", &a::NOP, b::IMP, 4 }
    };

    regs.af.value = 0;
    regs.bc.value = 0;
    regs.de.value = 0;
    regs.hl.value = 0;
    regs.stackPointer = 0;
    regs.programCounter = 0;
}

CPU::~CPU() {

}

void CPU::write(uint16_t addr, uint8_t data) {
    bus->write(addr, data);
}

uint8_t CPU::read(uint16_t addr) {
    return bus->read(addr);
}

void CPU::clock() {
    if (cycles == 0) {
        opcode = read(regs.programCounter++);
        fetch();

        cycles = lookup[opcode].cycles;

        (this->*lookup[opcode].operate)();
    }
    cycles--;
}

void CPU::fetch() {

}

/* #region Instructions */

void CPU::NOP() {
    std::cout << "NOP" << std::endl;
}

/* #endregion */