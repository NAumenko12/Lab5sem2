#include "plain.h"

int main() {
    AirTraffic traffic{};
    for (string line{}; getline(cin, line);) {
        string result = processCommand(traffic, line);
        cout << result << "\n";
    }
    return 0;
}
