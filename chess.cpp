#include <array>
#include <cstdint>

struct Position {
    std::array<Piece, 64> boardMB;
    std::array<std::uint64_t, 12> piecesBB;
}