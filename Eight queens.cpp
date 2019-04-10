#include <iostream>
using namespace std;
void Print_Position(int right_position[93][9][9],int position)
{
    cout<<"   ";
    for(int i=0;i<8;i++)
    {
        cout<<char('A'+i)<<" ";
    }
    cout<<endl;
    for (int i=1;i<9;i++)
    {
        cout<<9-i<<"  ";
        for(int j=1;j<9;j++)
        {
            if(right_position[position][i][j]==1)
            {
                cout<<"Q ";
            }
            else
            {
                cout<<"* ";
            }
        }
        cout<<"  "<<9-i<<endl;
    }
    cout<<"   ";
    for(int i=0;i<8;i++)
    {
        cout<<char('A'+i)<<" ";
    }  
}
void Empty_Chess_Board(int chess_board[9][9] )
{
    for (int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            chess_board[i][j]=1;
        }
    }
    chess_board[0][1]=2;
}
void Queen_Attack(int chess_board[9][9],int queen_row ,int queen_column)
{   
    for(int j=1;j<9;j++)
    {
        chess_board[queen_row][j]=0;
    }

    for(int i=1;i<9;i++)
    {
        chess_board[i][queen_column]=0;
    }

    for(int i=queen_row,j=queen_column;i<9&&j<9;i++,j++)
    {
        chess_board[i][j]=0;
    }

    for(int i=queen_row,j=queen_column;i>0&&j>0;i--,j--)
    {
        chess_board[i][j]=0;
    }

    for(int i=queen_row,j=queen_column;i<9&&j>0;i++,j--)
    {
        chess_board[i][j]=0;
    }

    for(int i=queen_row,j=queen_column;i>0&&j<9;i--,j++)
    {
        chess_board[i][j]=0;
    }

}
void Undo_Queen_Attack(int chess_board[9][9],int right_position[93][9][9],int position)
{
    Empty_Chess_Board(chess_board);
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            if(right_position[position][i][j]==1)
            {
                Queen_Attack(chess_board,i,j);
                chess_board[i][j]=2;
            }
        }
    }
}
bool Check_All_Row(int chess_board[9][9])
{
    int counter;
    for(int i=1;i<9;i++)
    {
        counter=0;
        for(int j=1;j<9;j++)
        {
            if(chess_board[i][j]==0)
            {
                counter++;
                if(counter==8)
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
    for(int k=0;k<93;k++)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                right_position[k][i][j]=0;
            }
        }
    }
}
int last_queen_row_position;
int last_queen_column_position;
void Reomve_Last_Position(int right_position[93][9][9],int position )
{
    last_queen_row_position=0;
    last_queen_column_position=0;
    for (int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            if(right_position[position][i][j]==1)
            {
                last_queen_row_position=i;
                last_queen_column_position=j;
            }
        }
    }
    right_position[position][last_queen_row_position][last_queen_column_position]=0;
}
bool Check_Empty_Row(int chees_board[9][9],int row)
{
    for(int j=1;j<9;j++)
    {
        if(chees_board[row-1][j]==2)
        {
            return true;
        }
    }
    return false;
}
bool Checking_All_Row_To_Find_Queen(int chees_board[9][9])
{
    int counter=0;
    for (int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            if(chees_board[i][j]==2)
            {
                counter++;
                continue;
            }
        }
    }
    if(counter==8)
    {
        return true;
    }
    return false;
}
void Copy_Right_Position(int right_position[93][9][9],int position)
{
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            right_position[position][i][j]=right_position[position-1][i][j];
        }
    }
}
bool Find_Enough_Possibility(int chees_board[9][9],int row)
{
    int counter=0;
    for(int j=1;j<9;j++)
    {
        if(chees_board[row][j]==1)
        {
            counter++;
            if(counter>=2)
            {
                return false;
            }
        }
    }
    return true;
}
// this function is written just for check equality of two possibility
bool Check_Equality_Of_Two_Possibility(int right_position[93][9][9],int position_number)
{
    int counter;
    for(int k=position_number+1;k<93;k++)
    {
        counter=0;
        for(int i=1;i<9;i++)
        {
            for(int j=1;j<9;j++)
            {
                if(right_position[k][i][j]==right_position[position_number][i][j])
                {
                    counter++;
                    if(counter==64)
                    {
                        return false;
                    }
                }
                
            }
        } 
    }
    return true;
}
int main()
{
    int chess_board[9][9];
    int position=1;
    int flag=true;
    Empty_Chess_Board(chess_board);
    int right_position[93][9][9];
    First_Right_Position(right_position);
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)
        {
            if(Check_All_Row(chess_board)&&Check_Empty_Row(chess_board,i))
            {
                if(chess_board[i][j]==1)
                {
                    Queen_Attack(chess_board,i,j);
                    chess_board[i][j]=2;
                    right_position[position][i][j]=1;
                    if(Checking_All_Row_To_Find_Queen(chess_board))
                    {
                        position++;
                        if(position==93)
                        {
                            break;
                        }
                        Copy_Right_Position(right_position,position);
                        do
                        {
                            Reomve_Last_Position(right_position,position);
                            Undo_Queen_Attack(chess_board,right_position,position);
                            i=last_queen_row_position;
                            j=last_queen_column_position;

                        } while(Find_Enough_Possibility(chess_board,i));
                    }
                }
            }
            else
            {
                Reomve_Last_Position(right_position,position);
                Undo_Queen_Attack(chess_board,right_position,position);
                i=last_queen_row_position;
                j=last_queen_column_position;
            }
                
        }
    }

    for(;;)
    {
        system("cls");
        cout<<"             ____________ WELCOME ____________"<<endl<<endl;
        cout<<"This program is designed to show all the ways in which eight queens can be represented on a chessboard"<<endl;
        cout<<endl<<"Please enter a number between 1 and 92 enter 0 for EXIT."<<endl;
        int user_number;
        cin>>user_number;
        if(user_number>=1&&user_number<=92)
        {
            Print_Position(right_position,user_number);
            cin.ignore().get();
        }
        else if (user_number==0)
        {
            system("cls");
            cout<<"Have a good time :)";
            cin.ignore().get();
            return 0;
        }
        else
        {
            system("cls");
            cout<<"Please enter your number in range 1 to 92";
            cin.ignore().get();   
        }
    }
}
