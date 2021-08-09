#pragma once

#include "tester.h"

class KingMoves : public ITask {
    virtual std::vector<std::string> Run(std::vector<std::string> data) {
        int position = std::atoi(data.at(0).c_str());
        unsigned long bitPosition = (unsigned long) 1 << position;
        unsigned long bitPositionNoA = bitPosition & 0xfefefefefefefefe;
        unsigned long bitPositionNoH = bitPosition & 0x7f7f7f7f7f7f7f7f;
        unsigned long bitMoves = (bitPositionNoA << 7) | (bitPosition << 8) | (bitPositionNoH << 9) |
                                 (bitPositionNoA >> 1) | (bitPositionNoH << 1) |
                                 (bitPositionNoA >> 9) | (bitPosition >> 8) | (bitPositionNoH >> 7);
        return {std::to_string(countBits(bitMoves)), std::to_string(bitMoves)};
    };

private:
    int countBits(unsigned long number) {
        int counter = 0;
        while (number > 0) {
            counter++;
            number &= number - 1;
        }
        return counter;
    }
};