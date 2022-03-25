# engg1340-project
Repository for ENGG1340 team project.


## Team Members:
  Jam Kabeer Ali Khan,
  Salvatore Patrick Yuanto


## Game: Notakto

## Game Description:
    This is a variant of tiktakto. It is more complex and fun. In this game,__
    there is no possible draw situation unlike tiktakto.__
    Here is a link to android app for this game: https://play.google.com/store/apps/details?id=com.counterwave.notakto&hl=en&gl=US __
    <br />
    User will have the option of playing against computer or multiplayer.__
    Notakto has multiple tiktakto-like grids. User will be asked to select complexity and accordingly, number of grids will be increased.__
    We will implement a algorithmic bot using the algorithm in this paper: https://arxiv.org/pdf/1301.1672v1.pdf __
    <br />
    User will be asked to enter difficulty level and accordingly, we will set randomness in the decision-making of the bot__
    to allow better chances for user to win.__
    <br />
    Following are the rules of the game:__
    1. Every player will input a location on one of the grids where 'X' will be entered.__
    2. When a line (vertical, horizontal or diagonal) is formed by 'X' in a grid then that grid will be removed from the game.__
    3. Player which makes the last input which leads to the formation of a line and last grid removed will **LOSE**.__
    4. Player which doesn't makes the last input will **WIN**.__
<br />
<br />
## Implementation of Requirements:
### Requirement 1: Generation of random game sets or events
  Game can be played against computer. Depending on the difficulty level chosen by the player, we will enter the randomness into the bot.__
  That basically means that rather than following the bot algorithm and always making efficient moves, computer will make random moves to increase the__
  chances for the player winning the game.__
  For example:__
  Difficulty level - Extremely Easy: All the moves made by the computer will be random.__
  Difficulty level - Medium: Some moves will be random, some with algorithm.__
  Difficulty level - Extremely Hard: All moves will be done using algorithm. It will be impossible for Player to win the game if choses to go second.__
  <br />
### Requirement 2: Data structures for storing game status
  We will be using **Multi-dimensional Arrays** for storing the grid status of the game.__

### Requirement 3: Dynamic memory management

### Requirement 4: File input/output (e.g., for loading/saving game status)

### Requirement 5: Program codes in multiple files


## Sample Input/Output Display:
A      B      C__
X 1 X  0 X 2  0 X 2__
X X 5  3 4 5  3 4 5__
6 X 8  6 7 8  6 7 8__
Player 2: B4__
A      B      C__
X 1 X  0 X 2  0 X 2__
X X 5  3 X 5  3 4 5__
6 X 8  6 7 8  6 7 8__
Player 1: B7__
A      C__
X 1 X  0 X 2__
X X 5  3 4 5__
6 X 8  6 7 8__
Player 2: C0__
A      C__
X 1 X  X X 2__
X X 5  3 4 5__
6 X 8  6 7 8__
Player 1: C2__
A__
X 1 X__
X X 5__
6 X 8__
Player 2: A6__
Player 1 wins game__
<br />
