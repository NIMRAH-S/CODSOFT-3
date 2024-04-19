#include<iostream>
#include<iomanip>
using namespace std;

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

char board[3][3]; // A 2D Array to make 3 * 3 game board

// A function resetboard so that we can call it easily whenever we need to reset the board to its initial state without copying the code again and again
void Resetboard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' '; // It will assign empty space in index to represent index is unoccupied and player can put X or O
        }
    }
}

void Displayboard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j]; // print content of game board in row i and column j
            if (j < 3 - 1)
                cout << "|"; // Separate cells horizontally
        }
        cout << endl;
        if (i < 3 - 1)
            std::cout << "-+-+-" << std::endl; // Separate rows vertically

    }

}

bool isValidMove(int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

void Playerinput(char playerturn)
{
    int row, col;

    // player will continue to enter row and col (move) until they enter a valid move
    do
    {
        cout << "Player " << playerturn << " enter row and column " << endl;
        cin >> row >> col;

    } while (!isValidMove(row, col) || board[row][col] != ' ');

    // once the player has entered a valid move update the board 
    board[row][col] = playerturn;
}

bool checkWin(char player)
{
    // Check rows, columns, and diagonals simultaneously
    for (int i = 0; i < 3; ++i)
    {
        // Check row
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }

        // Check column
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }
    return false;
}

bool isDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false; // If any index is empty, the game is not a draw
            }
        }
    }
    return true; // All indexs are occupied and no player has won
}

bool isGameOver()
{
    return checkWin('X') || checkWin('O') || isDraw();
}

int main()
{
    char key;

    cout << endl; //-
    cout << endl; // |
    cout << endl; // |
    cout << endl; // |- To leave some space from the top
    cout << endl; // |
    cout << endl; // |
    cout << endl; //-

    cout << ANSI_COLOR_YELLOW << "                                                      -------------------------------- " << endl; //54
    cout << "                                                    |  Welcome to Tic-Tac-Toe Game    |" << endl; //52
    cout << "                                                    |   Enter any key to continue     | " <<  endl;
    cout << "                                                      -------------------------------- " << ANSI_COLOR_YELLOW << endl; //54

    cin >> key;

    system("cls");

    Resetboard();

    char player1 = 'X';
    char player2 = 'O';

    Displayboard();

    char playerturn = player1; // starting with player 1 you can start with player 2 as well

    // player will take turn to play
    while (!isGameOver())
    {
        Playerinput(playerturn);
        Displayboard();
        playerturn = (playerturn == player1) ? player2 : player1; // Switch players
    }

    // Display result
    if (checkWin('X'))
    {
        cout << "Player X wins!" << endl;
    }
    else if (checkWin('O'))
    {
        cout << "Player O wins!" << endl;
    }
    else
    {
        cout << "The game is a draw!" << endl;
    }

    // Ask to play again
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        Resetboard();
        main(); // Restart the game
    }

    system("pause");
    return 0;
}
