#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;


// struct q_value {
//     string value;
//     int []
// };

map<char, vector<char>> tables;



struct coordinates {
    char grid_name;
    int position;
};


bool validate_Input(string input){

    if (input.size() != 2) {
        return false;
    }
        

    coordinates coordinate;
    coordinate.grid_name = input.at(0);
    coordinate.position = int(input.at(1)) - 48;

    map<char, vector<char>>::iterator itr;

    bool correct_grid_name = false;

    for (itr = tables.begin(); itr != tables.end(); itr++) {

        if ((*itr).first == coordinate.grid_name) {
            if ((*itr).second[coordinate.position] == 'X') {
                return false;
            }
            correct_grid_name = true;
        }
    }

    if (!correct_grid_name){
        return false;
    }

    if (coordinate.position < 0 || coordinate.position > 8) {
        return false;
    }


    return true;

}

coordinates take_player_input(int player_num) {

    string input;
    cout << "Player " << player_num << ": ";
    cin >> input;

    while (!validate_Input(input)){
        cout << "Wrong Input Enter Again" << endl;
        cout << "Player " << player_num << ": ";
        cin >> input;
    }

    coordinates coordinate;
    coordinate.grid_name = input.at(0);
    coordinate.position = int(input.at(1)) - 48;

    return coordinate;
}



void print_grid(map<char, vector<char>> grid){
    map<char, vector<char>>::iterator itr;

    for(itr = grid.begin(); itr != grid.end(); itr++){
        cout << left << setw(8) << (*itr).first;
    }

    cout << endl;

    for(int i = 0; i < 3; i++) {
        
        for (itr = grid.begin(); itr != grid.end(); itr++){
            vector<char> vect_temp = (*itr).second;
            for (int j = 0; j < 3; j++) {
                cout << vect_temp[i * 3 + j] << " ";
            }
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

    // int horizontal_Xs = 0;
    // int vertical_Xs = 0;
    // int diagonal1_Xs = 0;
    // int diagonal2_Xs = 0;

    // bool cross_found = false;

    for (itr = tables.begin(); itr != tables.end(); itr++) {

        for (int i = 0; i < 3; i++) {
            if ((*itr).second[3 * i] == 'X' && (*itr).second[3 * i + 1] == 'X' && (*itr).second[3 * i + 2] == 'X') {
                tables.erase((*itr).first);
                // cross_found = true;
                return;
            }

            if ((*itr).second[i] == 'X' && (*itr).second[3 + i] == 'X' && (*itr).second[6 + i] == 'X') {
                tables.erase((*itr).first);
                // cross_found = true;
                return;
            }

            if ((*itr).second[0] == 'X' && (*itr).second[4] == 'X' && (*itr).second[8] == 'X') {
                tables.erase((*itr).first);
                // cross_found = true;
                return;
            }

            if ((*itr).second[2] == 'X' && (*itr).second[4] == 'X' && (*itr).second[6] == 'X') {
                tables.erase((*itr).first);
                // cross_found = true;
                return;
            }

        }

    }

}


int main() {

    vector<char> vect = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

    // for (int i = 0; i < 10; i++) {

    // }

    int difficulty;
    cout << "High: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
    cin >> difficulty;
    // validate difficulty
    cout << endl;

    for (int i = 0; i < 2 + difficulty; i++) {
        tables[(char)('A' + i)] = vect;
    }

    // tables['A'] = vect;
    // tables['B'] = vect;
    // tables['C'] = vect;

    print_grid(tables);

    coordinates input1 = take_player_input(1);

    
    int player_counter = 0;

    while(true) {
        refresh_grid(input1);
        cross_check();

        if (tables.empty())
            break;

        print_grid(tables);
        input1 = take_player_input(player_counter % 2 + 1);
        player_counter++; 
    }
    // was checking refresh grid
    
    cout << "Player " << (player_counter % 2 + 1) << " wins!";

}


// input: done
// display: done
// validation: done
// refreshGrid with cross: done
// remove grid once cross found: done