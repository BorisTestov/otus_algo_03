#pragma once

#include "tester.h"

class BishopMoves : public ITask {
    virtual std::vector<std::string> Run(std::vector<std::string> data) {
        int position = std::atoi(data.at(0).c_str());
        unsigned long bitPosition = (unsigned long) 1 << position;
        unsigned long bitMoves = 0;

// Down left
        bitMoves |= (bitPosition & 0xfefefefefefefefe) >> 9;
        bitMoves |= (bitPosition & 0xfcfcfcfcfcfcfcfc) >> 18;
        bitMoves |= (bitPosition & 0xf8f8f8f8f8f8f8f8) >> 27;
        bitMoves |= (bitPosition & 0xf0f0f0f0f0f0f0f0) >> 36;
        bitMoves |= (bitPosition & 0xe0e0e0e0e0e0e0e0) >> 45;
        bitMoves |= (bitPosition & 0xc0c0c0c0c0c0c0c0) >> 54;
        bitMoves |= (bitPosition & 0x8080808080808080) >> 63;

// Up right
        bitMoves |= (bitPosition & 0x7f7f7f7f7f7f7f7f) << 9;
        bitMoves |= (bitPosition & 0x3f3f3f3f3f3f3f3f) << 18;
        bitMoves |= (bitPosition & 0x1f1f1f1f1f1f1f1f) << 27;
        bitMoves |= (bitPosition & 0xf0f0f0f0f0f0f0f) << 36;
        bitMoves |= (bitPosition & 0x707070707070707) << 45;
        bitMoves |= (bitPosition & 0x303030303030303) << 54;
        bitMoves |= (bitPosition & 0x101010101010101) << 63;

// Down right
        bitMoves |= (bitPosition & 0x7f7f7f7f7f7f7f7f) >> 7;
        bitMoves |= (bitPosition & 0x3f3f3f3f3f3f3f3f) >> 14;
        bitMoves |= (bitPosition & 0x1f1f1f1f1f1f1f1f) >> 21;
        bitMoves |= (bitPosition & 0xf0f0f0f0f0f0f0f) >> 28;
        bitMoves |= (bitPosition & 0x707070707070707) >> 35;
        bitMoves |= (bitPosition & 0x303030303030303) >> 42;
        bitMoves |= (bitPosition & 0x101010101010101) >> 49;
//
// Up left
        bitMoves |= (bitPosition & 0xfefefefefefefefe) << 7;
        bitMoves |= (bitPosition & 0xfcfcfcfcfcfcfcfc) << 14;
        bitMoves |= (bitPosition & 0xf8f8f8f8f8f8f8f8) << 21;
        bitMoves |= (bitPosition & 0xf0f0f0f0f0f0f0f0) << 28;
        bitMoves |= (bitPosition & 0xe0e0e0e0e0e0e0e0) << 35;
        bitMoves |= (bitPosition & 0xc0c0c0c0c0c0c0c0) << 42;
        bitMoves |= (bitPosition & 0x8080808080808080) << 49;
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