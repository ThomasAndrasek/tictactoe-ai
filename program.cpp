#include <iostream>
#include <string>

#include "tictactoe_ai.h"

/******************************************************************************
 * 
 * Basic main file for playing against the tic-tac-toe A.I.
 * 
 * Example run: ./tictactoe.out
 * 
 * Author: Thomas Andrasek
 * 
 * Last updated: 2020/08/14
 * 
 * ***************************************************************************/

int main() 
{
    tictactoe::TicTacToe board;

    std::string input_text = "";

    std::cout << "Enter A.I. move depth >> ";
    std::cin >> input_text;
    unsigned int move_depth = std::stoi(input_text);

    std::cout << "Do you want to go first? y/n >> ";
    std::cin >> input_text;
    bool move_first = (input_text == "y") ? true : false;

    int x = -1;
    int y = -1;

    while (!(board.IsGameOver().first))
    {
      if (move_first)
      {
        std::cout << "Enter a column number 0,1,2 >> ";
        std::cin >> input_text;
        x = std::stoi(input_text);
        std::cout << "Enter a row number 0,1,2 >> ";
        std::cin >> input_text;
        y = std::stoi(input_text);
        board.PlaceToken(move_first, x, y);
      }
      else
      {
        std::cout << "Thinking..." << std::endl;
        std::pair<unsigned int, unsigned int> placement_choice =
         tictactoeai::MakePlacementChoice(board, move_depth, move_first);
        std::cout << "I'm going " << placement_choice.first << ", " <<
         placement_choice.second << std::endl;
        board.PlaceToken(move_first, placement_choice.first,
                         placement_choice.second);
      }

      board.PrintBoard();
      move_first = !move_first;
    }
}