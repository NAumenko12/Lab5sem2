#include "port.h"

string processCommand(Port& port, const string& commandFull) {
    string message{};
    istringstream input(commandFull);
    string command{};
    input >> command;
    if (command == "ARRIVE") {
        string id {};
        int weight {};
        input >> id >> weight;
        message = arrive(port, id, weight);
    } else if (command == "LOAD") {
        message = load(port);
    } else {
        message = "Неизвестная команда";
    }
    return message;
}

bool initPort(Port& port, int maxStackWeight, int numSections) {
    bool isReady = true;
    port.maxStackWeight = maxStackWeight;
    port.sections.clear();
    port.sections.resize(numSections);
    for (ShipSection& section : port.sections) {
        section.totalWeight = 0;
        section.containIds.clear();
    }
    return isReady;
}

string arrive(Port& port, const string& id, int weight) {
    string message{};
    PortStack* targetStack = nullptr;
    int stackNumber = 1;
    int targetStackNumber = 1;
    for (PortStack& portStack : port.stacks) {
        if (targetStack == nullptr && portStack.curWeight + weight <= port.maxStackWeight) {
            targetStack = &portStack;
            targetStackNumber = stackNumber;
        }
        ++stackNumber;
    }
    if (targetStack == nullptr) {
        PortStack newStack;
        newStack.curWeight = 0;
        port.stacks.push_back(newStack);
        targetStack = &port.stacks.back();
        targetStackNumber = port.stacks.size();
    }
    targetStack->containers.push({id, weight});
    targetStack->curWeight += weight;
    port.arrival.push_back({id, weight});
    message = "Контейнер " + id + " размещен в стек " + to_string(targetStackNumber);
    return message;
}


string load(Port& port) {
    string message{};
    for (const Container& container :loadingOrder(port)){
        int targetSecNum = findTargetSecNum(port);
        putContainerIntoSection(port, container, targetSecNum);
    }
    message = printSections(port);
    port.arrival.clear();
    port.stacks.clear();
    for (ShipSection& section : port.sections) {
        section.totalWeight = 0;
        section.containIds.clear();
    }
    return message;
}

vector<Container> loadingOrder(const Port& port){
    vector<Container> loadOrder;
    for (const Container& container : port.arrival){
        loadOrder.insert(loadOrder.begin(), container);
    }
    return loadOrder;
}

int findTargetSecNum(const Port& port) {
    int targetSecNum{};
    int currSecNum {};
    for (const ShipSection& section : port.sections) {
        if (section.totalWeight < port.sections[targetSecNum].totalWeight) {
            targetSecNum = currSecNum;
        }
        ++currSecNum;
    }
    return targetSecNum;
}

bool putContainerIntoSection(Port& port, const Container& container, int targetSecNum) {
    bool isPut = false;
    int curSecNum {};
    for (ShipSection& section : port.sections) {
        if (curSecNum == targetSecNum) {
            section.totalWeight += container.weight;
            section.containIds.push_back(container.id);
            isPut = true;
        }
        ++curSecNum;
    }
    return isPut;
}

string printSections(const Port& port) {
    string message{};
    int sectionNumber {1};
    for (const ShipSection& section : port.sections) {
        message += "Секция " + to_string(sectionNumber) + " " + to_string(section.totalWeight) + " тонн: ";
        for (const string& id : section.containIds) {
            message += id + " ";
        }
        message += '\n';
        ++sectionNumber;
    }
    return message;
}
