#ifndef BUS_HPP_
#define BUS_HPP_

#include "cpu.hpp"
#include <array>
#include <cstdint>

class Bus {
    public:
        Bus();
        ~Bus();
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        void clock();
        void testCPU();
    private:
        union Interrupts {
            struct {
                uint8_t vblank : 1;
                uint8_t lcd_stat : 1;
                uint8_t timer : 1;
                uint8_t serial : 1;
                uint8_t joypad : 1;
                uint8_t unused : 3;
            };
            uint8_t value;
        };
        
        CPU cpu;
        std::array<uint8_t, 4 * 1024> ram; // wram 0xC000-0xCFFF
    public:
        Interrupts intFlag;   // requested interrupts
        Interrupts intEnable; // "listening for" interrupts
};

#endif