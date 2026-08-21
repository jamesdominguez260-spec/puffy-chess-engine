#include <array>
#include <string>
#include <cstdint>

namespace chess {
    using u64 = std::uint64_t;
    using u16 = std::uint16_t;
    using u8 = std::uint8_t;

    using Bitboard = u64;

    enum Color : u8 {
        WHITE,
        BLACK
    };

    enum PieceType : u8 {
        PAWN = 1U,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };

    enum Piece : u8 {
        WHITE,
        WHITE
    }

    

    namespace constants {
        const Bitboard RANK_1 = 0x00000000000000ffULL;
        const Bitboard RANK_2 = 0x000000000000ff00ULL;
        const Bitboard RANK_3 = 0x0000000000ff0000ULL;
        const Bitboard RANK_4 = 0x00000000ff000000ULL;
        const Bitboard RANK_5 = 0x000000ff00000000ULL;
        const Bitboard RANK_6 = 0x0000ff0000000000ULL;
        const Bitboard RANK_7 = 0x00ff000000000000ULL;
        const Bitboard RANK_8 = 0xff00000000000000ULL;
    }

    struct Position {
        std::array<Piece, 64> board;
        std::array<Bitboard, 12> pieces;
        
        std::string fen();
    };
    struct Move {
        u16 data;
    };
}