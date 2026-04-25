#pragma once
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;

struct Container {
    string id;
    int weight;
};

struct PortStack {
    stack<Container> containers;
    int curWeight;
};

struct ShipSection {
    int totalWeight;
    vector<string> containIds;
};

struct Port {
    int maxStackWeight;
    vector<PortStack> stacks;
    vector<ShipSection> sections;
    vector<Container> arrival;
};

void initPort(Port& port, int maxStackWeight, int numSec);
void arrive(Port& port, const string& id, int weight);
void load(Port& port);
void processComand(Port& port, const string& comandLine);
void printSections(const Port& port);
void putContainerIntoSection(Port& port, const Container& container, int targetSecNum);
int findTargetSecNum(const Port& port);
vector<Container> loadingOrder(const Port& port);