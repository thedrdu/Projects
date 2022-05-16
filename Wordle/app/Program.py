# a python transcribed version of the other one

# ord: str/char --> int
# chr: int --> char

wordlist = []
wordle_values = dict()
letter_occurs = dict()

green_letters = "     "
yellow_letters = dict()
gray_letters = []

def reset():
    wordle_values.clear()
    letter_occurs.clear()
    green_letters = ""
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
        possible = True
        for c in yellow_letters.keys(): #If str does not contain a known yellow letter at all
                if not c in str:
                    possible = False
                    break
        for i, c in enumerate(str):
            if str[i] in yellow_letters.keys(): #If str contains a known yellow letter, but at a known yellow index
                possible = False
                #goto Jump
            if str[i] in gray_letters:
                possible = False
                break
            if not green_letters[i] == ' ' and not str[i] == green_letters[i]: #If green letter exists at index i and str doesn't match it
                possible = False
                break
        if possible:
            possibilities.append(str)
    highest = 0
    output = "default_value"
    for s in possibilities:
        if wordle_values[s] > highest:
            highest = wordle_values[s]
            output = s
    return output
            
            

def main():
    solved = False
    for i in range(97, 123):
        letter_occurs[chr(i)] = 0

    # try loop?
    with open("WordList2.txt", "r") as file:
        wordlist = file.read().splitlines()

    for word in wordlist:
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


if __name__ == "__main__":
    main()