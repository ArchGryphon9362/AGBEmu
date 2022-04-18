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
    if (count == 0) { fetchedValue = 0x0000; return; }                                                         // 0x0000
    if (count == 1) { fetchedValue = read(regs.programCounter++); return; }                                    // 0x00xx
    if (count == 2) { fetchedValue = read(regs.programCounter++) | read(regs.programCounter) << 8; return; }   // 4660 or 0x1234 in little endian is 0x34 0x12 so we "bitwise or" the first byte with the second one shifted left 8 bytes to get back our 0x1234 (4660)
}

/* #region Instructions */

void CPU::ADC_A_0HL() {
    uint16_t result = regs.af.accumulator + read(regs.hl.value) + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_A() {
    uint16_t result = regs.af.accumulator + regs.af.accumulator + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_B() {
    uint16_t result = regs.af.accumulator + regs.bc.b + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_C() {
    uint16_t result = regs.af.accumulator + regs.bc.c + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_D() {
    uint16_t result = regs.af.accumulator + regs.de.d + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_E() {
    uint16_t result = regs.af.accumulator + regs.de.e + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_H() {
    uint16_t result = regs.af.accumulator + regs.hl.h + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_L() {
    uint16_t result = regs.af.accumulator + regs.hl.l + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADC_A_X() {
    uint16_t result = regs.af.accumulator + fetchedValue + regs.af.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_0HL() {
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

void CPU::ADD_A_A() {
    uint16_t result = regs.af.accumulator + regs.af.accumulator;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_B() {
    uint16_t result = regs.af.accumulator + regs.bc.b;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_C() {
    uint16_t result = regs.af.accumulator + regs.bc.c;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_D() {
    uint16_t result = regs.af.accumulator + regs.de.d;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_E() {
    uint16_t result = regs.af.accumulator + regs.de.e;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_H() {
    uint16_t result = regs.af.accumulator + regs.hl.h;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_L() {
    uint16_t result = regs.af.accumulator + regs.hl.l;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_A_X() {
    uint16_t result = regs.af.accumulator + fetchedValue;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.af.accumulator = result;
}

void CPU::ADD_HL_BC() {
    uint32_t result = regs.hl.value + regs.bc.value;
    
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (result & 0x01 << 12) regs.af.h = 0x01;
    if (result & 0x01 << 16) regs.af.c = 0x01;

    regs.hl.value = result;
}

void CPU::ADD_HL_DE() {
    uint32_t result = regs.hl.value + regs.de.value;
    
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (result & 0x01 << 12) regs.af.h = 0x01;
    if (result & 0x01 << 16) regs.af.c = 0x01;

    regs.hl.value = result;
}

void CPU::ADD_HL_HL() {
    uint32_t result = regs.hl.value + regs.hl.value;
    
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (result & 0x01 << 12) regs.af.h = 0x01;
    if (result & 0x01 << 16) regs.af.c = 0x01;

    regs.hl.value = result;
}

void CPU::ADD_HL_SP() {
    uint32_t result = regs.hl.value + regs.stackPointer;
    
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (result & 0x01 << 12) regs.af.h = 0x01;
    if (result & 0x01 << 16) regs.af.c = 0x01;

    regs.hl.value = result;
}

void CPU::ADD_SP_X() {
    uint16_t result = regs.stackPointer + fetchedValue;
    
    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (result & 0x01 << 4) regs.af.h = 0x01;
    if (result & 0x01 << 8) regs.af.c = 0x01;

    regs.stackPointer = result;
}

void CPU::AND_0HL() {
    uint8_t result = regs.af.accumulator & read(regs.hl.value);

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_A() {
    uint8_t result = regs.af.accumulator & regs.af.accumulator;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_B() {
    uint8_t result = regs.af.accumulator & regs.bc.b;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_C() {
    uint8_t result = regs.af.accumulator & regs.bc.c;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_D() {
    uint8_t result = regs.af.accumulator & regs.de.d;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_E() {
    uint8_t result = regs.af.accumulator & regs.de.e;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_H() {
    uint8_t result = regs.af.accumulator & regs.hl.h;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_L() {
    uint8_t result = regs.af.accumulator & regs.hl.l;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::AND_X() {
    uint8_t result = regs.af.accumulator & fetchedValue;

    regs.af.z = 0x00;
    regs.af.n = 0x00;
    regs.af.h = 0x01;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;

    regs.af.accumulator = result;
}

void CPU::CALL_C_X() {
    if (regs.af.c) {
        cycles += 3;

        write(--regs.stackPointer, (regs.programCounter & 0b1111111100000000) >> 8); // push high byte onto stack
        write(--regs.stackPointer,  regs.programCounter & 0b0000000011111111);       // push low byte onto stack

        regs.programCounter = fetchedValue;
    }
}

void CPU::CALL_NC_X() {
    if (!regs.af.c) {
        cycles += 3;

        write(--regs.stackPointer, (regs.programCounter & 0b1111111100000000) >> 8); // push high byte onto stack
        write(--regs.stackPointer,  regs.programCounter & 0b0000000011111111);       // push low byte onto stack

        regs.programCounter = fetchedValue;
    }
}

void CPU::CALL_NZ_X() {
    if (!regs.af.z) {
        cycles += 3;

        write(--regs.stackPointer, (regs.programCounter & 0b1111111100000000) >> 8); // push high byte onto stack
        write(--regs.stackPointer,  regs.programCounter & 0b0000000011111111);       // push low byte onto stack

        regs.programCounter = fetchedValue;
    }
}

void CPU::CALL_X() {
    write(--regs.stackPointer, (regs.programCounter & 0b1111111100000000) >> 8); // push high byte onto stack
    write(--regs.stackPointer,  regs.programCounter & 0b0000000011111111);       // push low byte onto stack

    regs.programCounter = fetchedValue;
}

void CPU::CALL_Z_X() {
    if (regs.af.z) {
        cycles += 3;

        write(--regs.stackPointer, (regs.programCounter & 0b1111111100000000) >> 8); // push high byte onto stack
        write(--regs.stackPointer,  regs.programCounter & 0b0000000011111111);       // push low byte onto stack

        regs.programCounter = fetchedValue;
    }
}

void CPU::NOP() {
    // No OP'ing is so lame :cry_tear:
    std::cout << "We NOP'd... So lame!" << std::endl;
}

/* #endregion */