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


// struct coordinates {
//     char grid_name;
//     int position;
// };


void initialize_ai_bot(map<string, vector<vector<char>>> &monoid_values) {

    ifstream fin;
    fin.open("q_values.txt");

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
                monoid_values[q_value][i].push_back(temp_chr);
            }
        }
    }

    fin.close();
}



vector<char> get_sorted(vector<char> grid) {

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

    vector<char> rotated_grid;

    rotated_grid = {grid[6], grid[3], grid[0], grid[7], grid[4], grid[1], grid[8], grid[5], grid[2]};
    rotated_grid = get_sorted(rotated_grid);


    if (degrees == 90)
        return rotated_grid;
    else
        return get_rotation(rotated_grid, degrees - 90);

}

vector<char> get_reflection(vector<char> grid, char axis) {


    vector<char> reflected_grid;

    if (axis == 'y') {
        reflected_grid = {grid[2], grid[1], grid[0], grid[5], grid[4], grid[3], grid[8], grid[7], grid[6]};
    } else if (axis == 'x') {
        reflected_grid = {grid[6], grid[7], grid[8], grid[3], grid[4], grid[5], grid[0], grid[1], grid[2]};
    }

    return get_sorted(reflected_grid);

}



string get_q_value(vector<char> current_table, map<string, vector<vector<char>>> monoid_values) {

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

    return "";

}


string simplify_monoid(string monoid) {


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

        // simplified_monoid = string('a', count_a) + string('b', count_b) + string('c', count_c) + string('d', count_d);
        return simplify_monoid(simplified_monoid);

    }

}


string get_monoid(map<char, vector<char>> test_tables,  map<string, vector<vector<char>>> monoid_values) {

    string monoid = "";

    map<char, vector<char>>::iterator itr;

    for(itr = test_tables.begin(); itr != test_tables.end(); itr++)
        monoid += get_q_value((*itr).second, monoid_values);


    return simplify_monoid(monoid);
}

bool check_ai_move(map<char, vector<char>> test_tables, map<string, vector<vector<char>>> monoid_values) {

    string monoid = get_monoid(test_tables, monoid_values);

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

    for (itr = tables.begin(); itr != tables.end(); itr++) {
        for (int i = 0; i < 9; i++) {
            if (tables[(*itr).first][i] != 'X'){
                move.grid_name = (*itr).first;
                move.position = i;
                // return move;
                return;
            }
        }
    }
    // move = get_random_move();
    return;
    // return get_random_move();

}