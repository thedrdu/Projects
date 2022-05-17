# Python program designed to help user solve Wordle
#
# Note: Outdated and incomplete. May not work.
#
# Usage: User provides their guess and the feedback they got from it (the
# green, yellow, and grey squares). They input this into the script, and they 
# are provided with a guess based on the data provided.
#
# Written by: thedrdu and rayros25
#
# Last updated 2022-05-16

import time

# Name of file where words are stored
filename = "WordList.txt"

# Stores words from word list
wordlist = []
# Stores word and corresponding "strength value" (to be computed later)
wordle_values = dict()
# Stores occurrences of each letter
letter_occurs = dict()

# Stores characters with a green tile at the correct final index
green_letters = [' ', ' ', ' ', ' ', ' ']
# Stores character and an ArrayList of indexes(int)
yellow_letters = dict()
# Stores all characters with a gray tile
gray_letters = []

# reset
# used to reset all structures without exiting the program
def reset():
    wordle_values.clear()
    letter_occurs.clear()
    green_letters = "     "
    yellow_letters.clear()
    gray_letters.clear()

# generateGuess
# Idea: Try to find words that match criteria we have, then pick the one with 
# the highest strength value. Pass in string guess and string tileColors 
# (ex. 01221), 0=gray, 1=yellow, 2=green, then make a guess.
def generateGuess(guess, tiles):
    possibilities = []
    for i, c in enumerate(guess):
        if tiles[i] == '2':
            green_letters[i] = guess[i]
        elif tiles[i] == '1':
            if not guess[i] in yellow_letters.keys():
                yellow_letters[guess[i]] = [i]
            else:
                yellow_letters[guess[i]].append(i)
        else:
            gray_letters.append(guess[i])
    possible = True
    # TODO: fix issue where conditions for possible are never met
    for key in wordle_values.keys():
        possible = True
        for c in yellow_letters.keys(): 
            # If key does not contain a known yellow letter at all
            if not c in key:
                possible = False
                break
        for i, c in enumerate(key):
            if key[i] in yellow_letters.keys(): 
                # If key contains a known yellow letter, 
                # but at a known yellow index
                if i in yellow_letters[key[i]]:
                    possible = False
                    break
            if key[i] in gray_letters:
                possible = False
                break
            if not green_letters[i] == ' ' and not key[i] == green_letters[i]: 
                #If green letter exists at index i and key doesn't match it
                possible = False
                break
        if possible:
            possibilities.append(key)
    # Testing prints
    # print("GREEN", green_letters)
    # print("YELLOW", yellow_letters)
    # print("GRAY", gray_letters)
    highest = 0
    output = "PLACEHOLDER"
    # print("length of pos", len(possibilities))
    for s in possibilities:
        if wordle_values[s] > highest:
            print(s, wordle_values[s])
            highest = wordle_values[s]
            output = s
    return output


# main
# handles user input
def main():
    solved = False
    for i in range(97, 123):
        letter_occurs[chr(i)] = 0

    # try loop starts here
    starttime = time.time()
    with open(filename, "r") as file:
        wordlist = file.read().splitlines()

    for word in wordlist:
        if not word in wordle_values.keys():
            wordle_values.update({word : -1})
            for c in word:
                letter_occurs[c] += 1

    endtime = time.time()
    print("WordList processed in", endtime - starttime, "secs")
            
    visited_letters = []
    occurence_sum = 0.0
    for word in wordlist:
        visited_letters.clear()
        occurence_sum = 0.0
        for c in word:
            if not c in visited_letters:
                occurence_sum += letter_occurs[c]
            visited_letters.append(c)
        wordle_values[word] = occurence_sum / (len(wordlist) * 5)

    print("Ready!")

    #TODO: check for errors and stuff
    while not solved:
        inp = input("Enter input or command: ")
        if inp == "exit":
            print("Thanks for using me!")
            solved = True
            break
        elif inp == "reset":
            reset()
            # TODO: figure out how to go to beginning of main
        data = inp.split(' ')
        guess = generateGuess(data[0], data[1])
        print("Try guessing", guess)
    # try loop ends here


# guard clause
if __name__ == "__main__":
    main()
