#include "port.h"

void processComand(Port& port, const string& comandFull) {
    istringstream input(comandFull);
    string comand{};
    input >> comand;
    if (comand == "ARRIVE") {
        string id {};
        int weight {};
        input >> id >> weight;
        arrive(port, id, weight);
    } else if (comand == "LOAD") {
        load(port);
    } else {
        cout << "Неизвестная команда\n";
    }
}

void initPort(Port& port, int maxStackWeight, int numSections) {
    port.maxStackWeight = maxStackWeight;
    port.sections.clear();
    port.sections.resize(numSections);
    for (ShipSection& section : port.sections) {
        section.totalWeight = 0;
        section.containIds.clear();
    }
}

void arrive(Port& port, const string& id, int weight) {
    bool isFound = false;
    int stackNumber = 1;
    int foundStackNumber = 0;
    for (PortStack& portStack : port.stacks) {
        if (!isFound && portStack.curWeight + weight <= port.maxStackWeight) {
            isFound = true;
            foundStackNumber = stackNumber;
        }
        ++stackNumber;
    }
    if (isFound) {
        PortStack& portStack = port.stacks[foundStackNumber - 1];
        portStack.containers.push({id, weight});
        portStack.curWeight += weight;
        port.arrival.push_back({id, weight});
        cout << "Контейнер " << id << " размещен в стек " << foundStackNumber << '\n';
    } else {
        PortStack newStack;
        newStack.curWeight = weight;
        newStack.containers.push({id, weight});
        port.stacks.push_back(newStack);
        port.arrival.push_back({id, weight});
        cout << "Контейнер " << id << " размещен в стек " << port.stacks.size() << '\n';
    }
}

void load(Port& port) {
    for (const Container& container :loadingOrder(port)){
        int targetSecNum = findTargetSecNum(port);
        putContainerIntoSection(port, container, targetSecNum);
    }
    printSections(port);
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

void putContainerIntoSection(Port& port, const Container& container, int targetSecNum) {
    int curSecNum {};
    for (ShipSection& section : port.sections) {
        if (curSecNum == targetSecNum) {
            section.totalWeight += container.weight;
            section.containIds.push_back(container.id);
        }
        ++curSecNum;
    }
}

void printSections(const Port& port) {
    int sectionNumber {1};
    for (const ShipSection& section : port.sections) {
        cout << "Секция " << sectionNumber << " (" << section.totalWeight << " тонн): ";
        int idNumber {};
        for (const string& id : section.containIds) {
            if (idNumber > 0) {
                cout << ", ";
            }
            cout << id;
            ++idNumber;
        }
        cout << '\n';
        ++sectionNumber;
    }
}
