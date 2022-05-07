# engg1340-project
Repository for ENGG1340 team project.


## Team Members:
  Jam Kabeer Ali Khan  
  Salvatore Patrick Yuanto  


## Game: 
  Notakto

## Game Description:
    This is a variant of tiktakto. It is more complex and fun. In this game,  
    there is no possible draw situation unlike tiktakto.  
    Here is a link to android app for this game: https://play.google.com/store/apps/details?id=com.counterwave.notakto&hl=en&gl=US  
    
    User will have the option of playing against computer or multiplayer.  
    Notakto has multiple tiktakto-like grids. User will be asked to select complexity and accordingly, number of grids will be increased.
    We will implement a algorithmic bot using the algorithm in this paper: https://arxiv.org/pdf/1301.1672v1.pdf 
    
    User will be asked to enter difficulty level and accordingly, we will set randomness in the decision-making of the bot
    to allow better chances for user to win.
    
    Following are the rules of the game:
    1. Every player will input a location on one of the grids where 'X' will be entered.
    2. When a line (vertical, horizontal or diagonal) is formed by 'X' in a grid then that grid will be removed from the game.
    3. Player which makes the last input which leads to the formation of a line and last grid removed will **LOSE**.
    4. Player which doesn't makes the last input will **WIN**.
    

## Implementation of Requirements:
### Requirement 1: Generation of random game sets or events
  Game can be played against computer. Depending on the difficulty level chosen by the player, we will enter the randomness into the bot.  
  That basically means that rather than following the bot algorithm and always making efficient moves, computer will make random moves to increase the chances for the player winning the game.  
  For example:  
  Difficulty level - Extremely Easy: All the moves made by the computer will be random.  
  Difficulty level - Medium: Some moves will be random, some with algorithm.  
  Difficulty level - Extremely Hard: All moves will be done using algorithm. It will be impossible for Player to win the game if choses to go second.  
  <br />
### Requirement 2: Data structures for storing game status
  We will be using **Multi-dimensional Arrays** for storing the grid status of the game.  

### Requirement 3: Dynamic memory management
  The variable storing the move will be storing a different input each round. The previous move will be cleared.
  
### Requirement 4: File input/output (e.g., for loading/saving game status)
  We will provide the option to save the game status which will output a file.
  The status can be loaded by taking the file as an input.

### Requirement 5: Program codes in multiple files
  We will split the functions into different files such as the main code/board initialisation/checking if there is a winner.


## Sample Input/Output Display:
<pre>
A      B      C  
X 1 X  0 X 2  0 X 2  
X X 5  3 4 5  3 4 5  
6 X 8  6 7 8  6 7 8  
Player 2: B4  
A      B      C  
X 1 X  0 X 2  0 X 2  
X X 5  3 X 5  3 4 5  
6 X 8  6 7 8  6 7 8  
Player 1: B7  
A      C  
X 1 X  0 X 2  
X X 5  3 4 5  
6 X 8  6 7 8  
Player 2: C0  
A      C  
X 1 X  X X 2  
X X 5  3 4 5  
6 X 8  6 7 8  
Player 1: C2  
A  
X 1 X  
X X 5  
6 X 8  
Player 2: A6  
Player 1 wins game  

</pre>
<br />


## Instructions for Compilation
<pre>
A makefile has been included 
Please type "make Notakto" to compile the game.
</pre>
<br />
