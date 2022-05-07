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
#include "Grid_Functions.h"

using namespace std;


map<char, vector<char>> tables;
map<string, vector<vector<char>>> monoid_values;



int main() {

    welcome_text();

    initialize_ai_bot(monoid_values);

    int difficulty;
    string diff;
    string input;
    string mode;

    int bot_pos = 2;
    int player_counter = 0;

    get_values(difficulty, diff, input, mode, bot_pos, player_counter, tables);

    cout << "Enter '!' whenever you want to quit the game.\n" << endl;

    print_grid(tables);

    coordinates input1;

    if (player_counter % 2 + 1 == bot_pos && mode == "1") {

        input1 = get_bot_move(difficulty, tables, monoid_values);
        cout << "Player " << bot_pos << "(AI): " << input1.grid_name << input1.position << endl;
    }
    else 
        input1 = take_player_input(player_counter % 2 + 1, mode, difficulty, bot_pos, tables);


    while (true) {
       
        player_counter++;
        refresh_grid(input1, tables);

        
        cout << endl;

        cross_check(tables);

        if (tables.empty())
            break;

        print_grid(tables);

        if (player_counter % 2 + 1 == bot_pos && mode == "1") {

            input1 =  get_bot_move(difficulty, tables, monoid_values);

            cout << "Player " << bot_pos << "(AI): " << input1.grid_name << input1.position << endl;

        }
        else {
            input1 = take_player_input(player_counter % 2 + 1, mode, difficulty, bot_pos, tables);
        }

    }

    cout << "Player " << (player_counter % 2 + 1) << " wins!\n";

    end_text();

}
