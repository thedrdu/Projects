# a python transcribed version of the other one

# ord: str/char --> int
# chr: int --> char

wordlist = []
wordle_values = dict()
letter_occurs = dict()

green_letters = []
yellow_letters = dict()
gray_letters = []

def main():
    for i in range(97, 123):
        letter_occurs[chr(i)] = 0

    # try loop?
    with open("WordList2.txt", "r") as file:
        wordlist = file.read().splitlines()

    for word in wordlist:
        for c in word:
            letter_occurs[c] = letter_occurs[c] + 1
            
    print(letter_occurs)

if __name__ == "__main__":
    main()