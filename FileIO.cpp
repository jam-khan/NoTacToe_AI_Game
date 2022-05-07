#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <ctime>

#include "FileIO.h"

using namespace std;

// this function saves the game state in a text file
// this includes the board , player counter, mode of the game, difficulty of the game, and if the bot is player 1 or 2
// singleplayer and multiplayer is saved in different text files
void save_game_state(int counter, string mode, int difficulty, int bot_pos, map<char, vector<char>> tables)
{
    ofstream game_file;
    if (mode == "1")
        game_file.open("GameStateSingle.txt");
    else
        game_file.open("GameStateMulti.txt");

    game_file << counter - 1;
    game_file << endl;
    game_file << difficulty;
    game_file << endl;
    game_file << bot_pos;
    game_file << endl;

    map<char, vector<char>>::iterator itr;

    for (itr = tables.begin();itr != tables.end();itr++)
    {
        game_file << itr->first << endl;
        vector<char> vect_temp = itr->second;
        vector<char>::iterator itr2;

        for (itr2 = vect_temp.begin();itr2 != vect_temp.end();itr2++)
        {
            game_file << *itr2 << endl;
        }
    }
    game_file.close();
    return;
}

// this function loads the game state from a text file
// this includes the board , player counter, mode of the game, difficulty of the game, and if the bot is player 1 or 2
void load_game_state(int& counter, string mode, int& difficulty, int& bot_pos, map<char, vector<char>>& tables)
{
    ifstream game_file;

    cout << "... Loading File ...\n";

    if (mode == "1")
        game_file.open("GameStateSingle.txt");
    else
        game_file.open("GameStateMulti.txt");


    map<char, vector<char>>::iterator itr;

    vector<char> vect_temp;
    char input;
    char board;

    game_file >> counter;
    game_file >> difficulty;
    game_file >> bot_pos;

    while (game_file >> board)
    {
        for (int i = 0;i < 9;i++)
        {
            game_file >> input;

            vect_temp.push_back(input);

        }
        tables[board] = vect_temp;
        vect_temp.clear();
    }

    // checks if the grids are empty
    if (tables.empty())
    {
        cout << "No Previous Saves\n\n";
        cout << "Starting New Game ...\n\n";

        vector<char> vect = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };

        string diff;

        if (mode == "2")
            cout << "Please select number of boards:\n[3]: Enter 1\t[4]: Enter 2\t[5]: Enter 3\nNumber of boards: ";
        else
            cout << "Please select difficulty level\nHigh: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
        cin >> diff;
        cout << "\n";
        // validate difficulty

        while (true)
        {
            if (diff == "1" || diff == "2" || diff == "3")
                break;

            if (mode == "2")
                cout << "Please select number of boards:\n[3]: Enter 1\t[4]: Enter 2\t[5]: Enter 3\nNumber of boards: ";
            else
                cout << "Please select difficulty level\nHigh: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
            cin >> diff;
        }
        difficulty = stoi(diff);

        if (mode == "1")
        {
            string input;
            cout << "Would you like to go first?\n[yes/no]: ";
            cin >> input;
            while (true)
            {
                if (input == "yes")
                {
                    bot_pos = 2;
                    counter = 0;
                    break;
                }
                else if (input == "no")
                {
                    bot_pos = 1;
                    counter = 1;
                    break;
                }
                cout << "Would you like to go first?\n[yes/no]: ";
                cin >> input;
            }
        }

            
        cout << endl;

        for (int i = 0; i < 2 + difficulty; i++) {
            tables[(char)('A' + i)] = vect;
        }
    }
    game_file.close();
    return;
}
