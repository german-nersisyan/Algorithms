#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <filesystem>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

struct Rule {
    vector<string> deps;
    vector<string> commands;
};

map<string, Rule> rules;
set<string> visiting;
set<string> built;

void parseMakefile(const string& filename) {
    ifstream file(filename);
    string line, currentTarget;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find(':') != string::npos) {
            stringstream ss(line);
            string target;
            getline(ss, target, ':');

            currentTarget = target;
            rules[currentTarget] = Rule();

            string dep;
            while (ss >> dep) {
                rules[currentTarget].deps.push_back(dep);
            }
        }
        else if (!currentTarget.empty() && line[0] == '\t') {
            rules[currentTarget].commands.push_back(line.substr(1));
        }
    }
}

bool needsRebuild(const string& target) {
    if (!fs::exists(target)) return true;

    auto targetTime = fs::last_write_time(target);

    for (auto& dep : rules[target].deps) {
        if (!fs::exists(dep)) continue;

        if (fs::last_write_time(dep) > targetTime) {
            return true;
        }
    }
    return false;
}

void build(const string& target) {
    if (built.count(target)) return;

    if (visiting.count(target)) {
        cerr << "Error: cyclic dependency involving " << target << endl;
        exit(1);
    }

    visiting.insert(target);

    for (auto& dep : rules[target].deps) {
        if (rules.count(dep)) {
            build(dep);
        }
    }

    if (needsRebuild(target)) {
        cout << "[BUILD] " << target << endl;

        for (auto& cmd : rules[target].commands) {
            cout << "  -> " << cmd << endl;
            int res = system(cmd.c_str());
            if (res != 0) {
                cerr << "Command failed!" << endl;
                exit(1);
            }
        }
    } else {
        cout << "[SKIP] " << target << " is up to date\n";
    }

    visiting.erase(target);
    built.insert(target);
}

int main(int argc, char* argv[]) {
    parseMakefile("Makefile");

    string target = "all";
    if (argc > 1) target = argv[1];

    if (!rules.count(target)) {
        cerr << "No rule for target: " << target << endl;
        return 1;
    }

    build(target);
    return 0;
}

/*
all: main.o util.o
	g++ main.o util.o -o app

main.o: main.cpp
	g++ -c main.cpp

util.o: util.cpp
	g++ -c util.cpp
*/