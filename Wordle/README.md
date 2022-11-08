# Wordle Solver

Given a list of words, the program uses one-shot learning to compute weights, and gives the best guesses available at each step based on user input. <br />
Available in C# and Python(outdated).

## Instructions
Input your initial guess and then the tile result(format: "guess" + "tiles", where tiles is a 5 digit number with 0=gray, 1=yellow, 2=green) <br />
ex: "tears 12210"

The algorithm will give you the next best word to guess.

## Other commands:
exit - exits program <br />
reset - resets all constructors without exiting program. <br />
test - bruteforces the average # of guesses per word in the given WordList(very slow). <br />

NOTE: Not *fully* optimal. There is no placement analysis. WordList may also be outdated.
