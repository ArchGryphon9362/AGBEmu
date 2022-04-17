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
    private:
        CPU cpu;
        std::array<uint8_t, 32 * 1024> ram;
};

#endif