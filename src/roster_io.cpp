#include "roster_io.h"

#include <fstream>
#include <sstream>

bool save_roster(const std::vector<Mech>& roster, const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    for (const Mech& mech : roster) {
        out << mech.name() << "," << mech.hp() << "," << mech.attack() << ","
            << mech.armor() << "\n";
    }
    return true;
}

bool load_roster(const std::string& path, std::vector<Mech>& roster, int& skipped_lines) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    roster.clear();
    skipped_lines = 0;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream fields(line);
        std::string name;
        std::string hp_text;
        std::string attack_text;
        std::string armor_text;
        std::getline(fields, name, ',');
        std::getline(fields, hp_text, ',');
        std::getline(fields, attack_text, ',');
        std::getline(fields, armor_text, ',');

        int hp = 0;
        int attack = 0;
        int armor = 0;
        std::istringstream hp_in(hp_text);
        std::istringstream attack_in(attack_text);
        std::istringstream armor_in(armor_text);
        if (hp_in >> hp && attack_in >> attack && armor_in >> armor) {
            roster.push_back(Mech(name, hp, attack, armor));
        } else {
            ++skipped_lines;
        }
    }
    return true;
}

// TODO (Checkpoint 4): implement append_line.
bool append_line([[maybe_unused]] const std::string& path,
                 [[maybe_unused]] const std::string& text) {
    return false;
}
