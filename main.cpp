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

//Q1
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

//Q2
int searchPokemonByName(const vector<Pokemon> &pokemonList, const string &name) {
    for (size_t i = 0; i < pokemonList.size(); i++) {
        if (pokemonList[i].name == name) {
            return i;
        }
    }
    return -1;
;

void displayPokemonDetails(const Pokemon &pokemon) {
    cout << "\n--- Pokemon Details ---\n";
    cout << "Name: " << pokemon.name << "\n";
    cout << "Dex No: " << pokemon.dex << "\n";
    cout << "Height: " << pokemon.height << "\n";
    cout << "Type: " << pokemon.type << "\n";
    cout << "HP: " << pokemon.hp << "\n";
    cout << "Attack: " << pokemon.attack << "\n";
    cout << "Defense: " << pokemon.defense << "\n";
    cout << "Special Attack: " << pokemon.spAttack << "\n";
    cout << "Special Defense: " << pokemon.spDefense << "\n";
    cout << "Speed: " << pokemon.speed << "\n";
    cout << "------------------------\n";
}


int main() {
    vector<Pokemon> pokemonList;
    readCSV("pokemon_data.csv", pokemonList);

    int choice;
    do {
        cout << "\n=== Pokemon Database Menu ===\n";
        cout << "1. Display all Pokemon\n";
        cout << "2. Search Pokemon by Name\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline from previous input

        switch (choice) {
            case 1:
                displayAllPokemon(pokemonList);
            break;
            case 2: {
                string searchName;
                cout << "Enter Pokemon name: ";
                getline(cin, searchName);

                int index = searchPokemonByName(pokemonList, searchName);
                if (index != -1) {
                    displayPokemonDetails(pokemonList[index]);
                } else {
                    cout << "Pokemon '" << searchName << "' not found.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting program. Goodbye!\n";
            break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}


