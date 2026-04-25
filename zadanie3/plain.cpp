#include "plain.h"

bool getCommandType(const string& command, Type& commandType) {
    bool isComand{false};
    if (command == "CREATE_PLANE") {
        commandType = Type::CREATE_PLANE;
        isComand = true;
    } else if (command == "PLANES_FOR_TOWN") {
        commandType = Type::PLANES_FOR_TOWN;
        isComand = true;
    } else if (command == "TOWNS_FOR_PLANE") {
        commandType = Type::TOWNS_FOR_PLANE;
        isComand = true;
    } else if (command == "PLANES") {
        commandType = Type::PLANES;
        isComand = true;
    }
    return isComand;
}

void processCommand(AirTraffic& traffic, const string& commandLine) {
    vector<string> tokens = splitCommand(commandLine);
    if (!tokens.empty()) {
        Type commandType = Type::PLANES;
        if (!getCommandType(tokens[0], commandType)) {
            cout << "Ошибка: Неизвестная команда\n";
        } else {
            switch (commandType) {
                case Type::CREATE_PLANE:
                    createPlane(traffic, tokens);
                    break;
                case Type::PLANES_FOR_TOWN:
                    printPlanesForTown(traffic, tokens);
                    break;
                case Type::TOWNS_FOR_PLANE:
                    printTownsForPlane(traffic, tokens);
                    break;
                case Type::PLANES:
                    printPlanes(traffic);
                    break;
            }
        }
    }
}
 
vector<string> splitCommand(const string& commandLine) {
    istringstream input(commandLine);
    vector<string> tokens{istream_iterator<string>{input}, istream_iterator<string>{}};
    return tokens;
}

bool hasPlane(const AirTraffic& traffic, const string& planeName) {
    for (const Plane& plane : traffic.planes) {
        if (plane.name == planeName) {
            return true;
        }
    }
    return false;
}

bool hasTown(const Plane& plane, const string& town) {
    for (const string& currentTown : plane.towns) {
        if (currentTown == town) {
            return true;
        }
    }
    return false;
}

bool hasDuplicateTowns(const vector<string>& towns) {
    vector<string> checkedTowns;
    for (const string& town : towns) {
        for (const string& checkedTown : checkedTowns) {
            if (checkedTown == town) {
                return true;
            }
        }
        checkedTowns.push_back(town);
    }
    return false;
}

void createPlane(AirTraffic& traffic, const vector<string>& tokens) {
    if (tokens.size() < 4) {
        cout << "Ошибка: Самолет не может быть создан с одной остановкой\n";
    } else {
        string planeName = tokens[1];
        int townCount = stoi(tokens[2]);
        vector<string> towns;
        for (const string& token : vector<string>(tokens.begin() + 3, tokens.end())) {
            towns.push_back(token);
        }
        if (hasPlane(traffic, planeName)) {
            cout << "Ошибка: Самолет с именем " << planeName << " уже создан\n";
        } else if (townCount < 2 || towns.size() < 2) {
            cout << "Ошибка: Самолет не может быть создан с одной остановкой\n";
        } else if (static_cast<int>(towns.size()) != townCount) {
            cout << "Ошибка: Неверное количество городов\n";
        } else if (hasDuplicateTowns(towns)) {
            cout << "Ошибка: Самолет не может быть создан с одинаковыми городами\n";
        } else {
            traffic.planes.push_back({planeName, towns});
            cout << "Самолет " << planeName << " создан\n";
        }
    }
}

void printPlanesForTown(const AirTraffic& traffic, const vector<string>& tokens) {
    if (tokens.size() < 2) {
        cout << "Ошибка: Город не указан\n";
    } else {
        string town = tokens[1];
        vector<string> planeNames;
        for (const Plane& plane : traffic.planes) {
            if (hasTown(plane, town)) {
                planeNames.push_back(plane.name);
            }
        }
        if (planeNames.empty()) {
            cout << "Ошибка: Город " << town << " не найден\n";
        } else {
            cout << "Самолеты для города " << town << ": ";
            int planeNumber = 0;
            for (const string& planeName : planeNames) {
                if (planeNumber > 0) {
                    cout << ", ";
                }
                cout << planeName;
                ++planeNumber;
            }

            cout << '\n';
        }
    }
}

void printOtherPlanesForTown(const AirTraffic& traffic, const string& town, const string& planeName) {
    vector<string> otherPlanes;
    for (const Plane& plane : traffic.planes) {
        if (plane.name != planeName && hasTown(plane, town)) {
            otherPlanes.push_back(plane.name);
        }
    }
    cout << "Город " << town << ": ";
    if (otherPlanes.empty()) {
        cout << "-";
    } else {
        int planeNumber = 0;
        for (const string& otherPlane : otherPlanes) {
            if (planeNumber > 0) {
                cout << ", ";
            }
            cout << otherPlane;
            ++planeNumber;
        }
    }
    cout << '\n';
}
void printTownsForPlane(const AirTraffic& traffic, const vector<string>& tokens) {
    if (tokens.size() < 2) {
        cout << "Ошибка: Самолет не указан\n";
    } else {
        string planeName = tokens[1];
        bool hasCurrentPlane = false;
        for (const Plane& plane : traffic.planes) {
            if (plane.name == planeName) {
                hasCurrentPlane = true;
                cout << "Города для самолета " << planeName << ": ";
                int townNumber = 0;
                for (const string& town : plane.towns) {
                    if (townNumber > 0) {
                        cout << " ";
                    }
                    cout << town;
                    ++townNumber;
                }
                cout << '\n';
                for (const string& town : plane.towns) {
                    printOtherPlanesForTown(traffic, town, planeName);
                }
            }
        }
        if (!hasCurrentPlane) {
            cout << "Ошибка: Самолет " << planeName << " не найден\n";
        }
    }
}

void printPlanes(const AirTraffic& traffic) {
    if (traffic.planes.empty()) {
        cout << "Ошибка: Самолеты не найдены\n";
    } else {
        for (const Plane& plane : traffic.planes) {
            cout << "Самолет " << plane.name << ": ";
            int townNumber {};
            for (const string& town : plane.towns) {
                if (townNumber > 0) {
                    cout << " ";
                }
                cout << town;
                ++townNumber;
            }
            cout << '\n';
        }
    }
}
