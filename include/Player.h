#pragma once

#include <cstdint>

#include "Board.h"

class Player {
 public:
  Player(int num) : playerBoard(0ULL), playerNum(num) {}

  uint64_t getBoard() const { return playerBoard; }
  int getPlayerNum() const { return playerNum; }

 private:
  uint64_t playerBoard;
  int playerNum;
};

class HumanPlayer : public Player {
 public:
  using Player::Player;
  // Get the human player's move
  int getMove() const;
};

class ComputerPlayer : public Player {
 public:
  using Player::Player;
  // Get the computer player's move
  int getMove(const Board board, const int playerNum, const int maxDepth) const;
};