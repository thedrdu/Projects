/* sudoku solver
 * This program takes in a starting position for Sudoku and finds 
 * a solution via DFS.
 * Written by thedrdu and rayros2025, 2022-06-07
 */

#include <iostream>
#include <fstream>
// #include <unordered_set>     TODO: This doesn't seem to be used. Delete?

using namespace std;

const int GRIDSIZE = 9;
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
    if (solve(0, 0)) {
        cout << "Your solution: ";
        print();
    }
    else {
        cout << "No solution.\n";
    }

    return 0;
} 


// print
// Purpose: print out the sudoku grid, with lines
void print() {
    string output = "\n";
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            output += to_string(grid[i][j]) + " ";
            if (j % 3 == 2 and 1 < j and j < 8) {
                output += "| ";
            }
            // output.TrimEnd();
        }
        if (i % 3 == 2 and 1 < i and i < 8) {
            output += "\n---------------------";
        }
        output += "\n";
    }
    cout << output;
}

// solve
// Purpose: solve
// Args: row index and column index
// Returns: true if grid can be solved, false if not
bool solve(int r, int c) {
    if (r == GRIDSIZE - 1 and c == GRIDSIZE - 1) { //At the final tile
        return true;
    }

    if (c == GRIDSIZE) {
        c = 0; 
        r++;
    }

    if (grid[r][c] != 0) {
        return solve(r, c + 1);
    }

    for (int i = 1; i <= GRIDSIZE; i++) {
        if (checkAttempt(r, c, i)) {
            grid[r][c] = i;

            if (solve(r, c + 1)) {
                return true;
            }
        }
        grid[r][c] = 0;
    }

    return false;
}

// checkAttempt
// Args: a row index, a column index, and a value to be checked
// Returns: true if insert is a valid answer at [r,c] and false if not
bool checkAttempt(int r, int c, int insert) {
    // check for dupes in same column
    for (int i = 0; i < GRIDSIZE; i++) {
        if (grid[r][i] == insert) {
            return false;
        }
    }
    // check for dupes in same row
    for (int i = 0; i < GRIDSIZE; i++) {
        if (grid[i][c] == insert) {
            return false;
        }
    }
    // check for dupes in same box
    // NOTE: this is assuming a standard 9x9 Sudoku grid
    int startRow = (r / 3) * 3;
    int startCol = (c / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == insert) {
                return false;
            }
        }
    }
    //No duplicates found!
    return true;
}