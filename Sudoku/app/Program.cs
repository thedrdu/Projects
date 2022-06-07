// Authors: thedrdu, rayros25

using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;

class WordleWordProcessor{
public static int gridSize = 9;
    public static void Main(string[] args){
        Console.Write("Input file name: ");
        string? filename = Console.ReadLine();
        int[,] grid = new int[gridSize, gridSize];

        using (StreamReader sr = new StreamReader(filename)){
            string? line;
            int i = 0, j = 0;
            while((line = sr.ReadLine()) != null)
            {
                string[] numbers = line.Split(' ');
                foreach(string s in numbers){
                    grid[i,j] = Int32.Parse(s);
                    i++;
                }
                i = 0;
                j++;
            }
        }
        //Should have a complete grid at this point.
        long startTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        if(solve(grid, 0, 0)){
            long endTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
            Console.WriteLine("Your solution:");
            print(grid);
            Console.WriteLine("Sudoku processed in: " + (endTime - startTime) + "ms");
        }
        else{
            Console.WriteLine("No solution.");
        }
    }

    public static void print(int[,] grid){
        string output = "";
        for(int i = 0; i < gridSize; i++){
            for(int j = 0; j < gridSize; j++){
                output += (grid[i,j]) + " ";
                if(j % 3 == 2 && j > 1 && j < 8){
                    output += "| ";
                }
            }
            if(i % 3 == 2 && i > 1 && i < 8){
                output += "\n---------------------";
            }
            output += "\n";
        }
        Console.Write(output);
    }

    public static bool solve(int[,] grid, int row, int col){
        //Termination condition: We're at the last tile.
        if(row == gridSize-1 && col == gridSize-1){ return true; }
        if(col == gridSize){ col = 0; row++; }
        if(grid[row,col] != 0){ return solve(grid, row, col + 1); }

        for(int i = 1; i < gridSize+1; i++){
            if(checkAttempt(grid, row, col, i)){
                grid[row,col] = i;
                if(solve(grid, row, col+1)){
                    return true;
                }
            }
            grid[row, col] = 0;
        }
        return false;
    }
    /*
        Checks if the 
    */
    public static bool checkAttempt(int[,] grid, int row, int col, int insert){
        //First we check for duplicates along the 4 cardinal directions
        for(int i = 0; i < gridSize; i++){
            if(grid[row, i] == insert){
                return false;
            }
        }
        for(int i = 0; i < gridSize; i++){
            if(grid[i, col] == insert){
                return false;
            }
        }
        //Now we check the box for duplicates. Note: Not modular with different box sizes.
        int startRow = ((row)/3) * 3, startCol = ((col)/3) * 3;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(grid[startRow + i, startCol + j] == insert){
                    return false;
                }
            }
        }
        //No duplicates found!
        return true;
    }
}