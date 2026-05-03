#include "sklad.h"

int main() {
    vector<Cell> warehouse = createWarehouse();
    for (string commandLine{}; getline(cin, commandLine); ) {
        string message = processCommand(warehouse, commandLine);
        cout << message << '\n';
    }
    return 0;
}
