#include "sklad.h"

int main() {
    vector<Cell> warehouse = createWarehouse();
    string commandLine;
    for (; getline(cin, commandLine); ) {
        processCommand(warehouse, commandLine);
    }
    return 0;
}
