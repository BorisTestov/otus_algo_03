#pragma once

#include "tester.h"

class KnightMoves : public ITask {
    virtual std::vector<std::string> Run(std::vector<std::string> data) {
        int position = std::atoi(data.at(0).c_str());
        unsigned long bitPosition = (unsigned long) 1 << position;
        unsigned long bitPositionNoA = bitPosition & 0xfefefefefefefefe;
        unsigned long bitPositionNoH = bitPosition & 0x7f7f7f7f7f7f7f7f;
        unsigned long bitPositionNoAB = bitPosition & 0xfcfcfcfcfcfcfcfc;
        unsigned long bitPositionNoGH = bitPosition & 0x3f3f3f3f3f3f3f3f;
        unsigned long bitMoves = (bitPositionNoA << 15) | (bitPositionNoH << 17) |
                                 (bitPositionNoAB << 6) | (bitPositionNoGH << 10) |
                                 (bitPositionNoAB >> 10) | (bitPositionNoGH >> 6) |
                                 (bitPositionNoA >> 17) | (bitPositionNoH >> 15);
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