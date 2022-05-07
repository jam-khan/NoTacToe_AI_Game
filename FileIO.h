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

#ifndef FileIO
#define FileIO

void save_game_state(int counter, string mode, int difficulty, int bot_pos, map<char, vector<char>> tables);
void load_game_state(int& counter, string mode, int& difficulty, int& bot_pos, map<char, vector<char>>& tables);

#endif
