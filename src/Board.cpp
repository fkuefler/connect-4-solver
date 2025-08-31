#include "Board.h"

#include <cstdint>
#include <stdexcept>
#include <string>

bool Board::checkWin(const int playerNum) const {
  /*
  Board is represented as:
  35 36 37 38 39 40 41
  28 29 30 31 32 33 34
  21 22 23 24 25 26 27
  14 15 16 17 18 19 20
  7  8  9  10 11 12 13
  0  1  2  3  4  5  6

  The board is represented using the 42 least significant bits of an unsigned
  64-bit integer. The least significant bit represents pos 0, and the 42nd least
  significant bit represents pos 41.
  */
  const uint64_t playerBoard = (playerNum == 1) ? player1Board : player2Board;

  for (int i = 41; i >= 0; i--) {
    if (!(playerBoard & (1ULL << i))) {
      continue;  // No piece at this position, can skip win checks here
    }
    if (i > 20) {
      // Check vertical win
      if (playerBoard & (1ULL << i) && playerBoard & (1ULL << (i - 7)) &&
          playerBoard & (1ULL << (i - 14)) &&
          playerBoard & (1ULL << (i - 21))) {
        return true;
      }
      if (i % 7 > 2) {
        // Check anti-diagonal win
        if (playerBoard & (1ULL << i) && playerBoard & (1ULL << (i - 8)) &&
            playerBoard & (1ULL << (i - 16)) &&
            playerBoard & (1ULL << (i - 24))) {
          return true;
        }
      }
      if (i % 7 < 4) {
        // Check diagonal win
        if (playerBoard & (1ULL << i) && playerBoard & (1ULL << (i - 6)) &&
            playerBoard & (1ULL << (i - 12)) &&
            playerBoard & (1ULL << (i - 18))) {
          return true;
        }
      }
    }
    if (i % 7 > 2) {
      // Check horizontal win
      if (playerBoard & (1ULL << i) && playerBoard & (1ULL << (i - 1)) &&
          playerBoard & (1ULL << (i - 2)) && playerBoard & (1ULL << (i - 3))) {
        return true;
      }
    }
  }
  return false;  // No win found
}

bool Board::isValidDrop(const int xPos) const {
  return !(1ULL << (xPos + 35) & (player1Board | player2Board));
}

void Board::makeDrop(const int xPos, const int playerNum) {
  if (xPos > 6) {
    throw std::runtime_error("xPos can be greater than 6");
  }
  if (totalPiecesPlaced > 42) {
    throw std::runtime_error("Board full");
  }
  if (!isValidDrop(xPos)) {
    throw std::runtime_error("Can't drop at " + xPos);
  }

  for (int i = 0; i < 6; i++) {
    if (!((1ULL << (xPos + (i * 7))) & (player1Board | player2Board))) {
      if (playerNum == 1) {
        player1Board |= 1ULL << (xPos + (i * 7));
        totalPiecesPlaced++;
        return;
      } else if (playerNum == 2) {
        player2Board |= 1ULL << (xPos + (i * 7));
        totalPiecesPlaced++;
        return;
      } else {
        throw std::runtime_error("Invalid player number " +
                                 std::to_string(playerNum));
      }
    }
  }
  throw std::runtime_error("Couldn't make drop at pos " + std::to_string(xPos));
}

std::string Board::display() const {
  std::string display;
  for (int row = 5; row >= 0; row--) {
    display += "| ";
    for (int col = 0; col < 7; col++) {
      if (player1Board & (1ULL << (col + (row * 7)))) {
        display += "\033[34m● \033[0m";
      } else if (player2Board & (1ULL << (col + (row * 7)))) {
        display += "\033[31m● \033[0m";
      } else {
        display += "· ";
      }
    }
    display += " |\n";
  }
  display += "|________________|\n  1 2 3 4 5 6 7\n";
  return display;
}
