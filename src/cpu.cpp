#include "cpu.hpp"
#include "bus.hpp"
#include <iostream>

CPU::CPU() {
    using a = CPU;
    lookup = {
        { "NOP", &a::NOP, 0, 4 }
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
        // :: Account for halt bug!
        if (scheduleIME) { IME = 0x01; scheduleIME = 0x00; }

        opcode = read(regs.programCounter++);
        cycles = lookup[opcode].cycles;

        fetch(lookup[opcode].argLength);
        (this->*lookup[opcode].operate)();
    }
    cycles--;
}

void CPU::fetch(uint8_t count) {
    if (count == 0) { fetechedValue = 0x0000; return; }                                                         // 0x0000
    if (count == 1) { fetechedValue = read(regs.programCounter++); return; }                                    // 0x00xx
    if (count == 2) { fetechedValue = read(regs.programCounter++) | read(regs.programCounter) << 8; return; }   // 4660 or 0x1234 in little endian is 0x34 0x12 so we "bitwise or" the first byte with the second one shifted left 8 bytes to get back our 0x1234 (4660)
}

/* #region Instructions */

void CPU::ADC_A_0HL() {
    uint16_t result = regs.af.accumulator + read(regs.hl.value);
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::NOP() {
    // No OP'ing is so lame :cry_tear:
    std::cout << "We NOP'd... So lame!" << std::endl;
}

/* #endregion */