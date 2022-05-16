# a python transcribed version of the other one

# ord: key/char --> int
# chr: int --> char

#0=gray, 1=yellow, 2=green

# boobs 00000
# raile 21001
# redan 22010
# recta 22111
# react

import time

filename = "WordList.txt"

wordlist = []
wordle_values = dict()
letter_occurs = dict()

green_letters = [' ', ' ', ' ', ' ', ' ']
yellow_letters = dict()
gray_letters = []

def reset():
    wordle_values.clear()
    letter_occurs.clear()
    green_letters = "     "
    yellow_letters.clear()
    gray_letters.clear()

def generateGuess(guess, tiles):
    possibilities = []
    for i, c in enumerate(guess):
        if tiles[i] == '2':
            green_letters[i] = guess[i]
        elif tiles[i] == '1':
            if not guess[i] in yellow_letters.keys():
                yellow_letters[guess[i]] = [i]
            # NEED TO ADD AN ELSE STATEMENT TO APPEND TO KEY'S ARRAY VALUE OF INDEXES IF KEY ALREADY EXISTS IN YELLOW_LETTERS
        else:
            gray_letters.append(guess[i])
    possible = True
    #TODO: fix issue where conditions for possible are never met
    for key in wordle_values.keys():
        possible = True
        for c in yellow_letters.keys(): #If key does not contain a known yellow letter at all
            if not c in key:
                possible = False
                break
                #goto Jump
        for i, c in enumerate(key):
            if key[i] in yellow_letters.keys(): #If key contains a known yellow letter, but at a known yellow index
                possible = False
                #goto Jump
            if key[i] in gray_letters:
                possible = False
                break
            if not green_letters[i] == ' ' and not key[i] == green_letters[i]: #If green letter exists at index i and key doesn't match it
                possible = False
                break
        if possible:
            possibilities.append(key)
    #Testing
    print(green_letters)
    print(yellow_letters)
    print(gray_letters)
    highest = 0
    output = "PLACEHOLDER"
    print(len(possibilities))
    for s in possibilities:
        if wordle_values[s] > highest:
            print(s, wordle_values[s])
            highest = wordle_values[s]
            output = s
    return output
            
            

def main():
    solved = False
    for i in range(97, 123):
        letter_occurs[chr(i)] = 0

    # try loop?

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
            #figure out how to go to beginning of main
        data = inp.split(' ')
        guess = generateGuess(data[0], data[1])
        print("Try guessing", guess)
    # try loop ends here

if __name__ == "__main__":
    main()