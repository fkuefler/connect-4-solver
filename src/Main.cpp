#include <cstdint>
#include <iostream>

#include "Board.h"
#include "Player.h"

#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
  // Set console output to UTF-8 on Windows
#if defined(_WIN32)
  SetConsoleOutputCP(65001);
#endif

  Board board;
  HumanPlayer human(1);
  ComputerPlayer computer(2);

  while (true) {
    // Display the board
    std::cout << "\033[2J\033[H";  // Clear screen and move cursor to top-left
    std::cout << board.display();

    // Get human move
    while (true) {
      int humanMove = human.getMove();
      if (board.isValidDrop(humanMove)) {
        board.makeDrop(humanMove, human.getPlayerNum());
        break;
      } else {
        std::cout << "Invalid move. That column is full. Try again.\n";
      }
    }

    // After a valid move, clear and redraw the board to show the result
    std::cout << "\033[2J\033[H";
    std::cout << board.display();

    // Check for win
    if (board.checkWin(human.getPlayerNum())) {
      std::cout << "\033[2J\033[H";
      std::cout << board.display();
      std::cout << "Human wins!\n";
      break;
    }

    // Get computer move
    int computerMove = computer.getMove(board, computer.getPlayerNum(), 10);
    if (board.isValidDrop(computerMove)) {
      board.makeDrop(computerMove, computer.getPlayerNum());
    } else {
      std::cout << "Invalid move. Try again.\n";
      continue;
    }

    // Check for win
    if (board.checkWin(computer.getPlayerNum())) {
      std::cout << "\033[2J\033[H";
      std::cout << board.display();
      std::cout << "Computer wins!\n";
      break;
    }
  }

  return 0;
}