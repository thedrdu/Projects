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
void next(int &i, int &j);
void prev(int &i, int &j);

void solve(int r, int c);

// these might be unnecessary
// bool check_rows(); //placeholder, not sure what params will be yet.
// bool check_cols(); //placeholder, not sure what params will be yet.
// bool check_boxes(); //placeholder, not sure what params will be yet.

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
            answers[i][j] = grid[i][j];
            if (grid[i][j] != 0) { squares_filled++; }
        }
    }
    infile.close();

    // ok, we have a 2D grid. now what?
    solve(0, 0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << answers[i][j];
        }
        cout << endl;
    }
    return 0;
} 

bool is_valid(int row, int col) {
    // cout << "row check\n";
    for (int i = 0; i < 9; i++) {
        if (i != row and grid[row][col] != 0 and grid[i][col] == grid[row][col]) {
            return false;
        }
    }

    // cout << "col check\n";
    for (int i = 0; i < 9; i++) {
        if (i != col and grid[row][col] != 0 and grid[row][i] == grid[row][col]) {
            return false;
        }
    }

    // cout << "box check\n";
    for (int i = row / 3; i < 3; i++) {
        for (int j = col / 3; j < 3; j++) {
            if (i != row and j != col and grid[row][col] != 0 and grid[i][j] == grid[row][col]) {
                return false;
            }
        }
    }

    return true;
}

void next(int &i, int &j) {
    do {
        i++;
        if (i >=9) {
            i = 0;
            j++;
        }
    } while (grid[i][j] != 0);
}

void prev(int &i, int &j) {
    do {
        i--;
        if (i < 0) {
            i = 8;
            j--;
        }
    } while (grid[i][j] != 0);
}

void solve(int r, int c) {
    cout << "squares_filled:" << squares_filled << '\n';
    if (squares_filled != 81) {
        answers[r][c]++;
        //if (answers[r][c] < 10) {
            cout << "trying " << answers[r][c] << " at row " << r 
                 << " col " << c << '\n'; 
        // }
        bool your_mom = is_valid(r,c);
        cout << "valid:" << your_mom << '\n';
        if (your_mom) {
            squares_filled++;
            next(r, c);
            solve(r, c);
        }
        else {
            solve(r, c);
            if (answers[r][c] >= 9) {
                answers[r][c] = 0;
                squares_filled--;
                prev(r, c);
                solve(r, c);
            }
        }
    }
}
