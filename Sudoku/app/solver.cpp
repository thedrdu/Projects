/* sudoku solver
 * This program takes in a starting position for Sudoku and finds a solution via DFS.
 * Written by thedrdu and rayros2025, 2022-05-17
 * 
 */

#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int gridSize = 9;
int grid[9][9];

void print();
bool solve(int r, int c);
bool checkAttempt(int r, int c, int insert);

int main(int argc, char *argv[]) {
    string filename;

    if (argc == 1) {
        cout << "Enter filename: ";
        cin >> filename;
    } 
    else if (argc == 2) {
        filename = argv[1];
    }
    else {
        cerr << "ERROR: invalid number of arguments\n";
        exit(EXIT_FAILURE);
    }

    ifstream infile;
    infile.open(filename);
    if (not infile.is_open()) {
        cerr << "ERROR: not valid file\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> grid[i][j];
        }
    }
    infile.close();

    // ok, we have a 2D grid. now what?
    if(solve(0, 0)){
        cout << "Your solution:";
        print();
    }
    else{
        cout << "No solution.";
    }
    return 0;
} 

void print(){
    string output = "\n";
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            output += std::to_string(grid[i][j]) + " ";
            if(j % 3 == 2 && j > 1 && j < 8){
                output += "| ";
            }
            // output.TrimEnd();
        }
        if(i % 3 == 2 && i > 1 && i < 8){
            output += "\n-----------------------";
        }
        output += "\n";
    }
    cout << output;
}

bool solve(int r, int c) {
    if(r == gridSize-1 && c == gridSize-1){ //At the final tile
        return true;
    }
    if(c == gridSize){
        c = 0; r++;
    }
    if(grid[r][c] != 0){
        return solve(r, c + 1);
    }
    for(int i = 1; i < gridSize+1; i++){
        if(checkAttempt(r, c, i)){
            grid[r][c] = i;
            if(solve(r, c + 1)){
                return true;
            }
        }
        grid[r][c] = 0;
    }
    return false;
}

bool checkAttempt(int r, int c, int insert){
    //First we check for duplicates along the 4 cardinal directions
    for(int i = 0; i < gridSize; i++){
        if(grid[r][i] == insert){
            return false;
        }
    }
    for(int i = 0; i < gridSize; i++){
        if(grid[i][c] == insert){
            return false;
        }
    }
    //Now we check the box for duplicates. Note: Not modular with different box sizes.
    int startRow = ((r)/3) * 3, startCol = ((c)/3) * 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(grid[startRow + i][startCol + j] == insert){
                return false;
            }
        }
    }
    //No duplicates found!
    return true;
}