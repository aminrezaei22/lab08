#include "roster_io.h"

#include <fstream>
#include <sstream>

namespace {

bool read_whole_number(const std::string& text, int& value) {
    std::istringstream in(text);
    if (!(in >> value)) {
        return false;
    }
    in >> std::ws;
    return in.eof();
}

}  // namespace

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
    std::vector<Mech> loaded;
    int skipped = 0;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream fields(line);
        std::string name;
        std::string hp_text;
        std::string attack_text;
        std::string armor_text;
        int hp = 0;
        int attack = 0;
        int armor = 0;

        bool valid = std::getline(fields, name, ',') &&
                     std::getline(fields, hp_text, ',') &&
                     std::getline(fields, attack_text, ',') &&
                     std::getline(fields, armor_text, ',') &&
                     fields.eof() &&
                     !name.empty() &&
                     read_whole_number(hp_text, hp) &&
                     read_whole_number(attack_text, attack) &&
                     read_whole_number(armor_text, armor) &&
                     hp >= 1 && attack >= 0 && armor >= 0;

        if (valid) {
            loaded.push_back(Mech(name, hp, attack, armor));
        } else {
            ++skipped;
        }
    }
    roster = loaded;
    skipped_lines = skipped;
    return true;
}

bool append_line(const std::string& path, const std::string& text) {
    std::ofstream out(path, std::ios::app);
    if (!out) {
        return false;
    }
    out << text << "\n";
    return static_cast<bool>(out);
}
