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

using namespace std;

#include "Struct_Guard.h" // we have used this Struct_Guard.h to store definition of struct coordinates used across the files.
// this has allowed us to prevent compilation errors due to multiple redefinition of struct coordinates by including definition in each header file

#ifndef AI_BOT_H
#define AI_BOT_H


void initialize_ai_bot(map<string, vector<vector<char>>> &monoid_values);
vector<char> get_sorted(vector<char> grid);
vector<char> get_rotation(vector<char> grid, int degrees);
vector<char> get_reflection(vector<char> grid, char axis);
string get_q_value(vector<char> current_table, map<string, vector<vector<char>>> monoid_values);
string simplify_monoid(string monoid);
string get_monoid(map<char, vector<char>> test_tables,  map<string, vector<vector<char>>> monoid_values);
bool check_ai_move(map<char, vector<char>> test_tables, map<string, vector<vector<char>>> monoid_values);
void get_ai_move(coordinates &move, map<char, vector<char>> tables, map<string, vector<vector<char>>> monoid_values);

// above are function of AI bot written by Jam Kabeer

coordinates get_random_move(map<char, vector<char>> tables);

#endif
