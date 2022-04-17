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
        
        Registers regs;
        Bus *bus = nullptr;
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        uint8_t opcode = 0x00;
        uint8_t cycles = 0;

        struct Instruction {
            std::string name;		
            void (CPU::*operate)(void) = nullptr;
            uint8_t argLength;
            uint8_t cycles = 0;
        };

        std::vector<Instruction> lookup;
        void doPrefix();

        void fetch(uint8_t count);
        uint16_t fetechedValue = 0x0000; // usually will be 8 bytes but sometimes may be 16 so keeping this a uint16

        /* #region Instructions */

//      x0              x1                  x2                  x3              x4              x5              x6              x7              x8                  x9                  xA                  xB              xC              xD              xE              xF
/*0x*/  void NOP();     void LD_BC_X();     void LD_0BC_A();    void INC_BC();  void INC_B();   void DEC_B();   void LD_B_X();  void RLCA();    void LD_0X_SP();    void ADD_HL_BC();   void LD_A_0BC();    void DEC_BC();  void INC_C();   void DEC_C();   void LD_C_X();  void RRCA();
/*1x*/  void STOP();    void LD_DE_X();     void LD_0DE_A();    void INC_DE();  void INC_D();   void DEC_D();   void LD_D_X();  void RLA();     void JR_X();        void ADD_HL_DE();   void LD_A_0DE();    void DEC_DE();  void INC_E();   void DEC_E();   void LD_E_X();  void RRA();
/*2x*/  

        /* #endregion */
};

#endif