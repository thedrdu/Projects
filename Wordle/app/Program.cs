// See https://aka.ms/new-console-template for more information

using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;

class WordleWordProcessor{

    //Stores total # of letters(5 * # of words).
    static int totalLetters;
    //Stores word and corresponding "strength value"(to be computed later).
    static Dictionary<string, double> WordleValues = new Dictionary<string, double>();

    //Stores occurrences of each letter.
    static Dictionary<char, int> LetterOccurrences = new Dictionary<char, int>();

    //Need some struct that stores green/yellow letters and their index
    static char[] GreenLetters = new char[5];
    static Dictionary<char, ArrayList> YellowLetters = new Dictionary<char, ArrayList>();
    static ArrayList GrayLetters = new ArrayList();
    

    /*  generateGuess()
    Goal: Given a Dictionary of the previous guess, make the next guess.
    Idea: Try to find words that match criteria we have, then pick the one with the highest strength value.
    Pass in string tileColors(ex. 01221), 0=gray, 1=yellow, 2=green, then make a guess. Start with 00000
    Need a way to store index of tiles.
    */
    public static string generateGuess(string guess, string tiles){
        ArrayList Possibilities = new ArrayList();
        //Checks for green letters and adds to GreenLetters if applicable.
        for(int i = 0; i < guess.Length; i++){
            Console.WriteLine("tiles[i] is " + tiles[i]);
            if(tiles[i].Equals('2')){
                Console.WriteLine("Green Located");
                GreenLetters[i] = guess[i];
            }
            else if(tiles[i].Equals('1')){ //If yellow at index i
                Console.WriteLine("Yellow Located");
                if(!YellowLetters.ContainsKey(guess[i])){ //If char is not already in list, add to the list with the index
                    YellowLetters.Add(guess[i], new ArrayList{i});
                }
                else if(!YellowLetters[guess[i]].Contains(i)){ //char is already in the list
                    YellowLetters[guess[i]].Add(i); //If index is not already listed, add the new index
                }
            }
            else{
                Console.WriteLine("Gray Located");
                GrayLetters.Add(guess[i]);
            }
        }
        //Now we have an updated GrayLetters, YellowLetters(stores index) and GreenLetters(stores index). We can now form our next guess.
        //Need to find words that contain all yellows, and all greens at the right spots, and no grays.
        bool possible = true;
        bool containsYellow = false;

        foreach(string str in WordleValues.Keys){
            for(int i = 0; i < str.Length; i++){
                possible = true;
                containsYellow = false;
                foreach(char c in YellowLetters.Keys){ //If str does not contain a known yellow letter at all
                    if(!str.Contains(c)){
                        //Console.Write("str does not contain a known yellow.");
                        possible = false;
                        goto Jump;
                    }
                }
                if(YellowLetters.ContainsKey(str[i])){
                    if((YellowLetters[str[i]].Contains(i))){//If str contains a known yellow letter, but at a known yellow index
                        //Console.Write("str contains a known yellow at the wrong index.");
                        possible = false;
                        goto Jump;
                    }
                }
                if(GrayLetters.Contains(str[i])){ //If str contains a known gray letter
                    //Console.Write("str contains a known gray letter.");
                    possible = false;
                    break;
                }
                if(GreenLetters[i] != 0 && str[i] != GreenLetters[i]){ //If green letter exists at index i and str doesn't match it
                    //Console.Write("str is missing a green letter at index " + i + ".");
                    possible = false;
                    break;
                }
                
            }
            Jump: continue;
            if(possible){
                Console.WriteLine("Located possible word! ");
                Possibilities.Add(str);
            }
        }

        Console.WriteLine();
        Console.Write("GreenLetters contains: [");
        foreach(char c in GreenLetters){
            Console.Write(c + " ");
        }
        Console.WriteLine("]");
        Console.Write("YellowLetters contains: [");
        foreach(KeyValuePair<char,ArrayList> kv in YellowLetters){ 
            Console.Write(kv.Key + ": ");
            foreach(int i in kv.Value){
                Console.Write(i + " ");
            }
        }
        Console.WriteLine("]");

        double highest = 0;
        string output = "default_value";
        Console.WriteLine("Possibilities size is " + Possibilities.Count);
        foreach(string s in Possibilities){
            if(WordleValues[s] > highest){
                highest = WordleValues[s];
                output = s;
            }
        }
        Console.WriteLine("Output is " + output);
        return output;
    }
    public static void Main(string[] args){
        bool solved = false;
        for(int i = 97; i <= 122; i++){
            LetterOccurrences.Add(Convert.ToChar(i), 0);
        }

        try{
            // Create an instance of StreamReader to read from a file.
            using (StreamReader sr = new StreamReader("WordList.txt"))
            {
                string line;
                // Adds all words into a Dictionary of <Word,Value> pairing. Sets initial value to -1.
                // TODO: check for duplicate words
                while((line = sr.ReadLine()) != null)
                {
                    if(!(WordleValues.ContainsKey(line))){
                        WordleValues.Add(line, -1);
                    }
                    //Console.WriteLine(line);
                }
            }

            //Set totalLetters to 5 * # of words
            totalLetters = WordleValues.Count*5;

            //Add all the letters in all given words to LetterOccurrences
            foreach(string str in WordleValues.Keys){
                foreach(char c in str){
                    LetterOccurrences[c]++;
                }
            }

            //TESTING: For each character, print its occurrence count. 
            // foreach(KeyValuePair<char, int> kv in LetterOccurrences){
            //     Console.WriteLine(kv.Key + ": " + kv.Value);
            // }

            //TESTING: Print totalLetters
            //Console.WriteLine("totalLetters: " + totalLetters);

            //Idea: For each word, add its 5 letters' occurrences(OccurrenceSum) and then divide by totalLetters to get a strength value.
            //Problem: Duplicate letters in a word.
            //Solution: "visited" ArrayList to hold all checked letters so far.
            double OccurrenceSum = 0;
            ArrayList visited = new ArrayList();
            foreach(string str in WordleValues.Keys){
                OccurrenceSum = 0;
                visited.Clear();
                foreach(char c in str){
                    if(!visited.Contains(c)){
                        OccurrenceSum += LetterOccurrences[c];
                    }
                    visited.Add(c);
                }
                WordleValues[str] = OccurrenceSum/totalLetters;
            }

            //TESTING: Print in ascending strength value order.
            foreach (KeyValuePair<string,double> kv in WordleValues.OrderBy(key=> key.Value)){ 
                Console.WriteLine(kv.Key + ": " + kv.Value);
            }

            string guess;
            string tiles;
            Console.WriteLine("hello!");
            while(!solved){
                Console.WriteLine("Input guess and tiles: ");
                string line = Console.ReadLine();
                var data = line.Split(' ');
                guess = data[0]; //first input
                tiles = data[1]; //second input
                if(tiles == "22222"){
                    solved = true;
                }
                Console.WriteLine("guess is " + guess + ", tiles is " + tiles);
                Console.WriteLine(generateGuess(guess, tiles));
            }
        }
        catch (Exception e){
            Console.WriteLine("error: " + e.Message);
        }
    }
}