#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class Type {
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    UNKNOWN
};

struct Plane {
    string name;
    vector<string> towns;
};

struct AirTraffic {
    vector<Plane> planes;
};

string createPlane(AirTraffic& traffic, const string& name, const vector<string>& towns);
string planesForTown(const AirTraffic& traffic, const string& town);
string townsForPlane(const AirTraffic& traffic, const string& planeName);
string allPlanes(const AirTraffic& traffic);
Type parseCommandType(const string& command);
vector<string> splitLine(const string& line);
bool hasTown(const Plane& plane, const string& town);
string processCommand(AirTraffic& traffic, const string& line);
