# a python transcribed version of the other one

# ord: str/char --> int
# chr: int --> char

import time


wordlist = []
wordle_values = dict()
letter_occurs = dict()

green_letters = "     "
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
                yellow_letters[guess[i]] = []
        else:
            gray_letters.append(guess[i])
    possible = True
    for str in wordle_values.keys():
        for i, c in enumerate(str):
            possible = True
            for c in yellow_letters.keys():
                if not c in str:
                    possible = False
                    #goto Jump
            if str[i] in yellow_letters.keys():
                
    
            
            
def main():
    solved = False
    for i in range(97, 123):
        letter_occurs[chr(i)] = 0

    # try loop?

    starttime = time.time()
    with open("WordList2.txt", "r") as file:
        wordlist = file.read().splitlines()

    for word in wordlist:
        if not word in worlde_values.keys
        # car.update({"color": "White"})
        # if(!(WordleValues.ContainsKey(line))){
        #                 WordleValues.Add(line, -1);


        #             }
        for c in word:
            letter_occurs[c] += 1
            
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
            print("deez nuts lmao")
        elif inp == "reset":
            print("Whoa, I didn't implement that yet")
            
        data = inp.split(' ')
        guess = generateGuess(data[0], data[1])
        print("Try guessing", guess)
    # try loop ends here

if __name__ == "__main__":
    main()