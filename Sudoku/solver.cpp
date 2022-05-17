/* sudoku solver
 * This program solves a sudoku puzzle
 * Written by thedrdu and rayros2025, 2022-05-17
 */

 #include <iostream>
 #include <fstream>

 using namespace std;

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
    int grid[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> grid[i][j];
        }
    }
    infile.close();
    return 0;
 }