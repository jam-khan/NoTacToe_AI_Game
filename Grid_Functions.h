#pragma once
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

#include "Struct_Guard.h"


using namespace std;



#ifndef GRID_FUNCTIONS_H
#define GRID_FUNCTIONS_H



int get_player_pos(int& bot);
bool get_save(int counter, string mode, int difficulty, int bot_pos, map<char, vector<char>> &tables);
bool validate_Input(string input, map<char, vector<char>> &tables);
void print_grid(map<char, vector<char>> &tables);
void refresh_grid(coordinates coordinate, map<char, vector<char>> &tables);
void cross_check(map<char, vector<char>> &tables);
coordinates take_player_input(int player_num, string mode, int difficulty, int bot_pos, map<char, vector<char>> &tables);
coordinates get_bot_move(int diff, map<char, vector<char>> &tables, map<string, vector<vector<char>>> &monoid_values);
void get_values(int &difficulty, string &diff, string &input, string &mode, int &bot_pos, int &player_counter, map<char, vector<char>> &tables);
void welcome_text();
void end_text();


#endif