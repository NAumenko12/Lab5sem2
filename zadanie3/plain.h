#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

enum class Type {
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
};

struct Plane {
    string name;
    vector<string> towns;
};

struct AirTraffic {
    vector<Plane> planes;
};

bool getCommandType(const string& command, Type& commandType);
vector<string> splitCommand(const string& commandLine);
bool hasPlane(const AirTraffic& traffic, const string& planeName);
bool hasTown(const Plane& plane, const string& town);
bool hasDuplicateTowns(const vector<string>& towns);
void createPlane(AirTraffic& traffic, const vector<string>& tokens);
void printPlanesForTown(const AirTraffic& traffic, const vector<string>& tokens);
void printOtherPlanesForTown(const AirTraffic& traffic, const string& town, const string& planeName);
void printTownsForPlane(const AirTraffic& traffic, const vector<string>& tokens);
void printPlanes(const AirTraffic& traffic);
void processCommand(AirTraffic& traffic, const string& commandLine);
