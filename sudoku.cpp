#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/* THIS FUNCTIONALITY WILL BE FOR THE GAME OF SUDOKU */

bool checker(int puzzle[][9], int curr_row, int curr_col)
{
    int curr_value = puzzle[curr_row][curr_col];
    /* CHECKING GIVEN ROW */
    for(int i=0; i<9; i++){
        if(i == curr_col){
            continue;
        }
        if(puzzle[curr_row][i]==curr_value){
            return false;
        }
    }
    /* CHECKING GIVEN COL */
    for(int i=0; i<9; i++){
        if(i == curr_row){
            continue;
        }
        if(puzzle[i][curr_col]==curr_value){
            return false;
        }
    }
    /* CHECKING CURRENT 3X3 */
    int nearest3_row = (curr_row / 3) * 3, nearest3_col = (curr_col / 3) * 3;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            /* SKIP THE GIVEN CELL IN QUESTION */
            if(nearest3_row+i == curr_row && nearest3_col+j == curr_col){
                continue;
            }
            if(puzzle[nearest3_row+i][nearest3_col+j] == puzzle[curr_row][curr_col]){
                return false;
            }
        }
    }
    return true;
}

bool solver(int puzzle[][9], int curr_row, int curr_col)
{
    /* PUZZLE IS COMPLETED */
    if(curr_row==9){
        return true;
    }
    /* THE CURRENT CELL IS ALREADY GIVEN */
    if(puzzle[curr_row][curr_col]!=0){
        if(curr_col==8){
            return solver(puzzle,curr_row+1,0);
        }
        else{
            return solver(puzzle,curr_row,curr_col+1);
        }
    }
    /* CURRENT CELL NOT GIVEN. FIND ANSWER FOR CELL! */
    bool correct;
    for(int i=1; i<10; i++){
        puzzle[curr_row][curr_col] = i;
        if(!checker(puzzle, curr_row, curr_col)){
            continue;
        }
        if(curr_col==8){
            correct = solver(puzzle,curr_row+1,0);
        }
        else{
            correct = solver(puzzle,curr_row,curr_col+1);
        }
        if(correct){
            return true;
        }
    }
    /* A PREVIOUS ANSWER WAS INCORRECT. BACKTRACK! */
    puzzle[curr_row][curr_col] = 0;
    return false;
}

bool is_complete(int puzzle[][9]){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(puzzle[j][i]==0){
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char* argv[])
{
    if(argc<2){
        cout << "You are missing a file to read from..." << endl;
        return 1;
    }
    ifstream read;
    read.open(argv[1]);
    if(!read.is_open()){
        cout << "Cannot open the file" << endl;
        return 1;
    }
    /* READ 0'S AS EMPTY SPACES */
    int puzzle[9][9];
    int player_puzzle[9][9];
    string temp;
    read >> temp;
    read.close();
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            puzzle[i][j] = temp[9*i+j]-'0';
            player_puzzle[i][j] = puzzle[i][j];
        }
    }
    if(!solver(puzzle,0,0)){
        cout << "This puzzle is unsolvable!" << endl;;
        return 0;
    }

    /* PLAYER IS GIVEN 3 LIVES */
    int lives = 3;
    while(lives>0 && !is_complete(player_puzzle)){
        cout << "                 Lives: " << lives << endl;
        for(int i=0; i<9; i++){
            if(i%3==0){
                cout << " _______________________ " << endl;
            }
            for(int j=0; j<9; j++){
                if(j%3==0){
                    cout << "| ";
                }
                if(player_puzzle[i][j]==0){
                    cout << "  ";
                }
                else{
                    cout << player_puzzle[i][j] << " ";
                }
            }
            cout << "|" << endl;
        }
        int row=0, col=0, number=0;
        bool row_valid=true, col_valid=true, number_valid=true;
        do{
            cout << "Fill in a cell with your guess (row col number)." << endl;
            cin >> row >> col >> number;
            row--; col--;
            if(row>=0 && row<9){
                row_valid = true;
            }
            else{
                row_valid = false;
                cout << "Please choose a valid row!" << endl;
            }
            if(col>=0 && col<9){
                col_valid = true;
            }
            else{
                col_valid = false;
                cout << "Please choose a valid column!" << endl;
            }
            if(number>0 && number <10){
                number_valid = true;
            }
            else{
                number_valid = false;
                cout << "Please choose a valid number!" << endl;
            }
        }
        while(row_valid==false || col_valid==false || number_valid==false);
        if(puzzle[row][col]==number){
            player_puzzle[row][col] = number;
        }
        else{
            cout << "Boop boop boop! You guessed wrong!" << endl;
            lives--;
        }

    }
    if(lives==0){
        cout << "YOU DIED" << endl;
    }
    else{
        cout << "YOU WON! HERE'S A COOKIE!" << endl;
        cout << "                 Lives: " << lives << endl;
        for(int i=0; i<9; i++){
            if(i%3==0){
                cout << " _______________________ " << endl;
            }
            for(int j=0; j<9; j++){
                if(j%3==0){
                    cout << "| ";
                }
                if(player_puzzle[i][j]==0){
                    cout << "  ";
                }
                else{
                    cout << player_puzzle[i][j] << " ";
                }
            }
            cout << "|" << endl;
        }
    }



    return 0;
}