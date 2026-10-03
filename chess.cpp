#pragma once
#include <cstdint>
#include <array>
#include <bit>
#include <stdexcept>
#include <concepts>

namespace chess {
    using u64 = std::uint64_t;
    using u32 = std::uint32_t;
    using u16 = std::uint16_t;
    using u8 = std::uint8_t;
    using Bitboard = u64;

    enum class Color : u8 {
        WHITE,
        BLACK
    };

    enum class PieceType : u8 {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };

    enum class Piece : u8 {
        WHITE_PAWN,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_ROOK,
        WHITE_QUEEN,
        WHITE_KING,
        BLACK_PAWN,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_ROOK,
        BLACK_QUEEN,
        BLACK_KING,
        NO_PIECE
    };

    enum class Square : u8 {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        NO_SQUARE
    };

    enum class MoveType : u8;

    namespace constants {
        inline std::array<Bitboard, 128> PAWN_ATTACKS_BB;
        inline std::array<Bitboard, 64> KNIGHT_ATTACKS_BB;
        inline std::array<Bitboard, 64> KING_ATTACKS_BB;
    }

    constexpr Bitboard squareBB(Square square) noexcept {
        if (square == Square::NO_SQUARE) {
            return 0ULL;
        }
        return 1ULL << static_cast<u64>(square);
    };

    template<typename T>
    constexpr T getLsb(auto value) noexcept {
        return static_cast<T>(std::countr_zero(value));
    }

    template<typename T>
    constexpr T popLsb(auto& value) noexcept {
        T lsb = getLsb<T>(value);
        value &= value - 1;
        return lsb;
    }

    template<typename T, size_t bufferSize>
    struct List {
        T m_Data[bufferSize];
        size_t m_Size;

        List(std::initializer_list<T> init) : m_Size(init.size()) {
            if (m_Size > bufferSize) {
                throw std::out_of_range("Initializer list size exceeds buffer size");
            }
            std::copy(init.begin(), init.end(), m_Data);
        }

        List() = default;

        T& operator[](size_t index) noexcept {
            return m_Data[index];
        }

        const T& operator[](size_t index) const noexcept {
            return m_Data[index];
        }

        T& at(size_t index) {
            if (index < m_Size) {
                return m_Data[index];
            }
            throw std::out_of_range("Index out of bounds");
        }

        const T& at(size_t index) const {
            if (index < m_Size) {
                return m_Data[index];
            }
            throw std::out_of_range("Index out of bounds");
        }

        void push_back(const T& value) {
            if (m_Size >= bufferSize) {
                throw std::out_of_range("Buffer size exceeded");
            }
            m_Data[m_Size++] = value;
        }

        void push_back(T&& value) {
            if (m_Size >= bufferSize) {
                throw std::out_of_range("Buffer size exceeded");
            }
            m_Data[m_Size++] = std::move(value);
        }

        constexpr T* begin() noexcept {
            return m_Data;
        }

        constexpr const T* begin() const noexcept {
            return m_Data;
        }

        constexpr const T* cbegin() const noexcept {
            return m_Data;
        }

        constexpr T* end() noexcept {
            return m_Data + m_Size;
        }
        
        constexpr const T* end() const noexcept {
            return m_Data + m_Size;
        }

        constexpr const T* cend() const noexcept {
            return m_Data + m_Size;
        }
    };

    struct Move {
        Move() = default;
        Move(u16 d) : data(d) {}
        Move(Square from, Square to, MoveType type) : data(static_cast<u16>(type) << 12 | static_cast<u16>(from) << 6 | static_cast<u16>(to)) {}

        constexpr Square from() const noexcept {
            return static_cast<Square>((data >> 6) & 0x3f);
        }

        constexpr Square to() const noexcept {
            return static_cast<Square>(data & 0x3f);
        }

        constexpr MoveType type() const noexcept {
            return static_cast<MoveType>(data >> 12);
        }

        constexpr u16 raw() const noexcept {
            return data;
        }

        u16 data;
    };

    struct Position {
        using MoveList = List<Move, 256>;

        Position(std::string fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        void doMove(const Move& move) noexcept;
        void undoMove() noexcept;

        Piece& pieceAt(Square square) noexcept {
            return board[static_cast<size_t>(square)];
        }

        const Piece& pieceAt(Square square) const noexcept {
            return board[static_cast<size_t>(square)];
        }

        MoveList generateMoves() const noexcept {
            MoveList moves;

            Bitboard pawns;
            Bitboard knights;
            Bitboard bishops;
            Bitboard queens;
            Bitboard rooks;
            Bitboard king;

            while (pawns) {
                Square from = popLsb<Square>(pawns);
                // Generate pawn moves for the square 'from'
            }

            while (knights) {
                Square from = popLsb<Square>(knights);
                // Generate knight moves for the square 'from'
            }

            while (bishops) {
                Square from = popLsb<Square>(bishops);
                // Generate bishop moves for the square 'from'
            }

            while (queens) {
                Square from = popLsb<Square>(queens);
                // Generate queen moves for the square 'from'
            }

            while (rooks) {
                Square from = popLsb<Square>(rooks);
                // Generate rook moves for the square 'from'
            }

            while (king) {
                Square from = popLsb<Square>(king);
                // Generate king moves for the square 'from'
            }

            return moves;
        }

        MoveList generateLegalMoves() const noexcept;

        std::array<Bitboard, 12> pieceBitboards;
        std::array<Piece, 64> board;

        Color sideToMove;
    };

    u64 perft(Position& pos, int depth) {
        if (depth == 0) {
            return 1ULL;
        }

        Position::MoveList moves = pos.generateLegalMoves();

        u64 nodes = 0ULL;

        for (const Move& move : moves) {
            pos.doMove(move);
            nodes += perft(pos, depth - 1);
            pos.undoMove();
        }

        return nodes;
    } 

}
