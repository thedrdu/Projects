/* sudoku solver
 * This program takes in a starting position for Sudoku and finds a solution via DFS.
 * Written by thedrdu and rayros2025, 2022-05-17
 * 
 * TODO: Check if input is valid.
 */

#include <iostream>
#include <fstream>

using namespace std;

int grid[9][9];
int answers[9][9];
int squares_filled = 0;

bool is_valid(int row, int col);
void next(int &row, int &col);
void prev(int &row, int &col);

void solve(int r, int c);

// these might be unnecessary
// bool check_rows(); //placeholder, not sure what params will be yet.
// bool check_cols(); //placeholder, not sure what params will be yet.
// bool check_boxes(); //placeholder, not sure what params will be yet.

int main() {
    cout << "Enter filename: ";
    string filename;
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    if (not infile.is_open()) {
        cerr << "ERROR: not valid file\n";
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> grid[i][j];
            answers[i][j] = grid[i][j];
            if (grid[i][j] != 0) { squares_filled++; }
        }
    }
    infile.close();

    // TODO: automatically find first open squares
    solve(0, 2);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << answers[i][j];
        }
        cout << endl;
    }
    return 0;
}

bool is_valid(int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (i != row and grid[i][col] == grid[row][col]) {
            return false;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (i != col and grid[row][i] == grid[row][col]) {
            return false;
        }
    }

    for (int i = row / 3; i < 3; i++) {
        for (int j = col / 3; j < 3; j++) {
            if (i != row and j != col and grid[i][j] == grid[row][col]) {
                return false;
            }
        }
    }

    return true;
}

void next(int &row, int &col) {
    do {
        col++;
        if (col >=9) {
            col = 0;
            row++;
        }
    } while (grid[row][col] != 0);
}

void prev(int &row, int &col) {
    do {
        col--;
        if (col < 0) {
            col = 8;
            row--;
        }
    } while (grid[row][col] != 0);
}

void solve(int r, int c) {
    if (squares_filled != 81) {
        answers[r][c]++;
        // if (answers[r][c] < 10) {
            cout << "trying " << answers[r][c] << " at row " << r 
                 << " col " << c << '\n'; 
        // }
        if (is_valid(r, c)) {
            squares_filled++;
            next(r, c);
            solve(r, c);
        }
        else {
            // solve(r, c);
            if (answers[r][c] >= 9) {
                return;
            }
            answers[r][c] = 0;
            squares_filled--;
            prev(r, c);
            solve(r, c);
        }
    }
}
