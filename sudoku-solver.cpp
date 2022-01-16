#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/*
THIS FUNCTIONALITY WILL USE BACKTRACKING IN ORDER TO DERIVE A SOLUTION FOR THE GIVEN PUZZLE
*/


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

int main(int argc, char* argv[])
{
    if(argc<3){
        cout << "You are missing a file to read or write to..." << endl;
        return 1;
    }
    ifstream read;
    read.open(argv[1]);
    if(!read.is_open()){
        cout << "Cannot open the file" << endl;
        return 1;
    }
    int puzzle[9][9];
    /* READ 0'S AS EMPTY SPACES */
    string temp;
    read >> temp;
    read.close();
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            puzzle[j][i] = temp[9*i+j]-'0';
        }
    }
    if(!solver(puzzle,0,0)){
        cout << "This puzzle is unsolvable!" << endl;;
        return 0;
    }

    ofstream write;
    write.open(argv[2]);
    for(int i=0; i<9; i++){
        if(i%3==0){
            write << " _______________________ " << endl;
        }
        for(int j=0; j<9; j++){
            if(j%3==0){
                write << "| ";
            }
            write << puzzle[j][i] << " ";
        }
        write << "|" << endl;
    }
    write << " _______________________ " << endl;
    write.close();

    cout << "Puzzle has been solved!" << endl;

    return 0;
}