#include <utility>

#include "tictactoe.h"

/******************************************************************************
 * 
 * File for managing the tic-tac-toe a.i.
 * 
 * Author: Thomas Andrasek
 * 
 * Last updated: 2020/08/09
 * 
 * ***************************************************************************/

namespace tictactoeai
{
  class Node
  {
   public:
    // Copy of game board
    tictactoe::TicTacToe* board_data_;

    unsigned int child_arr_length_;
    Node** children_;

    int game_score_;

    // The last placement of the baord
    std::pair<unsigned int, unsigned int> placement_;

    int best_child_;

    // Constructors
    Node(const tictactoe::TicTacToe &board, 
         std::pair<unsigned int, unsigned int> placement);
  };

  int CalcGameScore(const tictactoe::TicTacToe &board);

  // Check if certain areas are blocked
  bool IsRowBlocked(const tictactoe::TicTacToe &board, 
                    unsigned int x, unsigned int y);
  bool IsColumnBlocked(const tictactoe::TicTacToe &board, 
                       unsigned int x, unsigned int y);
  bool IsRightDiagnolBlocked(const tictactoe::TicTacToe &board, 
                             unsigned int x, unsigned int y);
  bool IsLeftDiagnolBlocked(const tictactoe::TicTacToe &board, 
                            unsigned int x, unsigned int y);

  // Decide where the a.i. should put the next token
  std::pair<unsigned int, unsigned int> MakePlacementChoice(
      const tictactoe::TicTacToe &board, 
      unsigned int move_depth, 
      bool player);

  // Minimax functions
  void CalcMaxChild(Node* root, bool top_root, unsigned int move_depth,
                    int alpha, int beta);
  void CalcMinChild(Node* root, bool top_root, unsigned int move_depth,
                    int alpha, int beta);

  void DeleteTree(Node* root);
}