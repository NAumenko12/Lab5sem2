#include "sklad.h"

vector<Cell> createWarehouse() {
    vector<Cell> warehouse;
    vector<string> zones{"А", "Б", "В"};
    vector<int> racks{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    vector<int> sections{1, 2, 3, 4};
    vector<int> shelves{1, 2, 3, 4, 5, 6, 7, 8};
    for (const string& zone : zones) {
        for (int rack : racks) {
            for (int section : sections) {
                for (int shelf : shelves) {
                    Cell cell;
                    cell.address = buildAddress(zone, rack, section, shelf);
                    cell.product = "";
                    cell.quantity = 0;
                    warehouse.push_back(cell);
                }
            }
        }
    }
    return warehouse;
}

string addProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address) {
    string message{};
    int cellIndex = findCellIndex(warehouse, address);
    if (cellIndex == -1) {
        message = "Ячейка не найдена";
    } else if (!warehouse[cellIndex].product.empty() && warehouse[cellIndex].product != product) {
        message = "Ячейка занята";
    } else if (warehouse[cellIndex].quantity + quantity > MAX_PER_CELL) {
        message = "Превышена вместимость";
    } else {
        warehouse[cellIndex].product = product;
        warehouse[cellIndex].quantity += quantity;
        message = "Добавлено " + to_string(quantity) + " " + product + " в " + address;
    }
    return message;
}

string removeProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address) {
    string message{};
    int cellIndex = findCellIndex(warehouse, address);
    if (cellIndex == -1) {
        message = "Ячейка не найдена";
    } else if (warehouse[cellIndex].product != product || warehouse[cellIndex].quantity == 0) {
        message = "Товар не найден";
    } else if (warehouse[cellIndex].quantity < quantity) {
        message = "Недостаточно товара";
    } else {
        warehouse[cellIndex].quantity -= quantity;
        message = "Удалено " + to_string(quantity) + " " + product + " (остаток: " + to_string(warehouse[cellIndex].quantity) + ")";
        if (warehouse[cellIndex].quantity == 0) {
            warehouse[cellIndex].product = "";
        }
    }
    return message;
}

string info(const vector<Cell>& warehouse) {
    string message{};
    vector<string> zones{"А", "Б", "В"};
    vector<int> zoneQuantities{0, 0, 0};
    int totalQuantity{};
    for (const Cell& cell : warehouse) {
        totalQuantity += cell.quantity;
        if (isZoneAddress(cell.address, "А")) {
            zoneQuantities[0] += cell.quantity;
        } else if (isZoneAddress(cell.address, "Б")) {
            zoneQuantities[1] += cell.quantity;
        } else if (isZoneAddress(cell.address, "В")) {
            zoneQuantities[2] += cell.quantity;
        }
    }
    ostringstream output;
    output << fixed << setprecision(2);
    output << "Загруженность склада: " << totalQuantity * 100.0 / TOTAL_CAPACITY << " %\n";
    int zoneNumber{};
    for (const string& zone : zones) {
        output << "Загруженность зоны " << zone << ": " << zoneQuantities[zoneNumber] * 100.0 / ZONE_CAPACITY << " %\n";
        ++zoneNumber;
    }
    output << "Заполненные ячейки:\n";
    for (const Cell& cell : warehouse) {
        if (cell.quantity > 0) {
            output << cell.address << ": " << cell.product << " (" << cell.quantity << ")\n";
        }
    }
    output << "Пустые ячейки:\n";
    for (const Cell& cell : warehouse) {
        if (cell.quantity == 0) {
            output << cell.address << " ";
        }
    }
    message = output.str();
    return message;
}


string processCommand(vector<Cell>& warehouse, const string& commandLine) {
    string message{};
    istringstream input(commandLine);
    string command{};
    string product{};
    int quantity{};
    string address{};
    input >> command;
    if (command == "ADD") {
        input >> product >> quantity >> address;
        message = addProduct(warehouse, product, quantity, address);
    } else if (command == "REMOVE") {
        input >> product >> quantity >> address;
        message = removeProduct(warehouse, product, quantity, address);
    } else if (command == "INFO") {
        message = info(warehouse);
    } else if (!command.empty()) {
        message = "Неизвестная команда";
    }
    return message;
}


string buildAddress(const string& zone, int rack, int section, int shelf) {
    string address = zone;
    if (rack < 10) {
        address += "0";
    }
    address += to_string(rack);
    address += to_string(section);
    address += to_string(shelf);
    return address;
}

int findCellIndex(const vector<Cell>& warehouse, const string& address) {
    int index {};
    int foundIndex {-1};
    for (const Cell& cell : warehouse) {
        if (cell.address == address) {
            foundIndex = index;
        }
        ++index;
    }
    return foundIndex;
}

bool isZoneAddress(const string& address, const string& zone) {
    return address.find(zone) == 0;
}
