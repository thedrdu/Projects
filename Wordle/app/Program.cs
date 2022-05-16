// Authors: thedrdu, rayros25

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

    //Stores characters with a green tile at the correct final index.
    static char[] GreenLetters = new char[5];
    //Stores character and an ArrayList of indexes(int).
    static Dictionary<char, ArrayList> YellowLetters = new Dictionary<char, ArrayList>();
    //Stores all characters with a gray tile.
    static ArrayList GrayLetters = new ArrayList();
    
    //Resets all structures without exiting program.
    public static void reset(){
        WordleValues.Clear();
        LetterOccurrences.Clear();
        for(int i = 0; i < GreenLetters.Length; i++){
                GreenLetters[i] = '\0';
        }
        YellowLetters.Clear();
        GrayLetters.Clear();
    }

    /*  generateGuess()
    Idea: Try to find words that match criteria we have, then pick the one with the highest strength value.
    Pass in string guess and string tileColors(ex. 01221), 0=gray, 1=yellow, 2=green, then make a guess.
    */
    public static string generateGuess(string guess, string tiles){
        ArrayList Possibilities = new ArrayList();
        long startTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        for(int i = 0; i < guess.Length; i++){
            //Console.WriteLine("tiles[i] is " + tiles[i]);
            if(tiles[i].Equals('2')){ //Checks for green letters and adds to GreenLetters if applicable.
                //Console.WriteLine("Green Located");
                GreenLetters[i] = guess[i];
            }
            else if(tiles[i].Equals('1')){ //Checks for yellow letters at index i and adds to YellowLetters with said index.
                //Console.WriteLine("Yellow Located");
                if(!YellowLetters.ContainsKey(guess[i])){ //If char is not already in list, add to the list with the index.
                    YellowLetters.Add(guess[i], new ArrayList{i});
                }
                else if(!YellowLetters[guess[i]].Contains(i)){ //If char is already in the list, add to the ArrayList of indexes.
                    YellowLetters[guess[i]].Add(i);
                }
            }
            else{ //If the tile is not green or yellow, then we add to GrayLetters.
                //Console.WriteLine("Gray Located");
                GrayLetters.Add(guess[i]);
            }
        }
        //Now we have an updated GrayLetters, YellowLetters(stores index) and GreenLetters(stores index). We can now form our next guess.
        //Need to find words that contain all yellows not at prior spots, and all greens at known spots, and no grays.
        bool possible = true;
        foreach(string str in WordleValues.Keys){
            possible = true;
            foreach(char c in YellowLetters.Keys){ //If str does not contain a known yellow letter at all
                    if(!str.Contains(c)){
                        //Console.Write("str does not contain a known yellow.");
                        possible = false;
                        goto Jump;
                    }
                }
            for(int i = 0; i < str.Length; i++){
                if(YellowLetters.ContainsKey(str[i])){
                    if((YellowLetters[str[i]].Contains(i))){ //If str contains a known yellow letter, but at a known yellow index
                        //Console.Write("str contains a known yellow at the wrong index.");
                        possible = false;
                        goto Jump;
                    }
                }
                if(GrayLetters.Contains(str[i])){ //If str contains a known gray letter
                    //Console.Write("str contains a known gray letter.");
                    possible = false;
                    goto Jump;
                }
                if(GreenLetters[i] != 0 && str[i] != GreenLetters[i]){ //If green letter exists at index i and str doesn't match it
                    //Console.Write("str is missing a green letter at index " + i + ".");
                    possible = false;
                    goto Jump;
                }
            }
            Jump: //Serves as a break of sorts.
            if(possible){
                //Console.WriteLine("Located possible word! ");
                Possibilities.Add(str);
            }
        }

        //TESTING: Print contents of all structures storing tile colors
        // Console.WriteLine();
        // Console.Write("GreenLetters contains: [");
        // foreach(char c in GreenLetters){
        //     Console.Write(c + " ");
        // }
        // Console.WriteLine("]");
        // Console.Write("YellowLetters contains: [");
        // foreach(KeyValuePair<char,ArrayList> kv in YellowLetters){ 
        //     Console.Write(kv.Key + ": ");
        //     foreach(int i in kv.Value){
        //         Console.Write(i + " ");
        //     }
        // }
        // Console.WriteLine("]");

        double highest = 0;
        string output = "default_value";
        //Console.WriteLine("Possibilities size is " + Possibilities.Count);
        foreach(string s in Possibilities){
            //Console.WriteLine(s + ": " + WordleValues[s]);
            if(WordleValues[s] > highest){
                highest = WordleValues[s];
                output = s;
            }
        }
        long endTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        Console.Write("(" + (endTime - startTime) + "ms) ");
        //Console.WriteLine("Output is " + output + " with strength value of " + WordleValues[output]);
        return output;
    }
    public static void Main(string[] args){
        Start:
        bool solved = false;
        //Add each letter with initial frequency 0
        for(int i = 97; i <= 122; i++){
            LetterOccurrences.Add(Convert.ToChar(i), 0);
        }
        try{
            long startTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
            using (StreamReader sr = new StreamReader("WordList.txt"))
            {
                string? line;
                // Adds all words into a Dictionary of <Word,Value> pairing. Sets initial value to -1.
                while((line = sr.ReadLine()) != null)
                {
                    if(!(WordleValues.ContainsKey(line))){
                        WordleValues.Add(line, -1);
                    }
                }
            }
            long endTime = DateTimeOffset.Now.ToUnixTimeMilliseconds();
            Console.WriteLine("WordList processed in: " + (endTime - startTime) + "ms");

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
            // foreach (KeyValuePair<string,double> kv in WordleValues.OrderBy(key=> key.Value)){ 
            //     Console.WriteLine(kv.Key + ": " + kv.Value);
            // }

            Console.WriteLine("Ready!");

            //TESTING: audio vs penis
            // Console.Write("audio: " + WordleValues["audio"] + " letters: ");
            // foreach(char c in "audio"){
            //     Console.Write(c + ": " + LetterOccurrences[c] + "  ");
            // }
            // Console.WriteLine();
            // Console.Write("penis: " + WordleValues["penis"] + " letters: ");
            // foreach(char c in "penis"){
            //     Console.Write(c + ": " + LetterOccurrences[c] + "  ");
            // }

            string guess;
            string tiles;
            //Console.WriteLine("hello!");
            while(!solved){
                Console.Write("Enter input or command: ");
                string? line = Console.ReadLine(); //Takes in input as one string
                if(line == "exit"){ //Exit program
                    solved = true;
                    Console.WriteLine("Thanks for using me!");
                    break;
                }
                else if(line == "reset"){ //Reset all structures without exiting program
                    reset();
                    goto Start;
                }
                #pragma warning disable CS8602 //Situation where input is not valid will not cause any issues.
                var data = line.Split(' ');
                guess = data[0]; //first input
                tiles = data[1]; //second input
                //Console.WriteLine("guess is " + guess + ", tiles is " + tiles);
                Console.WriteLine("Try guessing " + generateGuess(guess, tiles) + ".");
            }
        }
        catch (Exception e){
            Console.WriteLine("error: " + e.Message);
        }
    }
}