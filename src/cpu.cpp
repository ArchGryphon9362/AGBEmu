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

void CPU::CCF() {
    regs.af.n = 0x00;
    regs.af.h = 0x00;
    regs.af.c ^= 0x01; // invert carry flag
}

void CPU::CPL() {
    regs.af.accumulator = ~regs.af.accumulator;
    regs.af.n = 0x00;
    regs.af.h = 0x00;
}

void CPU::CP_0HL() {
    uint8_t value = read(regs.hl.value);
    uint8_t result = regs.af.accumulator - value;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((value & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (value > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_A() {
    regs.af.z = 0x01;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
}

void CPU::CP_B() {
    uint8_t result = regs.af.accumulator - regs.bc.b;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.bc.b & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.bc.b > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_C() {
    uint8_t result = regs.af.accumulator - regs.bc.c;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.bc.c & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.bc.c > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_D() {
    uint8_t result = regs.af.accumulator - regs.de.d;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.de.d & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.de.d > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_E() {
    uint8_t result = regs.af.accumulator - regs.de.e;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.de.e & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.de.e > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_H() {
    uint8_t result = regs.af.accumulator - regs.hl.h;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.hl.h & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.hl.h > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_L() {
    uint8_t result = regs.af.accumulator - regs.hl.l;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((regs.hl.l & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (regs.hl.l > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::CP_X() {
    uint8_t result = regs.af.accumulator - fetchedValue;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;
    regs.af.c = 0x00;
    
    if (!result) regs.af.z = 0x01;
    if ((fetchedValue & 0b1111) > (regs.af.accumulator & 0b1111)) regs.af.h = 0x01;
    if (fetchedValue > regs.af.accumulator) regs.af.c = 0x01;
}

void CPU::DAA() {
    uint16_t value = regs.af.accumulator;
    uint8_t lsb = value & 0x0F;
    uint8_t msb = (value & 0xF0) >> 4;

    if (!regs.af.n) {
        if (lsb > 9 || regs.af.h) {
            lsb += 0x06;
            
            if (lsb & 0x01 << 4) {
                msb++;
                if (msb & 0x01 << 4) regs.af.c = 0x01; // if we overflowed set carry
            }
            
            lsb &= 0xF;
        }

        if (msb > 9 || regs.af.c) {
            regs.af.c = 0x01;
            msb += 0x06;
            msb &= 0xF;
        }
    } else {
        if (regs.af.c) {
            msb = ~msb & 0xF;
            lsb = (~lsb & 0xF) + 0x01;
        }
        
        if (lsb > 9) {
            lsb -= 0x06;
        }
    }

    regs.af.z = 0x00;
    regs.af.h = 0x00;
    regs.af.accumulator = (msb << 4) | (lsb);

    if (!regs.af.accumulator) regs.af.z = 0x01;
}

void CPU::DEC_0HL() {
    uint8_t currentValue = read(regs.hl.value);
    write(regs.hl.value, currentValue - 1);

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_A() {
    uint8_t currentValue = regs.af.accumulator;
    regs.af.accumulator = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_B() {
    uint8_t currentValue = regs.bc.b;
    regs.bc.b = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_BC() {
    uint16_t currentValue = regs.bc.value;
    regs.bc.value = currentValue - 1;
}

void CPU::DEC_C() {
    uint8_t currentValue = regs.bc.c;
    regs.bc.c = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_D() {
    uint8_t currentValue = regs.de.d;
    regs.de.d = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_DE() {
    uint16_t currentValue = regs.de.value;
    regs.de.value = currentValue - 1;
}

void CPU::DEC_E() {
    uint8_t currentValue = regs.de.e;
    regs.de.e = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_H() {
    uint8_t currentValue = regs.hl.h;
    regs.hl.h = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_HL() {
    uint16_t currentValue = regs.hl.value;
    regs.hl.value = currentValue - 1;
}

void CPU::DEC_L() {
    uint8_t currentValue = regs.hl.l;
    regs.hl.l = currentValue - 1;

    regs.af.z = 0x00;
    regs.af.n = 0x01;
    regs.af.h = 0x00;

    if (!regs.af.accumulator) regs.af.z = 0x01;
    if ((currentValue - 1 & 0b1111) > (currentValue & 0b1111)) regs.af.h = 0x01;
}

void CPU::DEC_SP() {
    uint16_t currentValue = regs.stackPointer;
    regs.stackPointer = currentValue - 1;
}

void CPU::DI() {
    IME = 0x00;
}

void CPU::EI() {
    scheduleIME = 0x01;
}

void CPU::HALT() {

}

void CPU::NOP() {
    // No OP'ing is so lame :cry_tear:
    std::cout << "We NOP'd... So lame!" << std::endl;
}

/* #endregion */

void CPU::testCPU() {
    regs.af.accumulator = 0x53;
    regs.bc.b = 0x29;

    ADD_A_B();
    DAA();

    std::cout << std::to_string(regs.af.accumulator) << std::endl;
}