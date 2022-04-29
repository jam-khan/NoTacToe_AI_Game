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


map<char, vector<char>> tables;
map<string, vector<vector<char>>> monoid_values;


struct coordinates {
    char grid_name;
    int position;
};


coordinates random_bot()
{
    srand(time(0));
    map<char, vector<char>>::iterator itr;
    char board;
    int pos;
    int map_size=tables.size();
    int rand_board;
    int rand_pos;
    int board_count=-1;

    //randomize board

    rand_board=rand()%map_size;
    rand_pos=rand()%9;

    for(itr=tables.begin();itr!=tables.end();itr++)
    {
        board_count++;
        if(board_count==rand_board)
        {

            board=itr->first;

            vector<char> vect_temp = itr->second;
            vector<char>::iterator itr2;

            int board_count=0;
            for(itr2=vect_temp.begin();itr2!=vect_temp.end();itr2++)
            {
                if (board_count==rand_pos)
                {
                    if (*itr2=='x')
                    {
                        rand_pos=rand()%9;
                    }
                    else
                    {
                        coordinates coordinate;
                        coordinate.grid_name = board;
                        coordinate.position = rand_pos;
                        return coordinate;
                    }

                }
                board_count++;

            }
        }
    }

}



void save_game_state(int counter)
{
    ofstream game_file;
    game_file.open("GameState.txt");

    game_file<<counter-1;

    map<char, vector<char>>::iterator itr;

    for(itr=tables.begin();itr!=tables.end();itr++)
    {
        game_file<< itr->first<<endl;
        vector<char> vect_temp = itr->second;
        vector<char>::iterator itr2;

        for(itr2=vect_temp.begin();itr2!=vect_temp.end();itr2++)
        {
            game_file<< *itr2<<endl;
        }
    }
    game_file.close();
    return;
}


void load_game_state(int &counter)
{
    ifstream game_file;
    game_file.open("GameState.txt");

    map<char, vector<char>>::iterator itr;

    vector<char> vect_temp;
    char input;
    char board;

    game_file>>counter;

    while(game_file>>board)
    {
        for(int i=0;i<9;i++)
        {
            game_file>>input;

            vect_temp.push_back(input);

        }
        tables[board]=vect_temp;
        vect_temp.clear();
    }



    if(tables.empty())
    {
        vector<char> vect = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

            int difficulty;
            cout << "High: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
            cin >> difficulty;
            // validate difficulty
            cout << endl;

            for (int i = 0; i < 2 + difficulty; i++) {
                tables[(char)('A' + i)] = vect;
            }
    }

    game_file.close();
    return;
}


bool get_save(int counter)
{
    string input;
    cout<<"Would you like to exit the game?\n [yes/no]:";
    cin>>input;
    while(true)
    {
        if(input=="yes")
        {

            cout<<"Would you like to save the game status?\n [yes/no]:";
            cin>>input;

            while(true)
            {
                if(input=="yes")
                {
                    save_game_state(counter);
                    exit(0);
                }

                else if(input=="no")
                    exit(0);

                cout<<"Would you like to save the game status?\n [yes/no]:";
                cin>>input;

            }
        }
        else if(input=="no")
            return false;

        cout<<"Would you like to save and exit the game status?\n [yes/no]:";
        cin>>input;

    }

}


bool validate_Input(string input){

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

coordinates take_player_input(int player_num) {

    string input;
    cout << "Player " << player_num << ": ";
    cin >> input;

    while(input=="!")
    {
        get_save(player_num);
        cout << "Player " << player_num << ": ";
        cin >> input;
    }

    while (!validate_Input(input)){
        cout << "Wrong Input Enter Again" << endl;
        cout << "Player " << player_num << ": ";
        cin >> input;
        while(input=="!")
        {
            get_save(player_num);
            cout << "Player " << player_num << ": ";
            cin >> input;
        }
    }

    coordinates coordinate;
    coordinate.grid_name = input.at(0);
    coordinate.position = int(input.at(1)) - 48;

    return coordinate;
}



void print_grid(){
    map<char, vector<char>>::iterator itr;

    for(itr = tables.begin(); itr != tables.end(); itr++)
        cout << left << setw(8) << (*itr).first;


    cout << endl;

    for(int i = 0; i < 3; i++) {
        for (itr = tables.begin(); itr != tables.end(); itr++){
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

void initialize_ai_bot() {

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



string get_q_value(vector<char> current_table) {

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


string get_monoid(map<char, vector<char>> test_tables) {

    string monoid = "";

    map<char, vector<char>>::iterator itr;

    for(itr = test_tables.begin(); itr != test_tables.end(); itr++)
        monoid += get_q_value((*itr).second);


    return simplify_monoid(monoid);
}

bool check_ai_move(map<char, vector<char>> test_tables) {

    string monoid = get_monoid(test_tables);

    if (monoid == "a"
            || monoid == "bc"
            || monoid == "cb"
            || monoid == "bb"
            || monoid == "cc")
            return true;

    return false;

}


coordinates get_ai_move() {

    coordinates move;

    map<char, vector<char>>::iterator itr;

    for (itr = tables.begin(); itr != tables.end(); itr++) {
        map<char, vector<char>> test_tables = tables;
        for (int i = 0; i < 9; i++) {

            if (test_tables[(*itr).first][i] != 'X'){
                test_tables[(*itr).first][i] = 'X';
            }else {
                continue;
            }

            if (check_ai_move(test_tables)) {
                move.grid_name = (*itr).first;
                move.position = i;
                return move;
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
                return move;
            }
        }
    }

}


int main() {


    initialize_ai_bot();

    string input;
    int player_counter = 0;

    cout<<"Please select an option:\nNew Game [1]\nLoad Game[2]\n";
    cin>>input;
    while(true)
    {
        if(input=="1")
        {
            vector<char> vect = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

            int difficulty;
            cout << "High: Enter 3\tMedium: Enter 2\tEasy: Enter 1\nDifficulty: ";
            cin >> difficulty;
            // validate difficulty
            cout << endl;

            for (int i = 0; i < 2 + difficulty; i++) {
                tables[(char)('A' + i)] = vect;
            }
                break;
        }
        else if (input=="2")
        {
            load_game_state(player_counter);
            break;
        }
        cout << "Please select an option:\n\tNew Game [1]\n\tLoad Game[2]\n";
        cin >> input;
    }


    print_grid();

    coordinates input1 = take_player_input(player_counter % 2 + 1);


    while(true) {
        player_counter++;
        refresh_grid(input1);

        get_ai_move();
        cout << endl;

        cross_check();

        if (tables.empty())
            break;

        print_grid();

        if (player_counter % 2 + 1 == 2) {

            input1 = get_ai_move();


            cout << "Player 2 (AI): " << input1.grid_name << input1.position << endl;

        }else {
            input1 = take_player_input(player_counter % 2 + 1);
        }

    }
    // was checking refresh grid

    cout << "Player " << (player_counter % 2 + 1) << " wins!";

}


// input: done
// display: done
// validation: done
// refreshGrid with cross: done
// remove grid once cross found: done
// AI bot done


// Random bot waiting to be added to main function
