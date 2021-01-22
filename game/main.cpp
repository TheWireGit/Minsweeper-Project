#include<bits/stdc++.h>

using namespace std;

//Macros
#define easy 0
#define medium 1
#define hard 2

//global Variables
int side; //side will depend on the level chosen by player
int mines; // number of mines on each board will depend on level chosen by player

void minesweeper(); // Function called
void replaceMines(int row, int col, char board[][25]);
void initialise(char realBoard[][25], char myBoard[][25]);
void placeMines(int Mines[][2],char realBoard[][25]); //
// A recursion to play minesweeper Game
bool playminesweeperUtil(char myBoard[][25],char realBoard[][25],int Mines[][2],int row, int col, int *movesLeft);
int countAdjacentmines(int row, int col, int Mines[][2],char realBoard[][25]);
bool isMine(int row, int col, char board[][25]); //Function to check whether the played cell has mine or not
bool isValid(int row, int col); //A function to check whether the played cell is valid cell or not
void makeMove(int *x, int *y); // A function to get the user's move
void printBoard(char myBoard[][25]);

void chooseDifficultyLevel()
{
    /*
        For Easy level enter 0 -> 9*9 board
        For Medium level enter 1 -> 16*16 board
        For Hard level enter 2 -> 25*25 board
    */
    cout<< "Choose Level: \n";
    cout<< "For Easy level enter 0\n";
    cout<< "For Medium level enter 1\n";
    cout<< "For Hard level enter 2\n";
    int level;
    cin>>level;
    if(level==0){
        side =9;
        mines=15;
        cout<< "Easy side:"<< side <<" mines:"<< mines<<" All the best!";
    }else if(level==1){
        side=16;
        mines=40;
        cout<< "Medium side:"<< side <<" mines:"<< mines<<" All the best!";
    }else if(level==2){
        side=24;
        mines=99;
        cout<< "Hard side:"<< side <<" mines:"<< mines<<" All the best!";
    }

    return; //for termination of this function
}

int main(){

    cout<<"***minesWEEPER***"<<'\n';
    cout<<"Welcome Player:-)";
    chooseDifficultyLevel();
    minesweeper();
    return 0;
}

void minesweeper ()
{
    // Initially the game is not over
    bool gameOver = false;

    // Actual Board and My Board
    char realBoard[25][25], myBoard[25][25];

    int movesLeft = side * side - mines, x, y;
    int mines[99][2]; // stores (x,y) coordinates of all mines.

      initialise (realBoard, myBoard);

    // Place the mines randomly
    placeMines (mines, realBoard);

    // You are in the game until you have not opened a mine
    // So keep playing

    int currentMoveIndex = 0;
    while (gameOver == false)
     {
        printf ("Current Status of Board : \n");
        printBoard (myBoard);
        makeMove (&x, &y);

        // This is to guarantee that the first move is
        // always safe
        // If it is the first move of the game
        if (currentMoveIndex == 0)
        {
            // If the first move itself is a mine
            // then we remove the mine from that location
            if (isMine (x, y, realBoard) == true)
                replaceMines (x, y, realBoard);
        }

        currentMoveIndex ++;

        gameOver = playminesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

        if ((gameOver == false) && (movesLeft == 0))
         {
            printf ("\nYou won !\n");
            gameOver = true;
         }
    }
    return;
}

void replaceMines (int row, int col, char board[][25])
{
    for (int i=0; i<side; i++)
    {
        for (int j=0; j<side; j++)
            {
                // Find the first location in the board
                // which is not having a mine and put a mine
                // there.
                if (board[i][j] != '*')
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
    }
    return;
}

void initialise(char realBoard[][25], char myBoard[][25])
{
    // Initiate the random number generator so that
    // the same configuration doesn't arises
    srand(time (NULL));

    // Assign all the cells as mine-free
    for (int i=0; i<side; i++)
    {
        for (int j=0; j<side; j++)
        {
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }

    return;
}

void placeMines(int Mines[][2], char realBoard[][25])
{
    bool mark[625];

    memset (mark, false, sizeof (mark));

    // Continue until all random mines have been created.
    for (int i=0; i<mines; )
     {
        int random = rand() % (side*side);
        int x = random / side;
        int y = random % side;

        // Add the mine if no mine is placed at this
        // position on the board
        if (mark[random] == false)
        {
            // Row Index of the Mine
            Mines[i][0]= x;
            // Column Index of the Mine
            Mines[i][1] = y;

            // Place the mine
            realBoard[Mines[i][0]][Mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }

    return;
}

bool playminesweeperUtil(char myBoard[][25], char realBoard[][25],
            int Mines[][2], int row, int col, int *movesLeft)
{

    // Base Case of Recursion
    if (myBoard[row][col] != '-')
        return (false);

    int i, j;

    // You opened a mine
    // You are going to lose
    if (realBoard[row][col] == '*')
    {
        myBoard[row][col]='*';

        for (i=0; i<mines; i++)
            myBoard[Mines[i][0]][Mines[i][1]]='*';

        printBoard (myBoard);
        printf ("\nYou lost!\n");
        return (true) ;
    }

    else
     {
        // Calculate the number of adjacent mines and put it
        // on the board
        int count = countAdjacentmines(row, col, Mines, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';

        if (!count)
        {
            /*
            Recur for all 8 adjacent cells

                N.W   N   N.E
                  \   |   /
                      \  |  /
                W----Cell----E
                     / | \
                   /   |  \
                S.W    S   S.E

            Cell-->Current Cell (row, col)
            N -->  North        (row-1, col)
            S -->  South        (row+1, col)
            E -->  East         (row, col+1)
            W -->  West            (row, col-1)
            N.E--> North-East   (row-1, col+1)
            N.W--> North-West   (row-1, col-1)
            S.E--> South-East   (row+1, col+1)
            S.W--> South-West   (row+1, col-1)
            */

                //----------- 1st Neighbour (North) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col) == true)
            {
                   if (isMine (row-1, col, realBoard) == false)
                   playminesweeperUtil(myBoard, realBoard, Mines, row-1, col, movesLeft);
            }

            //----------- 2nd Neighbour (South) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col) == true)
            {
                   if (isMine (row+1, col, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row+1, col, movesLeft);
            }

            //----------- 3rd Neighbour (East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col+1) == true)
            {
                if (isMine (row, col+1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row, col+1, movesLeft);
            }

            //----------- 4th Neighbour (West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col-1) == true)
            {
                   if (isMine (row, col-1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row, col-1, movesLeft);
            }

            //----------- 5th Neighbour (North-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col+1) == true)
            {
                if (isMine (row-1, col+1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row-1, col+1, movesLeft);
            }

             //----------- 6th Neighbour (North-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col-1) == true)
            {
                 if (isMine (row-1, col-1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row-1, col-1, movesLeft);
            }

             //----------- 7th Neighbour (South-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col+1) == true)
            {
                 if (isMine (row+1, col+1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row+1, col+1, movesLeft);
            }

            //----------- 8th Neighbour (South-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col-1) == true)
            {
                if (isMine (row+1, col-1, realBoard) == false)
                    playminesweeperUtil(myBoard, realBoard, Mines, row+1, col-1, movesLeft);
            }
        }

        return (false);
    }
}

bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < side) &&
           (col >= 0) && (col < side);
}

// A Utility Function to check whether given cell (row, col)
// has a mine or not.
bool isMine (int row, int col, char board[][25])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}

// A Function to get the user's move
void makeMove(int *x, int *y)
{
    // Take the input move
    printf("Enter your move, (row, column) -> ");
    scanf("%d %d", x, y);
    return;
}

// A Function to print the current gameplay board
void printBoard(char myBoard[][25])
{
    int i, j;

    printf ("    ");

    for (i=0; i<side; i++)
        printf ("%d ", i);

    printf ("\n\n");

    for (i=0; i<side; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<side; j++)
            printf ("%c ", myBoard[i][j]);
        printf ("\n");
    }
    return;
}

// A Function to count the number of
// mines in the adjacent cells
int countAdjacentmines(int row, int col, int Mines[][2],
                      char realBoard[][25])
{

    int i;
    int count = 0;

    /*
        Count all the mines in the 8 adjacent
        cells

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Current Cell (row, col)
        N -->  North        (row-1, col)
        S -->  South        (row+1, col)
        E -->  East         (row, col+1)
        W -->  West            (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
    */

    //----------- 1st Neighbour (North) ------------

        // Only process this cell if this is a valid one
        if (isValid (row-1, col) == true)
        {
               if (isMine (row-1, col, realBoard) == true)
               count++;
        }

    //----------- 2nd Neighbour (South) ------------

        // Only process this cell if this is a valid one
        if (isValid (row+1, col) == true)
        {
               if (isMine (row+1, col, realBoard) == true)
               count++;
        }

    //----------- 3rd Neighbour (East) ------------

        // Only process this cell if this is a valid one
        if (isValid (row, col+1) == true)
        {
            if (isMine (row, col+1, realBoard) == true)
               count++;
        }

    //----------- 4th Neighbour (West) ------------

        // Only process this cell if this is a valid one
        if (isValid (row, col-1) == true)
        {
               if (isMine (row, col-1, realBoard) == true)
               count++;
        }

    //----------- 5th Neighbour (North-East) ------------

        // Only process this cell if this is a valid one
        if (isValid (row-1, col+1) == true)
        {
            if (isMine (row-1, col+1, realBoard) == true)
               count++;
        }

     //----------- 6th Neighbour (North-West) ------------

        // Only process this cell if this is a valid one
        if (isValid (row-1, col-1) == true)
        {
             if (isMine (row-1, col-1, realBoard) == true)
               count++;
        }

     //----------- 7th Neighbour (South-East) ------------

        // Only process this cell if this is a valid one
        if (isValid (row+1, col+1) == true)
        {
               if (isMine (row+1, col+1, realBoard) == true)
               count++;
        }

    //----------- 8th Neighbour (South-West) ------------

        // Only process this cell if this is a valid one
        if (isValid (row+1, col-1) == true)
        {
            if (isMine (row+1, col-1, realBoard) == true)
               count++;
        }

    return (count);
}
