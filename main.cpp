#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Pokemon {
    string name;
    int dex;
    float height;
    string type;
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
};

bool parse(const string &line, Pokemon &pokemon) { //parse is a bool to act as a check to see if the data is read correct
    stringstream ss(line);
    string temp;
    vector<string> values;

    while (getline(ss, temp, ',')) {
        values.push_back(temp);
    }

    if (values.size() != 10) {
        cerr << "Error: Incorrect number of fields in line: " << line << endl;
        return false;
    }

    try {
        pokemon.name = values[0];
        pokemon.dex = stoi(values[1]);
        pokemon.height = stof(values[2]);
        pokemon.type = values[3];
        pokemon.hp = stoi(values[4]);
        pokemon.attack = stoi(values[5]);
        pokemon.defense = stoi(values[6]);
        pokemon.spAttack = stoi(values[7]);
        pokemon.spDefense = stoi(values[8]);
        pokemon.speed = stoi(values[9]);
    } catch (const invalid_argument &e) {//error catchings, points out any error within the csv file
        cerr << "Error: Invalid number format in line: " << line << " | Exception: " << e.what() << endl;
        return false;
    }

    return true;
}

void readCSV(const string &filename, vector<Pokemon> &pokemonList) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        Pokemon pokemon;
        if (parse(line, pokemon)) {
            pokemonList.push_back(pokemon);
        }
    }

    fin.close();
}

void displayAllPokemon(const vector<Pokemon> &pokemonList) {
    if (pokemonList.empty()) {
        cout << "No Pokemon data available.\n";
        return;
    }

    cout << "\n---------------------------------------- Pokemon List ----------------------------------------\n";
    cout << "Name           Dex   Height   Type           HP  Atk  Def  SpA  SpD  Spe" << endl;
    cout << "--------------------------------------------------------------------------------------------\n";

    for (const auto &pokemon : pokemonList) {
        cout << pokemon.name;

        int namePadding = 15 - pokemon.name.length();
        cout << string(namePadding, ' ') << pokemon.dex << "    "
             << pokemon.height << "     "
             << pokemon.type;

        int typePadding = 15 - pokemon.type.length();
        cout << string(typePadding, ' ') << pokemon.hp << "   "
             << pokemon.attack << "   "
             << pokemon.defense << "   "
             << pokemon.spAttack << "   "
             << pokemon.spDefense << "   "
             << pokemon.speed << endl;
    }

    cout << "--------------------------------------------------------------------------------------------\n";
}

int main() {
    vector<Pokemon> pokemonList;
    readCSV("pokemon_data.csv", pokemonList);

    int choice;
    do {
        cout << "\n=== Pokemon Database Menu ===\n";
        cout << "1. Display all Pokemon\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllPokemon(pokemonList);
                break;
            case 2:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 2);

    return 0;
}
