#pragma once

#include <cstdint>
#include <stdexcept>

class Board {
 public:
  // Check if a given player has won
  bool checkWin(const int playerNum) const;

  // Check if a drop at a given x-value (0-6) is valid. That is, check if that
  // column is full.
  bool isValidDrop(const int xPos) const;

  // Make a drop at the given x-value (0-6). Update the corresponding player's
  // board.
  void makeDrop(const int xPos, const int playerNum);

  // Get the total number of pieces placed on the board
  int getTotalPiecesPlaced() const { return totalPiecesPlaced; };

  // Get a string representation of the board.
  std::string display() const;

 private:
  /*
    Board is represented as:
    35 36 37 38 39 40 41
    28 29 30 31 32 33 34
    21 22 23 24 25 26 27
    14 15 16 17 18 19 20
    7  8  9  10 11 12 13
    0  1  2  3  4  5  6

    Player's pieces are represented as unsigned 64-bit integers, where the least
    significant bit is position 0, and the most significant is position 41.
   */
  uint64_t player1Board = 0ULL;
  uint64_t player2Board = 0ULL;
  int totalPiecesPlaced = 0;
};