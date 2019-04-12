#include <iostream>
using namespace std;

void Print_Position(int right_position[93][9][9], int position)
{
    cout << "   ";
    for (int i = 0; i < 8; i++)
    {
        cout << char('A' + i) << " ";
    }
    cout << endl;
    for (int i = 1; i < 9; i++)
    {
        cout << 9 - i << "  ";
        for (int j = 1; j < 9; j++)
        {
            if (right_position[position][i][j] == 1)
            {
                cout << "Q ";
            }
            else
            {
                cout << "* ";
            }
        }
        cout << "  " << 9 - i << endl;
    }
    cout << "   ";
    for (int i = 0; i < 8; i++)
    {
        cout << char('A' + i) << " ";
    }
}

void Empty_Chess_Board(int chess_board[9][9])
{
    for (int row = 0; row <= 8; row++)
    {
        for (int column = 0; column <= 8; column++)
        {
            chess_board[row][column] = 1;
        }
    }

    // To work correctly Searching the previous rows to find the queens function,
    // We need to put the contents of this cell equal to 2.
    chess_board[0][1] = 2;
}

void Queen_Attack(int chess_board[9][9], int queen_row, int queen_column)
{
    for (int column = 1; column <= 8; column++)
    {
        chess_board[queen_row][column] = 0;
    }

    for (int row = 1; row <= 8; row++)
    {
        chess_board[row][queen_column] = 0;
    }

    for (int row = queen_row, column = queen_column; row <= 8 && column <= 8; row++, column++)
    {
        chess_board[row][column] = 0;
    }

    for (int row = queen_row, column = queen_column; row > 0 && column > 0; row--, column--)
    {
        chess_board[row][column] = 0;
    }

    for (int row = queen_row, column = queen_column; row <= 8 && column > 0; row++, column--)
    {
        chess_board[row][column] = 0;
    }

    for (int row = queen_row, column = queen_column; row > 0 && column <= 8; row--, column++)
    {
        chess_board[row][column] = 0;
    }
}

void Undo_Queen_Attack(int chess_board[9][9], int right_position[93][9][9], int position)
{
    Empty_Chess_Board(chess_board);
    for (int row = 1; row <= 8; row++)
    {
        for (int column = 1; column <= 8; column++)
        {
            if (right_position[position][row][column] == 1)
            {
                Queen_Attack(chess_board, row, column);
                chess_board[row][column] = 2;
            }
        }
    }
}
// If the queens are in such a way that they are completely zero in linear lines,
// Our problem hasn't any answer in this position,
// and we have to go back one step back.
bool Check_All_The_Rows_To_Find_The_Rows_Full_Of_0(int chess_board[9][9])
{
    int counter;
    for (int row = 1; row <= 8; row++)
    {
        counter = 0;
        for (int column = 1; column <= 8; column++)
        {
            if (chess_board[row][column] == 0)
            {
                counter++;
                if (counter == 8)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void First_Right_Position(int right_position[93][9][9])
{
    for (int position = 0; position <= 92; position++)
    {
        for (int row = 0; row <= 8; row++)
        {
            for (int column = 0; column <= 8; column++)
            {
                right_position[position][row][column] = 0;
            }
        }
    }
}

int last_queen_row_position;
int last_queen_column_position;
void Reomve_Last_Position(int right_position[93][9][9], int position)
{
    for (int row = 1; row <= 8; row++)
    {
        for (int column = 1; column <= 8; column++)
        {
            if (right_position[position][row][column] == 1)
            {
                last_queen_row_position = row;
                last_queen_column_position = column;
            }
        }
    }
    right_position[position][last_queen_row_position][last_queen_column_position] = 0;
}

// If we want to put a queen in a row, there must exist a queen in all previous rows.
bool Searching_The_Previous_Rows_To_Find_The_Queens(int chees_board[9][9], int row)
{
    for (int column = 1; column <= 8; column++)
    {
        if (chees_board[row - 1][column] == 2)
        {
            return true;
        }
    }
    return false;
}

bool Checking_All_Row_To_Find_Queen(int chees_board[9][9])
{
    int counter = 0;
    for (int row = 1; row <= 8; row++)
    {
        for (int column = 1; column <= 8; column++)
        {
            if (chees_board[row][column] == 2)
            {
                counter++;
                continue;
            }
        }
    }
    if (counter == 8)
    {
        return true;
    }
    return false;
}

void Copy_Right_Position(int right_position[93][9][9], int position)
{
    for (int row = 1; row <= 8; row++)
    {
        for (int column = 1; column <= 8; column++)
        {
            right_position[position][row][column] = right_position[position - 1][row][column];
        }
    }
}

// When we found an answer,
// We have to go back so that we can again move the queens and reach another answer
bool Find_Enough_Possibility(int chees_board[9][9], int row)
{
    int counter = 0;
    for (int column = 1; column <= 8; column++)
    {
        if (chees_board[row][column] == 1)
        {
            counter++;
            if (counter >= 2)
            {
                return false;
            }
        }
    }
    return true;
}

// This function is written just for check equality of two possibility
bool Check_Equality_Of_Two_Possibility(int right_position[93][9][9], int position_number)
{
    int counter;
    for (int k = position_number + 1; k < 93; k++)
    {
        counter = 0;
        for (int row = 1; row <= 8; row++)
        {
            for (int column = 1; column <= 8; column++)
            {
                if (right_position[k][row][column] == right_position[position_number][row][column])
                {
                    counter++;
                    if (counter == 64)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int Interface(int right_position[93][9][9])
{
    for (;;)
    {
        system("cls");
        cout << "                         ____________ WELCOME ____________" << endl
             << endl;
        cout << "This program is designed to show all the ways in which eight queens can be represented on a chessboard" << endl;
        cout << "This question has 92 different answers." << endl;
        cout << endl
             << "Please enter a number between 1 and 92  to see the desired mode enter 0 for EXIT." << endl;
        int user_number;
        cin >> user_number;
        if (user_number >= 1 && user_number <= 92)
        {
            Print_Position(right_position, user_number);
            cin.ignore().get();
        }
        else if (user_number == 0)
        {
            system("cls");
            cout << "Have a good time :)";
            cin.ignore().get();
            return 0;
        }
        else
        {
            system("cls");
            cout << "Please enter your number in range 1 to 92";
            cin.ignore().get();
        }
    }
}

int main()
{
    // The chessboard consists of 8 rows and 8 columns
    int chess_board[9][9];
    int position = 1;
    Empty_Chess_Board(chess_board);

    // There are 92 answers in total for this question and we want save them in this array.
    int right_position[93][9][9];
    First_Right_Position(right_position);

    for (int row = 1; row <= 8; row++)
    {
        for (int column = 1; column <= 8; column++)
        {
            if (Check_All_The_Rows_To_Find_The_Rows_Full_Of_0(chess_board) && Searching_The_Previous_Rows_To_Find_The_Queens(chess_board, row))
            {
                if (chess_board[row][column] == 1)
                {
                    Queen_Attack(chess_board, row, column);

                    // We marking the house where the queen is there with 2
                    chess_board[row][column] = 2;
                    right_position[position][row][column] = 1;
                    if (Checking_All_Row_To_Find_Queen(chess_board))
                    {
                        position++;
                        if (position == 93)
                        {
                            break;
                        }
                        Copy_Right_Position(right_position, position);
                        do
                        {
                            Reomve_Last_Position(right_position, position);
                            Undo_Queen_Attack(chess_board, right_position, position);
                            row = last_queen_row_position;
                            column = last_queen_column_position;

                        } while (Find_Enough_Possibility(chess_board, row));
                    }
                }
            }
            else
            {
                Reomve_Last_Position(right_position, position);
                Undo_Queen_Attack(chess_board, right_position, position);
                row = last_queen_row_position;
                column = last_queen_column_position;
            }
        }
    }

    Interface(right_position);
}