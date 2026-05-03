#include "plain.h"

Type parseCommandType(const string& command) {
    Type result = Type::UNKNOWN;
    if (command == "CREATE_PLANE") {
        result = Type::CREATE_PLANE;
    } else if (command == "PLANES_FOR_TOWN") {
        result = Type::PLANES_FOR_TOWN;
    } else if (command == "TOWNS_FOR_PLANE") {
        result = Type::TOWNS_FOR_PLANE;
    } else if (command == "PLANES") {
        result = Type::PLANES;
    }
    return result;
}

vector<string> splitLine(const string& line) {
    vector<string> tokens;
    istringstream stream(line);
    for (string token; stream >> token;) {
        tokens.push_back(token);
    }
    return tokens;
}

string processCommand(AirTraffic& traffic, const string& line) {
    string report{};
    vector<string> tokens = splitLine(line);
    if (tokens.empty()) {
        report = "Пустая команда";
    } else {
        Type command = parseCommandType(tokens[0]);
        switch (command) {
            case Type::CREATE_PLANE: {
                if (tokens.size() < 4) {
                    report = "Неверная команда";
                } else {
                    string planeName = tokens[1];
                    int townCount = stoi(tokens[2]);
                    vector<string> towns{};
                    int tokenNumber = 0;
                    for (const string& token : tokens) {
                        if (tokenNumber > 2) {
                            towns.push_back(token);
                        }
                        tokenNumber++;
                    }
                    if (townCount != static_cast<int>(towns.size())) {
                        report = "Неверное число городов";
                    } else {
                        report = createPlane(traffic, planeName, towns);
                    }
                }
                break;
            }
            case Type::PLANES_FOR_TOWN: {
                if (tokens.size() < 2) {
                    report = "Город не указан";
                } else {
                    report = planesForTown(traffic, tokens[1]);
                }
                break;
            }
            case Type::TOWNS_FOR_PLANE: {
                if (tokens.size() < 2) {
                    report = "Самолет не указан";
                } else {
                    report = townsForPlane(traffic, tokens[1]);
                }
                break;
            }
            case Type::PLANES: {
                report = allPlanes(traffic);
                break;
            }
            default: {
                report = "Неизвестная команда";
                break;
            }
        }
    }
    return report;
}
