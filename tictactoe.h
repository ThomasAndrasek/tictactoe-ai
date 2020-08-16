#include <utility>

/******************************************************************************
 * General class for managing the game tic-tac-toe
 * 
 * Author: Thomas Andrasek
 * 
 * Last Updated: 2020/08/16
 * 
 * ***************************************************************************/

namespace tictactoe
{
  class TicTacToe 
  {
   public:
    // Constructors
    TicTacToe();
    TicTacToe(const char* game_state);
    TicTacToe(const TicTacToe& board);

    ~TicTacToe();

    // Get game info
    char** get_board_data() const { return board_data_; }
    unsigned int get_width() const { return widht_; }
    unsigned int get_height() const { return height_; }
    unsigned int get_empty_spaces() const { return empty_spaces_; }

    void ClearBoard();

    // Plays game between two players
    void PlayGame();

    bool PlaceToken(bool player, unsigned int x, unsigned int y);

    // Check board states
    std::pair<bool, char> CheckForWin() const;
    std::pair<bool, char> IsGameOver() const;
    bool IsBoardFull() const;

    void PrintBoard() const;

   private:
    // Size of board
    unsigned int widht_ = 3;
    unsigned int height_ = 3;

    unsigned int empty_spaces_;

    char** board_data_;
  };
}