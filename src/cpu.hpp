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
                    uint8_t n : 1; // Subtraction (Used For BCD)
                    uint8_t h : 1; // Half-Carry (Used For BCD)
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

        uint8_t IME = 0x00;
        uint8_t scheduleIME = 0x00;
        
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
/*      x0                  x1                  x2                  x3                  x4                  x5                  x6                  x7                  x8                  x9                  xA                  xB              xC                  xD              xE                  xF              */
/*0x*/  void NOP();         void LD_BC_X();     void LD_0BC_A();    void INC_BC();      void INC_B();       void DEC_B();       void LD_B_X();      void RLCA();        void LD_0X_SP();    void ADD_HL_BC();   void LD_A_0BC();    void DEC_BC();  void INC_C();       void DEC_C();   void LD_C_X();      void RRCA();
/*1x*/  void STOP();        void LD_DE_X();     void LD_0DE_A();    void INC_DE();      void INC_D();       void DEC_D();       void LD_D_X();      void RLA();         void JR_X();        void ADD_HL_DE();   void LD_A_0DE();    void DEC_DE();  void INC_E();       void DEC_E();   void LD_E_X();      void RRA();
/*2x*/  void JR_NZ_X();     void LD_HL_X();     void LD_0HLI_A();   void INC_HL();      void INC_H();       void DEC_H();       void LD_H_X();      void DAA();         void JR_Z_X();      void ADD_HL_HL();   void LD_A_0HLI();   void DEC_HL();  void INC_L();       void DEC_L();   void LD_L_X();      void CPL();
/*3x*/  void JR_NC_X();     void LD_SP_X();     void LD_0HLD_A();   void INC_SP();      void INC_0HL();     void DEC_0HL();     void LD_0HL_X();    void SCF();         void JR_C_X();      void ADD_HL_SP();   void LD_A_0HLD();   void DEC_SP();  void INC_A();       void DEC_A();   void LD_A_X();      void CCF();
/*4x*/  void LD_B_B();      void LD_B_C();      void LD_B_D();      void LD_B_E();      void LD_B_H();      void LD_B_L();      void LD_B_0HL();    void LD_B_A();      void LD_C_B();      void LD_C_C();      void LD_C_D();      void LD_C_E();  void LD_C_H();      void LD_C_L();  void LD_C_0HL();    void LD_C_A();
/*5x*/  void LD_D_B();      void LD_D_C();      void LD_D_D();      void LD_D_E();      void LD_D_H();      void LD_D_L();      void LD_D_0HL();    void LD_D_A();      void LD_E_B();      void LD_E_C();      void LD_E_D();      void LD_E_E();  void LD_E_H();      void LD_E_L();  void LD_E_0HL();    void LD_E_A();
/*6x*/  void LD_H_B();      void LD_H_C();      void LD_H_D();      void LD_H_E();      void LD_H_H();      void LD_H_L();      void LD_H_0HL();    void LD_H_A();      void LD_L_B();      void LD_L_C();      void LD_L_D();      void LD_L_E();  void LD_L_H();      void LD_L_L();  void LD_L_0HL();    void LD_L_A();
/*7x*/  void LD_0HL_B();    void LD_0HL_C();    void LD_0HL_D();    void LD_0HL_E();    void LD_0HL_H();    void LD_0HL_L();    void HALT();        void LD_0HL_A();    void LD_A_B();      void LD_A_C();      void LD_A_D();      void LD_A_E();  void LD_A_H();      void LD_A_L();  void LD_A_0HL();    void LD_A_A();
/*8x*/  void ADD_A_B();     void ADD_A_C();     void ADD_A_D();     void ADD_A_E();     void ADD_A_H();     void ADD_A_L();     void ADD_A_0HL();   void ADD_A_A();     void ADC_A_B();     void ADC_A_C();     void ADC_A_D();     void ADC_A_E(); void ADC_A_H();     void ADC_A_L(); void ADC_A_0HL();   void ADC_A_A();
/*9x*/  void SUB_B();       void SUB_C();       void SUB_D();       void SUB_E();       void SUB_H();       void SUB_L();       void SUB_0HL();     void SUB_A();       void SBC_A_B();     void SBC_A_C();     void SBC_A_D();     void SBC_A_E(); void SBC_A_H();     void SBC_A_L(); void SBC_A_0HL();   void SBC_A_A();
/*Ax*/  void AND_B();       void AND_C();       void AND_D();       void AND_E();       void AND_H();       void AND_L();       void AND_0HL();     void AND_A();       void XOR_B();       void XOR_C();       void XOR_D();       void XOR_E();   void XOR_H();       void XOR_L();   void XOR_0HL();     void XOR_A();
/*Bx*/  void OR_B();        void OR_C();        void OR_D();        void OR_E();        void OR_H();        void OR_L();        void OR_0HL();      void OR_A();        void CP_B();        void CP_C();        void CP_D();        void CP_E();    void CP_H();        void CP_L();    void CP_0HL();      void CP_A();
/*Cx*/  void RET_NZ();      void POP_BC();      void JP_NZ_X();     void JP_X();        void CALL_NZ_X();   void PUSH_BC();     void ADD_A_X();     void RST_00();      void RET_Z();       void RET();         void JP_Z_X();      void PFX();     void CALL_Z_X();    void CALL_X();  void ADC_A_X();     void RST_08();
/*Dx*/  void RET_NC();      void POP_DE();      void JP_NC_X();     /* Illegal */       void CALL_NC_X();   void PUSH_DE();     void SUB_X();       void RST_10();      void RET_C();       void RETI();        void JP_C_X();      /* Illegal */   void CALL_C_X();    /* Illegal */   void SBC_A_X();     void RST_18();
/*Ex*/  void LDH_0X_A();    void POP_HL();      void LD_0C_A();     /* Illegal */       /* Illegal */       void PUSH_HL();     void AND_X();       void RST_20();      void ADD_SP_X();    void JP_HL();       void LD_0X_A();     /* Illegal */   /* Illegal */       /* Illegal */   void XOR_X();       void RST_28();
/*Fx*/  void LDH_A_0X();    void POP_AF();      void LD_A_0C();     void DI();          /* Illegal */       void PUSH_AF();     void OR_X();        void RST_30();      void LD_HL_SP_X();  void LD_SP_HL();    void LD_A_0X();     void EI();      /* Illegal */       /* Illegal */   void CP_X();        void RST_38();
        /* #endregion */
};

#endif