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

#include "AI_Bot.h"
#include "FileIO.h"

using namespace std;


map<char, vector<char>> tables;
map<string, vector<vector<char>>> monoid_values;


// struct coordinates {
//     char grid_name;
//     int position;
// };

//checks if player would like to go first or second
//input for function is pass by reference of bot being player 1 or 2
int get_player_pos(int& bot)
{
    string input;
    cout << "Would you like to go first?\n[yes/no]: ";
    cin >> input;
    while (true)
    {
        if (input == "yes")
        {
            bot = 2;
            return 0;
        }
        else if (input == "no")
        {
            bot = 1;
            return 1;
        }
        cout << "Would you like to go first?\n[yes/no]: ";
        cin >> input;
    }
}


// function to ask player if they want to quit the game and to save the game
// it also asks for the board , player counter, mode of the game, difficulty of the game, and if the bot is player 1 or 2
bool get_save(int counter, string mode, int difficulty, int bot_pos)
{
    string input;
    cout << "Would you like to exit the game?\n[yes/no]:";
    cin >> input;
    cout << endl;
    while (true)
    {
        if (input == "yes")
        {

            cout << "Would you like to save the game status?\n[yes/no]:";
            cin >> input;
            cout << endl;

            while (true)
            {
                if (input == "yes")
                {
                    save_game_state(counter, mode, difficulty, bot_pos,tables);
                    exit(0);
                }

                else if (input == "no")
                    exit(0);

                cout << "Would you like to save the game status?\n[yes/no]:";
                cin >> input;
                cout << endl;

            }
        }
        else if (input == "no")
            return false;

        cout << "Would you like to exit the game?\n[yes/no]:";
        cin >> input;
        cout << endl;

    }

}


bool validate_Input(string input) {

    if (input.size() != 2)
        return false;


    coordinates coordinate;
    coordinate.grid_name = input.at(0);
    coordinate.position = int(input.at(1)) - 48;

    map<char, vector<char>>::iterator itr;

    bool correct_grid_name = false;

    for (itr = tables.begin(); itr != tables.end(); itr++)
        if ((*itr).first == coordinate.grid_name) {
            if ((*itr).second[coordinate.position] == 'X')
                return false;

            correct_grid_name = true;
        }


    if (!correct_grid_name)
        return false;

    if (coordinate.position < 0 || coordinate.position > 8)
        return false;


    return true;
}

coordinates take_player_input(int player_num, string mode, int difficulty, int bot_pos) {

    string input;
    cout << "Player " << player_num << ": ";
    cin >> input;
    cout << endl;

    while (input == "!")
    {
        get_save(player_num, mode, difficulty, bot_pos);
        cout << "Player " << player_num << ": ";
        cin >> input;
        cout << endl;
    }

    while (!validate_Input(input)) {
        cout << "Wrong Input Enter Again" << endl;
        cout << "Player " << player_num << ": ";
        cin >> input;
        while (input == "!")
        {
            get_save(player_num, mode, difficulty, bot_pos);
            cout << "Player " << player_num << ": ";
            cin >> input;
            cout << endl;
        }
    }

    coordinates coordinate;
    coordinate.grid_name = input.at(0);
    coordinate.position = int(input.at(1)) - 48;

    return coordinate;
}



void print_grid() {
    map<char, vector<char>>::iterator itr;

    for (itr = tables.begin(); itr != tables.end(); itr++)
        cout << left << setw(8) << (*itr).first;


    cout << endl;

    for (int i = 0; i < 3; i++) {
        for (itr = tables.begin(); itr != tables.end(); itr++) {
            vector<char> vect_temp = (*itr).second;
            for (int j = 0; j < 3; j++)
                cout << vect_temp[i * 3 + j] << " ";

            cout << "  ";
        }
        cout << endl;
    }
}


void refresh_grid(coordinates coordinate) {

    tables[coordinate.grid_name][coordinate.position] = 'X';

}


void cross_check() {

    map<char, vector<char>>::iterator itr;

    for (itr = tables.begin(); itr != tables.end(); itr++)
        for (int i = 0; i < 3; i++) {
            if ((*itr).second[3 * i] == 'X' && (*itr).second[3 * i + 1] == 'X' && (*itr).second[3 * i + 2] == 'X') {
                tables.erase((*itr).first);
                return;
            }

            if ((*itr).second[i] == 'X' && (*itr).second[3 + i] == 'X' && (*itr).second[6 + i] == 'X') {
                tables.erase((*itr).first);
                return;
            }

            if ((*itr).second[0] == 'X' && (*itr).second[4] == 'X' && (*itr).second[8] == 'X') {
                tables.erase((*itr).first);
                return;
            }

            if ((*itr).second[2] == 'X' && (*itr).second[4] == 'X' && (*itr).second[6] == 'X') {
                tables.erase((*itr).first);
                return;
            }
        }

}



// gives the appropriate ai move according to the difficulty level
// it takes diffficulty level as an input
coordinates get_bot_move(int diff)
{
    coordinates move;
    if (diff == 1)
    {
        return get_random_move(tables);
    }
    else if (diff == 2)
    {
        if (rand() % 2)
            return get_random_move(tables);
        else {
            get_ai_move(move, tables, monoid_values);
            return move;
        }

    }
    else if (diff == 3)
    {
        get_ai_move(move, tables, monoid_values);
        return move;
    }

    return get_random_move(tables);

}

//print welcome text
void welcome_text()
{
    ifstream game_file;

    game_file.open("welcome.txt");

    string line;

    while (getline(game_file, line))
        cout << line << endl;

    game_file.close();

}

//print end text
void end_text()
{
    ifstream game_file;

    game_file.open("GameOver.txt");

    string line;

    while (getline(game_file, line))
        cout << line << endl;

    game_file.close();

}


int main() {

    welcome_text();


    initialize_ai_bot(monoid_values);

    int difficulty;
    string diff;
    string input;
    string mode;

    int bot_pos = 2;
    int player_counter = 0;

    cout << "Please select a game mode:\nSingleplayer [1]\nMultiplayer  [2]\nmode: ";
    cin >> mode;
    cout << endl;
    while (true)
    {
        if (mode == "1" || mode == "2")
            break;
        cout << "Please select a game mode:\nSingleplayer [1]\nMultiplayer  [2]\nmode: ";
        cin >> mode;
        cout << endl;
    }

    cout << "Please select an option:\nNew Game  [1]\nLoad Game [2]\noption: ";
    cin >> input;
    cout << endl;
    while (true)
    {
        if (input == "1")
        {
            vector<char> vect = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
            if (mode == "2")
                cout << "Please select number of boards:\n[3]: Enter 1\t[4]: Enter 2\t[5]: Enter 3\nNumber of boards: ";
            else
                cout << "Please select difficulty level\nHigh: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
            cin >> diff;
            cout << endl;

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
                cout << endl;
            }
            difficulty = stoi(diff);

            if (mode == "1")
                get_player_pos(bot_pos);

            cout << endl;

            for (int i = 0; i < 2 + difficulty; i++) {
                tables[(char)('A' + i)] = vect;
            }
            break;
        }
        else if (input == "2")
        {
            load_game_state(player_counter, mode, difficulty, bot_pos,tables);
            break;
        }
        cout << "Please select an option:\nNew Game  [1]\nLoad Game [2]\noption: ";
        cin >> input;
        cout << endl;
    }


    print_grid();

    coordinates input1;

    if (player_counter % 2 + 1 == bot_pos && mode == "1") {

        input1 = get_bot_move(difficulty);

        cout << "Player " << bot_pos << "(AI): " << input1.grid_name << input1.position << endl;

    }
    else {

        input1 = take_player_input(player_counter % 2 + 1, mode, difficulty, bot_pos);

    }


    while (true) {
        player_counter++;
        refresh_grid(input1);

        // get_ai_move();
        cout << endl;

        cross_check();

        if (tables.empty())
            break;

        print_grid();

        if (player_counter % 2 + 1 == bot_pos && mode == "1") {

            input1 = get_bot_move(difficulty);

            cout << "Player " << bot_pos << "(AI): " << input1.grid_name << input1.position << endl;

        }
        else {
            input1 = take_player_input(player_counter % 2 + 1, mode, difficulty, bot_pos);
        }

    }
    // was checking refresh grid

    cout << "Player " << (player_counter % 2 + 1) << " wins!\n";
    end_text();
}

// input: done
// display: done
// validation: done
// refreshGrid with cross: done
// remove grid once cross found: done
// AI bot done
