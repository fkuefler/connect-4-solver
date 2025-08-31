#include "Player.h"

#include <cstdint>
#include <iostream>
#include <limits>

#include "Minimax.h"

int HumanPlayer::getMove() const {
  while (true) {
    int xPos;
    std::cout << "Enter your move (1-7): ";
    std::cin >> xPos;

    if (std::cin.fail() || xPos < 1 || xPos > 7) {
      // Handle invalid input (not a number or out of range)
      std::cout << "Invalid input. Please enter a number between 1 and 7."
                << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      // Valid input, return the 0-indexed column
      return xPos - 1;
    }
  }
}

int ComputerPlayer::getMove(const Board board, const int playerNum,
                            const int maxDepth) const {
  return Minimax::findBestMove(board, playerNum, maxDepth);
}