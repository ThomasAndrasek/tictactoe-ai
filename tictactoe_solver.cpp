#include <utility>
#include <iostream>

#include "tictactoe_ai.h"

/******************************************************************************
 * 
 * File for managing all the methods for the TicTacToe class
 * 
 * Author: Thomas Andrasek
 * 
 * Last updated: 2020/10/05
 * 
 * ***************************************************************************/

//  Construct a Node object for the game decision tree
//  
//  @param board the tic-tac-toe board to copy and make moves on
//  @param placement the position of the last token placed
tictactoeai::Node::Node(tictactoe::TicTacToe *board,
           std::pair<unsigned int, unsigned int> placement)
{
  this->board_data_ = board;
  this->placement_ = placement;
  this->child_arr_length_ = 0;
  // Using -1 to indicate the best move position hasn't been chosen yet
  this->best_child_ = -1;
  // Temp game score, using -1337 as a key value
  this->game_score_ = -1337;
}

// Calculates the game score of the given board
// 
// A positive score indicates that 'X' is winning, and a negative score
// indicates that 'O' is winning. If the score is 0 the current game state is a
// tie. 
// 
// Points are awarded for having control of a given dirrection without being
// blocked by the other player. Points are also awarded for winning the game.
//
// @param board the board to calculate the game score of
// 
// @return the score of the game
int tictactoeai::CalcGameScore(const tictactoe::TicTacToe &board)
{
  // Scores for each player
  int x = 0;
  int o = 0;

  for (unsigned int i = 0; i < board.get_width(); ++i)
  {
    for (unsigned int j = 0; j < board.get_height(); ++j)
    {
      char piece = board.get_board_data()[i][j];

      if (piece != ' ')
      {
        // Check if the four dirrections are blocked in any case

        if (!IsRowBlocked(board, i, j))
        {
          if (piece == 'X')
            x += 1;
          else
            o += 1;
        }

        if (!IsColumnBlocked(board, i, j))
        {
          if (piece == 'X')
            x += 1;
          else
            o += 1;
        }

        if (!IsRightDiagnolBlocked(board, i, j))
        {
          if (piece == 'X')
            x += 1;
          else
            o += 1;
        }

        if (!IsLeftDiagnolBlocked(board, i, j))
        {
          if (piece == 'X')
            x += 1;
          else
            o += 1;
        }
      }
    }
  }

  // Award 100 points if there is a winner
  std::pair<bool, char> win_data = board.CheckForWin();
  if (win_data.second == 'X')
    x+=100;
  else if (win_data.second == 'O')
    o+=100;

  return x-o;
}

// Checks if the row is blocked at the given position
//
// @param board the tictactoe board
// @param x the column position
// @param y the row position
//
// @return whether or not the row is blocked
bool tictactoeai::IsRowBlocked(const tictactoe::TicTacToe &board,
                               unsigned int x, unsigned int y)
{
  char piece = board.get_board_data()[x][y];

  if ((board.get_board_data()[0][y] == ' ' ||
       board.get_board_data()[0][y] == piece) &&
      (board.get_board_data()[1][y] == ' ' ||
       board.get_board_data()[1][y] == piece) &&
      (board.get_board_data()[2][y] == ' ' ||
       board.get_board_data()[2][y] == piece))
    return false;

  return true;
}

// Checks if the column is blocked at the given position
//
// @param board the tictactoe board
// @param x the column position
// @param y the row position
//
// @return whether or not the column is blocked
bool tictactoeai::IsColumnBlocked(const tictactoe::TicTacToe &board,
                                  unsigned int x, unsigned int y)
{
  char piece = board.get_board_data()[x][y];

  if ((board.get_board_data()[x][0] == ' ' ||
       board.get_board_data()[x][0] == piece) && 
      (board.get_board_data()[x][1] == ' ' ||
       board.get_board_data()[x][1] == piece) &&
      (board.get_board_data()[x][2] == ' ' || 
       board.get_board_data()[x][2] == piece))
    return false;

  return true;
}

// Checks if the right diagnol on the board is blocked
//
// @param board the tictactoe board
// @param x the column position
// @param y the row position
//
// @return whether the right diagnol on the board is blocked
bool tictactoeai::IsRightDiagnolBlocked(const tictactoe::TicTacToe &board,
                                        unsigned int x, unsigned int y)
{
  char piece = board.get_board_data()[x][y];

  // check if the given position is on the right angle
  if ((x == 0 && y == 0) || (x==1 && y==1) || (x==2 && y==2))
  {
    if ((board.get_board_data()[0][0] == ' ' ||
         board.get_board_data()[0][0] == piece) &&
        (board.get_board_data()[1][1] == ' ' ||
         board.get_board_data()[1][1] == piece) &&
        (board.get_board_data()[2][2] == ' ' ||
         board.get_board_data()[2][2] == piece))
      return false;
  }

  return true;
}

// Checks if the left diagnol on the board is blocked
//
// @param board the tictactoe board
// @param x the column position
// @param y the row position
//
// @return whether the left diagnol on the board is blocked
bool tictactoeai::IsLeftDiagnolBlocked(const tictactoe::TicTacToe &board,
                                       unsigned int x, unsigned int y)
{
  char piece = board.get_board_data()[x][y];

  // check if the given position is on the left angle
  if ((x == 0 && y == 2) || (x==1 && y==1) || (x==2 && y==0))
  {
    if ((board.get_board_data()[0][2] == ' ' ||
         board.get_board_data()[0][2] == piece) &&
        (board.get_board_data()[1][1] == ' ' ||
         board.get_board_data()[1][1] == piece) &&
        (board.get_board_data()[2][0] == ' ' ||
         board.get_board_data()[2][0] == piece))
      return false;
  }

  return true;
}

// This function makes a choice for placing a token on the board using the idea
// of the minimax algorithm. It generates moves up the specified move depth or
// until the game has been completed. After generating moves the minimax
// algorithm will make a choice on where is the best place to place a token
// 
// If a game score is positive that means that 'X' is winning, if the game
// score is negative then 'O' is winning, and if the score is zero then it is
// currently a tie.
//
// Alpha beta pruning is also implemented to increase the speed of the function
// To learn more about minimax and alpha beta pruning check out the wikipedia
// article
// - https://en.wikipedia.org/wiki/Minimax
// - https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
// 
// @param board current tic-tac-toe board
// @param move_depth the amount of moves to look ahead
// @param player which players turn it is, true for 'X' false for 'O'
std::pair<unsigned int, unsigned int> tictactoeai::MakePlacementChoice(
    const tictactoe::TicTacToe &board,
    unsigned int move_depth,
    bool player)
{
  tictactoe::TicTacToe *game = new tictactoe::TicTacToe(board);
  Node* root = new Node(game, {100,100});

  if (player)
    CalcMaxChild(root, true, move_depth, INT32_MIN, INT32_MAX);
  else
    CalcMinChild(root, true, move_depth, INT32_MIN, INT32_MAX);

  std::pair<unsigned int, unsigned int> placement =
   root->children_[root->best_child_]->placement_;

  if (root->children_)
    {
      for (unsigned int i = 0; i < root->child_arr_length_; ++i)
      {
        delete root->children_[i];
      }

      delete [] root->children_;
    }

  delete root;

  return placement;
}

// Figures out which child node will result in the maximum game score
// 
// Implements alpha beta pruning in order to optimize the function
//
// @param root the root node to calculate the maximum child of
// @param top_root whether or not the current root node is the root of the entire tree
// @param move_depth how many moves to look ahead
// @param alpha the alpha score for alpha beta pruning
// @param beta the beta score for the alpha beta pruning
void tictactoeai::CalcMaxChild(Node* root, bool top_root,
                               unsigned int move_depth, int alpha, int beta)
{
  if (root)
  {
    // Checks if no more moves can be made
    if (move_depth == 0 || root->board_data_->IsGameOver().first)
    {
      root->game_score_ = CalcGameScore(*root->board_data_);
    }
    else if (move_depth >= 1)
    {
      root->child_arr_length_ = (*root->board_data_).get_empty_spaces();
      root->children_ = new Node*[root->child_arr_length_];
      for (unsigned int i = 0; i < root->child_arr_length_; ++i)
      {
        root->children_[i] = NULL;
      }

      unsigned int child = 0;
      int max = 0;

      for (unsigned int i = 0; i < (*root->board_data_).get_width(); ++i)
      {
        for (unsigned int j = 0; j < (*root->board_data_).get_height(); ++j)
        {
          if (root->board_data_->get_board_data()[i][j] == ' ')
          {
            tictactoe::TicTacToe *copy = new tictactoe::TicTacToe(*root->board_data_);
            copy->PlaceToken(true, i, j);
            root->children_[child] = new Node(copy, {i, j});
            CalcMinChild(root->children_[child], false, move_depth-1, alpha,
                         beta);

            if (root->children_[max]->game_score_ <
                root->children_[child]->game_score_)
              max = child;

            if (root->children_[max]->game_score_ > alpha)
              alpha = root->children_[max]->game_score_;

            child++;

            if (beta <= alpha)
              break;
          }
        }

        if (beta <= alpha)
          break;
      }

      root->game_score_ = root->children_[max]->game_score_;

      if (top_root)
        root->best_child_ = max;
    }

    if (root->board_data_)
        delete root->board_data_;

      if (root->children_ && !top_root)
      {
        for (unsigned char i = 0; i < root->child_arr_length_; ++i)
        {
          if (root->children_[i])
            delete root->children_[i];
        }

        delete [] root->children_;
      }
  }
}

// Figures out which child node will result in the minimum game score
// 
// Implements alpha beta pruning in order to optimize the function
//
// @param root the root node to calculate the minimum child of
// @param top_root whether or not the current root node is the root of the entire tree
// @param move_depth how many moves to look ahead
// @param alpha the alpha score for alpha beta pruning
// @param beta the beta score for the alpha beta pruning
void tictactoeai::CalcMinChild(Node* root, bool top_root,
                               unsigned int move_depth, int alpha, int beta)
{
  if (root)
  {
    // Checks if no more moves can be made
    if (move_depth == 0 || root->board_data_->IsGameOver().first)
    {
      root->game_score_ = CalcGameScore(*root->board_data_);
    }
    else if (move_depth >= 1)
    {
      root->child_arr_length_ = (*root->board_data_).get_empty_spaces();
      root->children_ = new Node*[root->child_arr_length_];
      for (unsigned int i = 0; i < root->child_arr_length_; ++i)
      {
        root->children_[i] = NULL;
      }

      unsigned int child = 0;
      int min = 0;

      for (unsigned int i = 0; i < (*root->board_data_).get_width(); ++i)
      {
        for (unsigned int j = 0; j < (*root->board_data_).get_height(); ++j)
        {
          if (root->board_data_->get_board_data()[i][j] == ' ')
          {
            tictactoe::TicTacToe *copy = new tictactoe::TicTacToe(*root->board_data_);
            copy->PlaceToken(true, i, j);
            root->children_[child] = new Node(copy, {i, j});
            CalcMaxChild(root->children_[child], false, move_depth-1, alpha,
                         beta);

            if (root->children_[min]->game_score_ >
                root->children_[child]->game_score_)
              min = child;

            if (root->children_[min]->game_score_ < beta)
              beta = root->children_[min]->game_score_;

            child++;

            if (beta <= alpha)
              break;
          }
        }

        if (beta <= alpha)
          break;
      }

      root->game_score_ = root->children_[min]->game_score_;

      if (top_root)
        root->best_child_ = min;
    }

    if (root->board_data_)
        delete root->board_data_;

      if (root->children_ && !top_root)
      {
        for (unsigned char i = 0; i < root->child_arr_length_; ++i)
        {
          if (root->children_[i])
            delete root->children_[i];
        }

        delete [] root->children_;
      }
  }
}
