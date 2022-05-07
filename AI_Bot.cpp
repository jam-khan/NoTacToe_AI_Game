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

using namespace std;

// this file holds the Artificially intelligent Bot and Random Bot

void initialize_ai_bot(map<string, vector<vector<char>>> &monoid_values) {

    // what it does?
    // this function loads the values into the map monoid_values. These values are a set of possible arrangements of the Notakto grids
    // monoid values will allow the Artificial Intelligent Bot to find the most efficient move

    // monoid from what I know is some mathematical word used for sets.
    // we have implemented this algorithm using following research paper
    // https://arxiv.org/pdf/1301.1672.pdf

    // What the inputs are?
    // input is simply the map monoid_values passed by reference so that changes are reflected in the main program as well

    ifstream fin;
    fin.open("q_values.txt"); // this file stores the monoid values 

    if (fin.fail()) {
        cout << "Error!"<<endl;
        exit(1);
    }

    string q_value;
    int value_count = 0;

    while(fin >> q_value){
        fin >> value_count;
        char temp_chr;

        for (int i = 0; i < value_count; i++) {
            monoid_values[q_value].push_back({});
            for (int j = 0; j < 9; j++) {
                fin >> temp_chr;
                monoid_values[q_value][i].push_back(temp_chr); // all the values are loaded to the monoid_values map
                // we have used a map since it will allow storage of values as a dictionary
                // each monoid values had a corresponding value such as 'c^2' or 'ad'
                // these values are then used by algorithm to make the best move
            }
        }
    }

    fin.close();
}



vector<char> get_sorted(vector<char> grid) {

    // this function will return the sorted vector grid
    // this is used to sort an possible arrangment of grid after going through reflection of rotation
    // this changes vector from e.g. {'8', '6', 'X', '7', '3', 'X', '1', '0', '4'} to {'0', '1', 'X', '3', '4', 'X', '6', '7', '8'}

    vector<char> sorted_grid;

    int counter = 0;


    for (int i = 0; i < 9; i++) {
        if (grid[i] == 'X'){
            sorted_grid.push_back('X');
        }else {
            sorted_grid.push_back(i + '0');
        }
    }

    return sorted_grid;

}

vector<char> get_rotation(vector<char> grid, int degrees) {

    // this function rotates the given grid arrangement inside grid by 90 degrees
    // and then, return the new rotated arrangement
    // this is for the purpose of comparison used by the algorithm to get the best possible move

    // this function also uses recursion if e.g. degrees parameter is 180, 270, or 360.

    vector<char> rotated_grid;

    rotated_grid = {grid[6], grid[3], grid[0], grid[7], grid[4], grid[1], grid[8], grid[5], grid[2]};


    rotated_grid = get_sorted(rotated_grid);


    if (degrees == 90)
        return rotated_grid;
    else
        return get_rotation(rotated_grid, degrees - 90); // here we can see how it uses recursion. it first rotate 90 degrees and then, calls again for further rotation

}

vector<char> get_reflection(vector<char> grid, char axis) {

    // this function is used to reflect the arrangment inside grid about x-axis or y-axis
    // return the new reflected arrangement

    vector<char> reflected_grid;

    if (axis == 'y') {
        reflected_grid = {grid[2], grid[1], grid[0], grid[5], grid[4], grid[3], grid[8], grid[7], grid[6]};
    } else if (axis == 'x') {
        reflected_grid = {grid[6], grid[7], grid[8], grid[3], grid[4], grid[5], grid[0], grid[1], grid[2]};
    }

    return get_sorted(reflected_grid);

}



string get_q_value(vector<char> current_table, map<string, vector<vector<char>>> monoid_values) {

    // this function return the special value associated with the grid arrangement
    // it runs through the map monoid values and compares the current grid arrangement with each arrangment in map monoid_values
    // once it has found the match then it returns the key associated with that vector inside vector in map
    // key can be 'a', 'ad', 'b' etc
    // this is in accordance to the research paper
    //https://arxiv.org/pdf/1301.1672.pdf

    map<string, vector<vector<char>>>::iterator itr;
    vector<char> temp_grid;

    for(itr = monoid_values.begin(); itr != monoid_values.end(); itr++) {
        // cout << (*itr).first << endl;
        for (int i = 0; i < monoid_values[(*itr).first].size(); i++){
            temp_grid = (*itr).second[i];
            if (current_table == temp_grid
                || current_table == get_reflection(temp_grid, 'x')
                || current_table == get_reflection(temp_grid, 'y')
                || current_table == get_rotation(temp_grid, 90)
                || current_table == get_rotation(temp_grid, 180)
                || current_table == get_rotation(temp_grid, 270)){

                    return (*itr).first;

            }
        }
    }

    return ""; // there are going to be grid arrangments which have no associated value
    // for those grids we simply return nothing or you can say empty string

}


string simplify_monoid(string monoid) {

    // this function takes in the monoid string which can look something like following "aaacccadad"
    // then, this string is simplified to something like "acc" and returned
    // this simplification happens on the basis of method given in the below paper
    // https://arxiv.org/pdf/1301.1672.pdf


    bool no_change = true;

    string simplified_monoid = "";

    int count_a = count(monoid.begin(), monoid.end(), 'a');
    int count_b = count(monoid.begin(), monoid.end(), 'b');
    int count_c = count(monoid.begin(), monoid.end(), 'c');
    int count_d = count(monoid.begin(), monoid.end(), 'd');

    if (count_a >= 2) {
        no_change = false;
        count_a = count_a - 2;
    }

    if (count_b >= 3) {
        no_change = false;
        count_b = count_b - 2;
    }

    if (count_b >= 2 && count_c >= 1) {
        no_change = false;
        count_b = count_b - 2;
    }

    if (count_c >= 3) {
        no_change = false;
        count_c = count_c - 1;
        count_a = count_a + 1;
    }

    if (count_b >= 2 && count_d >= 1) {
        no_change = false;
        count_b = count_b - 2;
    }

    if (count_c >= 1 && count_d >= 1) {
        no_change = false;
        count_c = count_c - 1;
        count_a = count_a + 1;
    }

    if (count_d >= 2) {
        no_change = false;
        count_d = count_d - 2;
        count_c = count_c + 2;
    }

    if(no_change) {
        return monoid;
    }else {

        for (int i = 0; i < count_a; i++)
            simplified_monoid = simplified_monoid + "a";

        for (int i = 0; i < count_b; i++)
            simplified_monoid = simplified_monoid + "b";

        for (int i = 0; i < count_c; i++)
            simplified_monoid = simplified_monoid + "c";

        for (int i = 0; i < count_d; i++)
            simplified_monoid = simplified_monoid + "d";

        
        return simplify_monoid(simplified_monoid); // it uses recursion to simplify the monoid as much as possible.
        // the recursion ends when there are no changes made to the monoid string passed to the function

    }

}


string get_monoid(map<char, vector<char>> test_tables,  map<string, vector<vector<char>>> monoid_values) {

    // since our game has multiple grids during the game and those all are dynamically arranged
    // therefore, the combined monoid value associated with the current grids changes after every move
    // this function is used to iterate through each grid and then, find the monoid value of each grid and 
    // combine those monoid values and concatenate them into a string called monoid 

    // this string is then returned

    string monoid = "";

    map<char, vector<char>>::iterator itr;

    for(itr = test_tables.begin(); itr != test_tables.end(); itr++)
        monoid += get_q_value((*itr).second, monoid_values);


    return simplify_monoid(monoid); // once all monoid values are combined into monoid then it is passed to function called simplify_monoid
                                    // then, output of simplify_monoid will be returned
}

bool check_ai_move(map<char, vector<char>> test_tables, map<string, vector<vector<char>>> monoid_values) {

    // this function takes in the grids of the game stored inside test_tables along with monoid values initialized
    // then, these values are passed to get_monoid function to get a simplified monoid value e.g. "bc"
    // this function will tell whether the recent move made is the best possible move or not
    // it will return true if move is best 
    // it will return false if move is not best

    string monoid = get_monoid(test_tables, monoid_values);

    // below is the comparison. if simplified monoid value is one of the following: "a", "bc", "cb", "bb", "cc" then the move is best

    if (monoid == "a"
            || monoid == "bc"
            || monoid == "cb"
            || monoid == "bb"
            || monoid == "cc")
            return true;

    return false;

}


void get_ai_move(coordinates &move, map<char, vector<char>> tables, map<string, vector<vector<char>>> monoid_values) {

    map<char, vector<char>>::iterator itr;

    // this function takes in the struct coordinates move variable to store the best move or any move
    
    // it iterates through all of grids and makes changes and uses new moves once it has found the best move it is stored inside move variable
    // function is returned (stopped)
    for (itr = tables.begin(); itr != tables.end(); itr++) {
        map<char, vector<char>> test_tables = tables;
        for (int i = 0; i < 9; i++) {

            if (test_tables[(*itr).first][i] != 'X'){
                test_tables[(*itr).first][i] = 'X';
            }else {
                continue;
            }

            if (check_ai_move(test_tables, monoid_values)) {
                move.grid_name = (*itr).first;
                move.position = i;
                // return move;
                return;
            }else {
                test_tables[(*itr).first][i] = i + '0';
            }
        }
    }

    // there can be scenario where there are no best possible moves remaining
    // for that situation below iteration allows for move to take place on the first empty cell so if A3 if first empty cell in grids
    // then, it is returned

    for (itr = tables.begin(); itr != tables.end(); itr++) {
        for (int i = 0; i < 9; i++) {
            if (tables[(*itr).first][i] != 'X'){
                move.grid_name = (*itr).first;
                move.position = i;
                return;
            }
        }
    }
    return;
}


// above code is written by Jam Kabeer Ali Khan (UID: 3035918749)

// below code is written by Yuanto


coordinates get_random_move(map<char, vector<char>> tables)
{
    srand(time(0));
    map<char, vector<char>>::iterator itr;
    char board;
    int pos;
    int map_size = tables.size();
    int rand_board;
    int rand_pos;

    //randomize board

    rand_board = rand() % map_size;
    rand_pos = rand() % 9;

    while (true)
    {
        int board_count = -1;
        for (itr = tables.begin();itr != tables.end();itr++)
        {
            board_count++;
            if (board_count == rand_board)
            {

                board = itr->first;

                vector<char> vect_temp = itr->second;
                vector<char>::iterator itr2;

                int board_pos = 0;
                for (itr2 = vect_temp.begin();itr2 != vect_temp.end();itr2++)
                {
                    if (board_pos == rand_pos)
                    {
                        if (*itr2 == 'X')
                        {
                            rand_pos = rand() % 9;
                        }
                        else
                        {
                            coordinates coordinate;
                            coordinate.grid_name = board;
                            coordinate.position = rand_pos;
                            return coordinate;
                        }

                    }
                    board_pos++;

                }
            }
        }
    }
}
