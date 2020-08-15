#include <utility>

/******************************************************************************
 * General class for managing the game tic-tac-toe
 * 
 * Author: Thomas Andrasek
 * 
 * Last Updated: 2020/08/09
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
    char** get_board_data() const { return m_board_data; }
    unsigned int get_width() const { return m_width; }
    unsigned int get_height() const { return m_height; }
    unsigned int get_empty_spaces() const { return m_empty_spaces; }

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
    unsigned int m_width = 3;
    unsigned int m_height = 3;

    unsigned int m_empty_spaces = 9;

    char** m_board_data;
  };
}