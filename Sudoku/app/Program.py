import time
import numpy as np

GRIDSIZE = 9
grid = [[0] * GRIDSIZE for i in range(GRIDSIZE)]

def print_grid():
    print(np.matrix(grid))

def solve(row, col):
    if row == GRIDSIZE - 1 and col == GRIDSIZE - 1:
        return True
    if col == GRIDSIZE:
        col = 0
        row += 1
    if grid[row][col] != 0:
        return solve(row, col+1)

    for i in range(1, GRIDSIZE + 1):
        if check_attempt(row, col, i):
            grid[row][col] = i
            if solve(row, col + 1):
                return True

def check_attempt(row, col, insert):
    #Check 4 cardinal directions
    for i in range(0, GRIDSIZE):
        if grid[row][i] == insert:
            return False
    for i in range(0, GRIDSIZE):
        if grid[i][col] == insert:
            return False
    #Check boxes
    start_row = (row/3) * 3
    start_col = (col/3) * 3
    for i in range(0,3):
        for j in range(0,3):
            if grid[start_row + i][start_col + j] == insert:
                return False
    return True #no duplicates found

def main():
    print