#include <bits/stdc++.h> 
using namespace std;
//Finding the block number of one of the 9x9 cells
int findBlock(int row, int col) {
        return (row / 3) * 3 + col / 3;
    }
bool solve(vector<vector<int>>& board, vector<vector<int>>& rows, vector<vector<int>>& cols, vector<vector<int>>& blocks) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) { //if the cell value is zero(here zero represents an empty cell)
                    for (int num = 1; num <= 9; num++) { //check for among all numbers 1-9 which can be possibly filled
                        int block = findBlock(row, col);
                        if (rows[row][num - 1] == 0 && cols[col][num - 1] == 0 && blocks[block][num - 1] == 0) {
                            board[row][col] = num ;
                            rows[row][num - 1] = 1;
                            cols[col][num - 1] = 1;
                            blocks[block][num - 1] = 1;

                            if (solve(board, rows, cols, blocks)) { //recursively call the solve function to attempt to solve the rest of the board
                                return true;
                            }

                            board[row][col] = 0;
                            rows[row][num - 1] = 0;
                            cols[col][num - 1] = 0;
                            blocks[block][num - 1] = 0;
                        }
                    }
                    return false; // tried all numbers from 1 to 9 for an empty cell but none returned a valid board
                }
            }
        }
        return true;
    }

void solveSudoku(vector<vector<int>>& board)
{
	    vector<vector<int>> rows(9, vector<int>(9, 0));
        vector<vector<int>> cols(9, vector<int>(9, 0));
        vector<vector<int>> blocks(9, vector<int>(9, 0));
//Hashing the required integers into respective hashTables
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != 0) {
                    int num = board[i][j];
                    rows[i][num - 1] = 1;
                    cols[j][num - 1] = 1;
                    blocks[findBlock(i, j)][num - 1] = 1;
                }
            }
        }

        solve(board, rows, cols, blocks);
}
int main(){
    vector<vector<int>> board = {
        {0,0,2,0,8,0,0,0,0},
        {0,0,3,0,0,0,0,0,6},
        {4,0,0,1,2,0,0,8,0},
        {0,3,0,2,0,0,0,0,1},
        {0,6,0,8,0,1,0,3,0},
        {1,0,0,0,0,9,0,4,0},
        {0,9,0,0,4,2,0,0,5},
        {6,0,0,0,0,03,0,0,},
        {0,0,0,0,9,0,8,0,0,}
    };
    solveSudoku(board);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
