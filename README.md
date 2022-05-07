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
    3. Player which makes the last input which leads to the formation of a line and the last grid removed will **LOSE**.
    4. Player which doesn't makes the last input will **WIN**.
    
    Sample Move: A4
    Meaning: X will be marked on the 4th position of the grid A


## Installation and Running the Game:

Command-line commands to run project: 
<pre>
    g++ -pedantic-errors -std=c++11 main.cpp AI_Bot.cpp Grid_Functions.cpp FileIO.cpp -o Notakto  
    ./Notakto  
</pre>
A Makefile has been added to the project. It can be used with the following command to compile the project.

<br>

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
  We have used Map and Vectors from Standard Template Library (STL) to implement Data Structures for storing game status. Maps with string as keys and vectors as the items is used to store the Notakto grids used in this game. We have used Struct as a user-defined data type for coordinates inputed by the user.

### Requirement 3: Dynamic memory management
  We have the Notakto Grids stored inside Maps with strings as key and vectors (which store the single notakto grids). These grids are initialized according to the input from the user and then, once a cross-line of 3 X's is formed, just like in TikTakTo, that grid or key of our map data structure is erased and therefore, memory is automatatically released.
  
### Requirement 4: File input/output (e.g., for loading/saving game status)
  1. File q_values.txt stores the needed data values for our AI bot to work. These values are read when the program is started and stored inside a map data structure.
  2. User can save the game status in a file and then, user has the option to load the game from the where they left. When users asks to save the game, a file is created and game status is stored inside it. On Next game, user can choose to load their old game and continue from where they left. If there is a saved file then that game will be loaded otherwise program will output that there is no game saved.
  3. Welcome and Game ending messages are stored in files. These are read

### Requirement 5: Program codes in multiple files
  We have divided our code into following files:
  1. main.cpp
  2. AI_Bot.cpp
  3. Grid_Functions.cpp
  4. FileIO.cpp
  
  We have used header files to break the code into multiple files.

### Requirement 6 & 7:
  We have followed same code style across the project. We have made sure that our code remains efficient and readable by adding proper indentations, comments and 
  meaningful variable names. We have added extensive comments for complex functions, especially those of AI_Bot.cpp


## Sample Input/Output Display:

We have added 3 sample input output files inside the project. However, please note that our output or input may not remain consistent since we have used random functionality to generate some moves in our code. Therefore, output may not be the same for same input.

<pre>
             _        _    _        
            | |      | |  | |
 _ __   ___ | |_ __ _| | _| |_ ___
| '_ \ / _ \| __/ _` | |/ / __/ _ \
| | | | (_) | || (_| |   <| || (_) |
|_| |_|\___/ \__\__,_|_|\_\\__\___/

===============================================
Please select a game mode:
Singleplayer [1]
Multiplayer  [2]
mode: 1

Please select an option:
New Game  [1]
Load Game [2]
option: 2

... Loading File ...
Enter '!' whenever you want to quit the game.

A       B
X X 2   X 1 2
X 4 5   3 4 X   
6 7 X   6 7 X
Player 1: B1


A       B
X X 2   X X 2
X 4 5   3 4 X
6 7 X   6 7 X
Player 2(AI): B2

A
X X 2
X 4 5
6 7 X
Player 1: A7


A
X X 2
X 4 5
6 X X   
Player 2(AI): A5

A
X X 2
X 4 X
6 X X
Player 1: A6


Player 2 wins!
  _____                 ____
 / ___/__ ___ _  ___   / __ \_  _____ ____
/ (_ / _ `/  ' \/ -_) / /_/ / |/ / -_) __/
\___/\_,_/_/_/_/\__/  \____/|___/\__/_/
</pre>
<br />
