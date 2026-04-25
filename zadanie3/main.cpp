#include "plain.h"

int main() {
    AirTraffic traffic;
    string commandLine;
    for (; getline(cin, commandLine); ) {
        processCommand(traffic, commandLine);
    }
    return 0;
}
