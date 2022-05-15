// See https://aka.ms/new-console-template for more information

using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;

class WordleWordProcessor{
    
    public static void Main(string[] args){
        //Stores total # of letters(5 * # of words)
        int totalLetters;
        //Stores word and corresponding "strength value"(to be computed later).
        Dictionary<string, double> WordleValues = new Dictionary<string, double>();

        //Stores occurrences of each letter.
        Dictionary<char, int> LetterOccurrences = new Dictionary<char, int>();
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
            //Solution: Visited ArrayList to hold all checked letters so far.
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


        }
        catch (Exception e){
            Console.WriteLine("error: " + e.Message);
        }
    }
}