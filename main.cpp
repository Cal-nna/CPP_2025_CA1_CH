#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

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

    cout << "\n--------------------------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(6) << "Dex"
         << setw(10) << "Height(m)"
         << setw(15) << "Type"
         << setw(5) << "HP"
         << setw(5) << "Atk"
         << setw(5) << "Def"
         << setw(5) << "SpA"
         << setw(5) << "SpD"
         << setw(5) << "Spe"
         << endl;
    cout << "--------------------------------------------------------------------------------------------------\n";

    for (const auto &pokemon : pokemonList) {
        cout << left << setw(15) << pokemon.name
             << setw(6) << pokemon.dex
             << fixed << setprecision(2) << setw(10) << pokemon.height
             << setw(15) << pokemon.type
             << setw(5) << pokemon.hp
             << setw(5) << pokemon.attack
             << setw(5) << pokemon.defense
             << setw(5) << pokemon.spAttack
             << setw(5) << pokemon.spDefense
             << setw(5) << pokemon.speed
             << endl;
    }

    cout << "--------------------------------------------------------------------------------------------------\n";
}

//Q2
string toLowerCase(const string &str) { //converts name to lower case
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int searchPokemonByName(const vector<Pokemon> &pokemonList, const string &name) {
    string searchNameLower = toLowerCase(name);

    for (size_t i = 0; i < pokemonList.size(); i++) {
        if (toLowerCase(pokemonList[i].name) == searchNameLower) {
            return i;
        }
    }
    return -1;
}

void displayPokemonDetails(const Pokemon &pokemon) {
    cout << "\n--- Pokemon Details ---\n";
    cout << "Name: " << pokemon.name << "\n";
    cout << "Dex No: " << pokemon.dex << "\n";
    cout << "Height: " << pokemon.height << "m\n";
    cout << "Type: " << pokemon.type << "\n";
    cout << "HP: " << pokemon.hp << "\n";
    cout << "Attack: " << pokemon.attack << "\n";
    cout << "Defense: " << pokemon.defense << "\n";
    cout << "Special Attack: " << pokemon.spAttack << "\n";
    cout << "Special Defense: " << pokemon.spDefense << "\n";
    cout << "Speed: " << pokemon.speed << "\n";
    cout << "------------------------\n";
}

//Q3
unordered_map<string, int> countPokemonByType(const vector<Pokemon> &pokemonList) {
    unordered_map<string, int> typeCounts;

    for (const auto &pokemon : pokemonList) {
        typeCounts[pokemon.type]++;
    }

    return typeCounts;
}

void displayTypeCounts(const unordered_map<string, int> &typeCounts) {
    if (typeCounts.empty()) {
        cout << "No data available to count.\n";
        return;
    }

    cout << "\n--- Pokemon Type Counts ---\n";
    for (const auto &entry : typeCounts) {
        cout << entry.first << ": " << entry.second << endl;
    }
    cout << "---------------------------\n";
}

//Q4
void displayPokemonByDex(const vector<Pokemon> &pokemonList, int dexNumber) {
    bool found = false;

    cout << "\n------------------------ Pokemon with Dex #: " << dexNumber << " ------------------------\n";
    cout << "Name           Dex   Height   Type           HP  Atk  Def  SpA  SpD  Spe" << endl;
    cout << "--------------------------------------------------------------------------------\n";

    for (const auto &pokemon : pokemonList) {
        if (pokemon.dex == dexNumber) {
            found = true;
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
    }

    if (!found) {
        cout << "No Pokemon found with Dex number '" << dexNumber << "'.\n";
    }

    cout << "--------------------------------------------------------------------------------\n";
}


//Q5 is quite complicated due to my odd obligation to the base stats,
// this looks daunting because of the user input accountability,
//not only for case but proper wording like Special Attack
int findStatExtremes(const vector<Pokemon> &pokemonList) {
    if (pokemonList.empty()) {
        cout << "No Pokemon data available.\n";
        return -1;
    }

    cout << "Choose a base stat to analyze (HP, Attack, Defense, SpAttack, SpDefense, Speed): ";
    string statChoice;
    getline(cin, statChoice);

    int (Pokemon::*statPtr) = nullptr;

    if (statChoice == "HP" || statChoice == "hp") statPtr = &Pokemon::hp;
    else if (statChoice == "Attack" || statChoice == "attack") statPtr = &Pokemon::attack;
    else if (statChoice == "Defense" || statChoice == "defense") statPtr = &Pokemon::defense;
    else if (statChoice == "SpAttack" || statChoice == "spattack" || statChoice == "Special Attack") statPtr = &Pokemon::spAttack;
    else if (statChoice == "SpDefense" || statChoice == "spdefense" || statChoice == "Special Defense") statPtr = &Pokemon::spDefense;
    else if (statChoice == "Speed" || statChoice == "speed") statPtr = &Pokemon::speed;
    else {
        cout << "Invalid stat choice.\n";
        return -1;
    }

    const Pokemon *highest = &pokemonList[0];
    const Pokemon *lowest = &pokemonList[0];
    int total = 0;

    for (const auto &pokemon : pokemonList) {
        int statValue = pokemon.*statPtr;
        total += statValue;
        if (statValue > highest->*statPtr) highest = &pokemon;
        if (statValue < lowest->*statPtr) lowest = &pokemon;
    }

    int average = total / pokemonList.size();

    cout << "\n--- " << statChoice << " Analysis ---\n";
    cout << "Highest: " << highest->name << " (" << highest->*statPtr << " " << statChoice << ")\n";
    cout << "Lowest: " << lowest->name << " (" << lowest->*statPtr << " " << statChoice << ")\n";
    cout << "Average " << statChoice << ": " << average << "\n";
    cout << "---------------------------------\n";

    return average;
}
//Q6 connects to the display all pokemon function
vector<Pokemon> searchPokemonByType(const vector<Pokemon> &pokemonList, const string &partialType) {
    vector<Pokemon> matchingPokemon;
    string searchTypeLower = toLowerCase(partialType);

    for (auto it = pokemonList.begin(); it != pokemonList.end(); ++it) {
        if (toLowerCase(it->type).find(searchTypeLower) != string::npos) {
            matchingPokemon.push_back(*it);
        }
    }

    return matchingPokemon;
}
//Q7
void displayPokemonByHeightDescending(vector<Pokemon> &pokemonList) {
    if (pokemonList.empty()) {
        cout << "No Pokemon data available.\n";
        return;
    }

    sort(pokemonList.begin(), pokemonList.end(), [](const Pokemon &a, const Pokemon &b) {
        return a.height > b.height;
    });

    cout << "\n------------------------ Pokemon Sorted by Height (Descending) ------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(6) << "Dex"
         << setw(10) << "Height(m)"
         << setw(15) << "Type"
         << setw(5) << "HP"
         << setw(5) << "Atk"
         << setw(5) << "Def"
         << setw(5) << "SpA"
         << setw(5) << "SpD"
         << setw(5) << "Spe"
         << endl;
    cout << "--------------------------------------------------------------------------------------\n";

    for (const auto &pokemon : pokemonList) {
        cout << left << setw(15) << pokemon.name
             << setw(6) << pokemon.dex
             << fixed << setprecision(2) << setw(10) << pokemon.height
             << setw(15) << pokemon.type
             << setw(5) << pokemon.hp
             << setw(5) << pokemon.attack
             << setw(5) << pokemon.defense
             << setw(5) << pokemon.spAttack
             << setw(5) << pokemon.spDefense
             << setw(5) << pokemon.speed
             << endl;
    }

    cout << "--------------------------------------------------------------------------------------\n";
}



int main() {
    vector<Pokemon> pokemonList;
    readCSV("pokemon_data.csv", pokemonList);

    int choice;
    do {
        cout << "\n=== Pokemon Database Menu ===\n";
        cout << "1. Display all Pokemon\n";
        cout << "2. Search Pokemon by Name\n";
        cout << "3. Count Pokemon by Type\n";
        cout << "4. List Pokemon by Dex Number\n";
        cout << "5. Find Highest, Lowset and Average Pokemon Stat\n";
        cout << "6. Find Pokemon by Type\n";
        cout << "7. Display Pokemon by assorted Height\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

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
            case 3: {
                unordered_map<string, int> typeCounts = countPokemonByType(pokemonList);
                displayTypeCounts(typeCounts);
                break;
            }
            case 4: {
                int searchDex;
                cout << "Enter Dex number: ";
                cin >> searchDex;

                displayPokemonByDex(pokemonList, searchDex);
                break;
            }
            case 5: {findStatExtremes(pokemonList);
                break;}
            case 6: {
                string searchType;
                cout << "Enter part of the type to search for: ";
                getline(cin, searchType);

                vector<Pokemon> results = searchPokemonByType(pokemonList, searchType);
                displayAllPokemon(results);
                break;
            }
            case 7: {
                displayPokemonByHeightDescending(pokemonList);
                break;
            }
            case 8:
                cout << "Exiting program. Goodbye!\n";
            break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}


