#include <iostream>
#include <utility>
#include <string>

#include "tictactoe.h"

/******************************************************************************
 * 
 * File for managing all the methods for the TicTacToe class
 * 
 * Author: Thomas Andrasek
 * 
 * Last updated: 2020/08/14
 * 
 * ***************************************************************************/

// Default Constructor for the TicTacToe class
//  
// Creates a blank 3x3 tictactoe board object
tictactoe::TicTacToe::TicTacToe()
{
  m_board_data = new char*[m_width];
  for (unsigned int i = 0; i < m_width; ++i)
    m_board_data[i] = new char[m_height];

  ClearBoard();
}

// Creates a TicTacToe object from the given character aray of 9 characters
//
// @param game_state game state of 9 characters
tictactoe::TicTacToe::TicTacToe(const char* game_state)
{
  m_board_data = new char*[3];

  for (unsigned int i = 0; i < 3; ++i)
    m_board_data[i] = new char[3];

  for (unsigned int j = 0; j < 3; ++j)
    for (unsigned int i = 0; i < 3; ++i)
      m_board_data[i][j] = game_state[j*3+i];
}

// Copies the given TicTacToe object
//  
// @param board the TicTacToe board object to copy
tictactoe::TicTacToe::TicTacToe(const TicTacToe& board)
{
  m_board_data = new char*[m_width];

  for (unsigned int i = 0; i < m_width; ++i)
  {
    m_board_data[i] = new char[m_height];
    for (unsigned int j = 0; j < m_height; ++j)
      m_board_data[i][j] = board.m_board_data[i][j];
  }
}

// Deconstructor for the TicTacToe object
tictactoe::TicTacToe::~TicTacToe()
{
  for (unsigned int i = 0; i < m_width; ++i)
    delete [] m_board_data[i];

  delete [] m_board_data;
}

// Sets all the spots on the board to blank spots.
void tictactoe::TicTacToe::ClearBoard()
{
  for (unsigned int i = 0; i < m_width; ++i)
    for (unsigned int j = 0; j < m_height; ++j)
      m_board_data[i][j] = ' ';
}

// Prints out the current board state.
void tictactoe::TicTacToe::PrintBoard() const
{
  std::cout << " " << m_board_data[0][2] << " | "
   << m_board_data[1][2] << " | " << m_board_data[2][2] << std::endl;
  std::cout << "-----------" << std::endl;
  std::cout << " " << m_board_data[0][1] << " | "
   << m_board_data[1][1] << " | " << m_board_data[2][1] << std::endl;
  std::cout << "-----------" << std::endl;
  std::cout << " " << m_board_data[0][0] << " | "
   << m_board_data[1][0] << " | " << m_board_data[2][0] << std::endl;
}

// Places a token in the given position
// 
// @param player true for X false for O
// @param x the column to place the token
// @param y the row to place the token
// 
// @return whether the token could be placed
bool tictactoe::TicTacToe::PlaceToken(bool player, unsigned int x,
                                      unsigned int y)
{
  if (x >= 3 || y >= 3)
    return false;

  if (m_board_data[x][y] == ' ')
  {
    if (player)
      m_board_data[x][y] = 'X';
    else
      m_board_data[x][y] = 'O';

    m_empty_spaces--;
    return true;
  }

  return false;
}

// Checks for if there is a winner.
// 
// @return whether there is a winner or not, if there is a winner the char of
// the winner
std::pair<bool, char> tictactoe::TicTacToe::CheckForWin() const 
{
  std::pair<bool, char> ret = {false, ' '};

  if (m_board_data[0][0] != ' '
   && m_board_data[0][0] == m_board_data[1][0]
   && m_board_data[0][0] == m_board_data[2][0])
    ret = {true, m_board_data[0][0]};
  else if (m_board_data[0][1] != ' '
   && m_board_data[0][1] == m_board_data[1][1]
   && m_board_data[0][1] == m_board_data[2][1])
    ret = {true, m_board_data[0][1]};
  else if (m_board_data[0][2] != ' '
   && m_board_data[0][2] == m_board_data[1][2]
   && m_board_data[0][2] == m_board_data[2][2])
    ret = {true, m_board_data[0][2]};
  else if (m_board_data[0][0] != ' '
   && m_board_data[0][0] == m_board_data[0][1]
   && m_board_data[0][0] == m_board_data[0][2])
    ret = {true, m_board_data[0][0]};
  else if (m_board_data[1][0] != ' '
   && m_board_data[1][0] == m_board_data[1][1]
   && m_board_data[1][0] == m_board_data[1][2])
    ret = {true, m_board_data[1][0]};
  else if (m_board_data[2][0] != ' '
   && m_board_data[2][0] == m_board_data[2][1]
   && m_board_data[2][0] == m_board_data[2][2])
    ret = {true, m_board_data[2][0]};
  else if (m_board_data[0][0] != ' '
   && m_board_data[0][0] == m_board_data[1][1]
   && m_board_data[0][0] == m_board_data[2][2])
    ret = {true, m_board_data[0][0]};
  else if (m_board_data[0][2] != ' '
   && m_board_data[0][2] == m_board_data[1][1]
   && m_board_data[0][2] == m_board_data[2][0])
    ret = {true, m_board_data[0][2]};

  return ret;
}

// Check if the board is full
// 
// @return whether or not the board is full
bool tictactoe::TicTacToe::IsBoardFull() const
{
  if (m_empty_spaces == 0)
    return true;

  return false;
}

// Checks if the tic-tac-toe game is over 
// The game is over if: 
//  - a player has three in a row 
//  - the board is full
//  
// @return whether or not the game is over, if the game is over return the
//  token of the winner, space character if tied
std::pair<bool, char> tictactoe::TicTacToe::IsGameOver() const
{
  std::pair<bool, char> ret = CheckForWin();

  if (ret.first)
    return ret;
  
  if (IsBoardFull())
    ret = {true, ' '};
  
  return ret;
}

// Have two players play a game of tic-tac-toe in the console
void tictactoe::TicTacToe::PlayGame()
{
  bool player = true;
  unsigned int x;
  unsigned int y;

  std::string temp = "";

  std::pair<bool, char> game_over_data = IsGameOver();

  PrintBoard();

  while(!game_over_data.first)
  {
    std::cout << "Enter column >> ";
    std::cin >> temp;
    x = std::stoi(temp);

    std::cout << "Enter row >> ";
    std::cin >> temp;
    y = std::stoi(temp);

    PlaceToken(player, x, y);

    player = !player;

    game_over_data = IsGameOver();

    PrintBoard();
  }
}