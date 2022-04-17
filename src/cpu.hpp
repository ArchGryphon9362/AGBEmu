#ifndef CPU_HPP_
#define CPU_HPP_

#include <string>
#include <cstdint>
#include <vector>

class Bus;

// addressing modes:
//   - imp                              ()
//   - pfx                              ()
//   - imm 8bit                         (d8)
//   - imm 16bit                        (d16) le (aka messed up order)
//   - imm 8bit, signed (1byte/0xNN)    (r8)
//   - abx 8bit addr (0xFFNN)           (a8)
//   - abx 16bit addr (0xNNNN)          (a16)

class CPU {
    public:
        CPU();
        ~CPU();
        void clock();
        void ConnectBus(Bus *n) { bus = n; }
    private:
        struct Registers
        {
            union {
                struct {
                    uint8_t accumulator : 8;
                    uint8_t unused_1 : 1;
                    uint8_t z : 1; // Zero
                    uint8_t n : 1; // Subtraction (BCD)
                    uint8_t h : 1; // Half-Carry (BCD)
                    uint8_t c : 1; // Carry
                    uint8_t unused_2 : 3;
                };
                uint16_t value;
            } af; // a + flags register
            
            union {
                struct {
                    uint8_t b : 8;
                    uint8_t c : 8;
                };
                uint16_t value;
            } bc; // b + c register
            
            union {
                struct {
                    uint8_t d : 8;
                    uint8_t e : 8;
                };
                uint16_t value;
            } de; // d + e register
            
            union {
                struct {
                    uint8_t h : 8;
                    uint8_t l : 8;
                };
                uint16_t value;
            } hl; // high low register

            uint16_t stackPointer;
            uint16_t programCounter;
        };
        typedef enum {
            IMP,        // implied, we don't need any parameters                                            ()
            PFX,        // prefix, we need to fetch next instruction which won't need any params either     ()
            IMM_8U,     // immediate 8 bit, next byte after instruction is the parameter                    (d8)
            IMM_16,     // immediate 16 bit, next 2 bytes after ins are the args                            (d16)
            REL,        // relative to current position address                                             (r8)
            ABS_8,      // absolute 8 bit, fetch arg and convert address to last page                       (a8)
            ABS_16      // absolute 16 bit address                                                          (a16)
        } ARG;
        
        Registers regs;
        Bus *bus = nullptr;
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        uint8_t opcode = 0x00;
        uint8_t cycles = 0;

        struct Instruction {
            std::string name;		
            void (CPU::*operate)(void) = nullptr;
            ARG argumentMode;
            uint8_t cycles = 0;
        };

        std::vector<Instruction> lookup;
        void doPrefix();

        void fetch();
        uint8_t fetechedValue = 0x00;

        /* #region Instructions */

        void NOP();   //

        /* #endregion */
};

#endif