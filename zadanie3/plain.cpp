#include "plain.h"


bool hasTown(const Plane& plane, const string& town) {
    bool isFound = false;
    for (const string& currentTown : plane.towns) {
        if (currentTown == town) {
            isFound = true;
        }
    }
    return isFound;
}

string createPlane(AirTraffic& traffic, const string& name, const vector<string>& towns) {
    string reportPlane{};
    bool isVklychat = false;
    for (const Plane& plane : traffic.planes) {
        if (plane.name == name) {
            isVklychat = true;
        }
    }
    if (isVklychat) {
        reportPlane = "Самолет уже есть";
    } else {
        Plane newPlane;
        newPlane.name = name;
        for (const string& town : towns) {
            newPlane.towns.push_back(town);
        }
        traffic.planes.push_back(newPlane);
        reportPlane = "Самолет создан";
    }
    return reportPlane;
}


string planesForTown(const AirTraffic& traffic, const string& town) {
    string message{};
    vector<string> foundPlanes{};
    for (const Plane& plane : traffic.planes) {
        if (hasTown(plane, town)) {
            foundPlanes.push_back(plane.name);
        }
    }
    if (foundPlanes.empty()) {
        message = "Город не найден";
    } else {
        message = "Самолеты: ";
        for (const string& planeName : foundPlanes) {
            message += planeName + " ";
        }
    }
    return message;
}


string townsForPlane(const AirTraffic& traffic, const string& planeName) {
    string reportPlane{};
    for (const Plane& plane : traffic.planes) {
        if (plane.name == planeName) {
            reportPlane = "Города самолета " + planeName + ":\n";
            for (const string& town : plane.towns) {
                reportPlane += "Город " + town + ": ";
                for (const Plane& otherPlane : traffic.planes) {
                    if (otherPlane.name != planeName && hasTown(otherPlane, town)) {
                        reportPlane += otherPlane.name + " ";
                    }
                }
                reportPlane += "\n";
            }
        }
    }
    return reportPlane;
}


string allPlanes(const AirTraffic& traffic) {
    string reportPlanes{};
    for (const Plane& plane : traffic.planes) {
        reportPlanes += "Самолет " + plane.name + ": ";
        for (const string& town : plane.towns) {
            reportPlanes += town + " ";
        }
        reportPlanes += "\n";
    }
    return reportPlanes;
}



