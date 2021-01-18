#include<bits/stdc++.h>

using namespace std;

//Macros
#define easy 0
#define medium 1
#define hard 2

//global Variables
int side; //side will depend on the level chosen by player
int mines; // number of mines on each board will depend on level chosen by player

void playMineSweeper();
void replaceMines();
void initialise();
void placeMines();
void playMineSweeperUtil();
int countAdjacentMines();
void makeMove(int row, int col, char board[][25]); //Function to check whether the played cell has 
bool isValid(int row, int col); //A function to check whether the played cell is valid cell or not

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

    cout<<"***MINESWEEPER***"<<'\n';
    cout<<"Welcome Player:-)";
    chooseDifficultyLevel();
    playMineSweeper();
    return 0;
}