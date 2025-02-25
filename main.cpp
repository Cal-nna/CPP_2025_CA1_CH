#include <iostream>
#include <fstream>
#include <sstream>
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

void parse(string line, Pokemon &pokemon) {
    stringstream ss(line);
    string temp;

    getline(ss, pokemon.name, ',');

    getline(ss, temp, ',');
    pokemon.dex = stoi(temp);

    getline(ss, temp, ',');
    pokemon.height = stof(temp);

    getline(ss, pokemon.type, ',');

    getline(ss, temp, ',');
    pokemon.hp = stoi(temp);

    getline(ss, temp, ',');
    pokemon.attack = stoi(temp);

    getline(ss, temp, ',');
    pokemon.defense = stoi(temp);

    getline(ss, temp, ',');
    pokemon.spAttack = stoi(temp);

    getline(ss, temp, ',');
    pokemon.spDefense = stoi(temp);

    getline(ss, temp, ',');
    pokemon.speed = stoi(temp);
}

void readCSV(const string &filename) {
    ifstream fin(filename);

    if (!fin) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        // if (line.empty()) continue;

        Pokemon pokemon;
        try {
            parse(line, pokemon);
            cout << pokemon.name << ", " << pokemon.dex << ", " << pokemon.height << ", "
                 << pokemon.type << ", " << pokemon.hp << ", " << pokemon.attack << ", "
                 << pokemon.defense << ", " << pokemon.spAttack << ", " << pokemon.spDefense
                 << ", " << pokemon.speed << endl;
        } catch (const invalid_argument &e) {
            cerr << "Error parsing line: " << line << " | Exception: " << e.what() << endl;
        }
    }

    fin.close();
}

int main() {
    readCSV("pokemon_data.csv");  // Change this to the actual CSV file name
    return 0;
}
