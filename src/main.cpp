#include "tester.h"
#include "kingmoves.h"
#include "knightmoves.h"
#include "rookmoves.h"
#include "bishopmoves.h"
#include "queenmoves.h"

int main() {
    auto kingTask = std::make_shared<KingMoves>();
    auto knightTask = std::make_shared<KnightMoves>();
    auto rookTask = std::make_shared<RookMoves>();
    auto bishopTask = std::make_shared<BishopMoves>();
    auto queenTask = std::make_shared<QueenMoves>();
    Tester kingTester(kingTask, "../tests/1.Bitboard - Король");
    Tester knightTester(knightTask, "../tests/2.Bitboard - Конь");
    Tester rookTester(rookTask, "../tests/3.Bitboard - Ладья");
    Tester bishopTester(bishopTask, "../tests/4.Bitboard - Слон");
    Tester queenTester(queenTask, "../tests/5.Bitboard - Ферзь");
    queenTester.RunTests(false, true);
    return 0;
}
