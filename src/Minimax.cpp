#include "Minimax.h"

#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

int Minimax::evaluateBoard(const Board board, const int maximizingPlayerNum,
                           const int depth) {
  if (board.checkWin(maximizingPlayerNum)) {
    return 100 - depth;
  } else if (board.checkWin(3 - maximizingPlayerNum)) {
    return depth - 100;
  } else {
    return 0;
  }
}

int Minimax::minimax(const Board board, const int currentPlayerNum,
                     const int maximizingPlayerNum, const bool isMaximizing,
                     const int depth, const int maxDepth, const int alpha,
                     const int beta) {
  int score = evaluateBoard(board, maximizingPlayerNum, depth);
  if (score != 0 || depth >= maxDepth) {
    return score;
  }

  if (isMaximizing) {
    int maxEval = -1000;
    int a = alpha;
    for (int col = 0; col < 7; col++) {
      if (board.isValidDrop(col)) {
        Board newBoard = board;
        newBoard.makeDrop(col, currentPlayerNum);
        int eval = minimax(newBoard, 3 - currentPlayerNum, maximizingPlayerNum,
                           false, depth + 1, maxDepth, a, beta);
        maxEval = std::max(maxEval, eval);
        a = std::max(a, eval);
        if (beta <= a) {
          break;  // Beta cut-off
        }
      }
    }
    return maxEval;
  } else {
    int minEval = 1000;
    int b = beta;
    for (int col = 0; col < 7; col++) {
      if (board.isValidDrop(col)) {
        Board newBoard = board;
        newBoard.makeDrop(col, currentPlayerNum);
        int eval = minimax(newBoard, 3 - currentPlayerNum, maximizingPlayerNum,
                           true, depth + 1, maxDepth, alpha, b);
        minEval = std::min(minEval, eval);
        b = std::min(b, eval);
        if (b <= alpha) {
          break;  // Alpha cut-off
        }
      }
    }
    return minEval;
  }
}

int Minimax::findBestMove(const Board board, const int playerNum,
                          const int maxDepth) {
  int bestValue = -1000;
  std::vector<int> bestMoves;

  for (int col = 0; col < 7; col++) {
    if (board.isValidDrop(col)) {
      Board newBoard = board;
      newBoard.makeDrop(col, playerNum);
      int moveValue = minimax(newBoard, 3 - playerNum, playerNum, false, 0,
                              maxDepth, -1000, 1000);
      if (moveValue > bestValue) {
        bestValue = moveValue;
        bestMoves.clear();
        bestMoves.push_back(col);
      } else if (moveValue == bestValue) {
        bestMoves.push_back(col);
      }
    }
  }
  // If there are multiple best moves, return a random one
  return bestMoves[rand() % bestMoves.size()];
}