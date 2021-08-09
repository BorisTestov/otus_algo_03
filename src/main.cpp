#include "tester.h"
#include "kingmoves.h"

int main() {
    auto kingTask = std::make_shared<KingMoves>();
    Tester kingTester(kingTask, "../tests/1.Bitboard - Король");
    kingTester.RunTests(false, true);
    return 0;
}
