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

// TODO (Checkpoints 2 and 3): implement load_roster.
bool load_roster([[maybe_unused]] const std::string& path,
                 [[maybe_unused]] std::vector<Mech>& roster,
                 [[maybe_unused]] int& skipped_lines) {
    return false;
}

// TODO (Checkpoint 4): implement append_line.
bool append_line([[maybe_unused]] const std::string& path,
                 [[maybe_unused]] const std::string& text) {
    return false;
}
