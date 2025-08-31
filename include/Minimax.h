#pragma once

#include "Board.h"

class Minimax {
 public:
  // Find the best move for the current player
  static int findBestMove(const Board board, const int playerNum,
                          const int maxDepth);

  // Minimax connect-4 algorithm with alpha-beta pruning
  static int minimax(const Board board, const int currentPlayerNum,
                     const int maximizingPlayerNum, const bool isMaximizing,
                     const int depth, const int maxDepth, const int alpha,
                     const int beta);

  // Evaluate the board and return a score
  static int evaluateBoard(const Board board, const int playerNum,
                           const int depth);
};