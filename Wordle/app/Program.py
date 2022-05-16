# a python transcribed version of the other one

# file = open("WordList.txt", "r")
# wordlist = file.read().splitlines()
# print(wordlist)
# file.close()

wordlist = []

with open("WordList.txt", "r") as file:
    wordlist = file.read().splitlines()

print(wordlist[0])
print(wordlist[3])