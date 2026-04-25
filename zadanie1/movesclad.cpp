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
                    warehouse.push_back({buildAddress(zone, rack, section, shelf), "", 0});
                }
            }
        }
    }
    return warehouse;
}

void addProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address) {
    int cellIndex = findCellIndex(warehouse, address);
    if (cellIndex == -1) {
        cout << "Ошибка: Ячейка " << address << " не найдена\n";
    } else if (!warehouse[cellIndex].product.empty() && warehouse[cellIndex].product != product) {
        cout << "Ошибка: Ячейка " << address << " занята товаром " << warehouse[cellIndex].product << '\n';
    } else if (warehouse[cellIndex].quantity + quantity > MAX_PER_CELL) {
        cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
    } else {
        warehouse[cellIndex].product = product;
        warehouse[cellIndex].quantity += quantity;
        cout << "Добавлено " << quantity << " " << product << " в " << address << '\n';
    }
}

void removeProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address) {
    int cellIndex = findCellIndex(warehouse, address);
    if (cellIndex == -1) {
        cout << "Ошибка: Ячейка " << address << " не найдена\n";
    } else if (warehouse[cellIndex].product != product || warehouse[cellIndex].quantity == 0) {
        cout << "Ошибка: Товар " << product << " не найден в ячейке " << address << '\n';
    } else if (warehouse[cellIndex].quantity < quantity) {
        cout << "Ошибка: Недостаточно товаров для удаления\n";
    } else {
        warehouse[cellIndex].quantity -= quantity;
        cout << "Удалено " << quantity << " " << product << " (остаток: " << warehouse[cellIndex].quantity << ")\n";
        if (warehouse[cellIndex].quantity == 0) {
            warehouse[cellIndex].product = "";
        }
    }
}

void info(const vector<Cell>& warehouse) {
    vector<string> zones{"А", "Б", "В"};
    vector<int> zoneQuantities{0, 0, 0};
    vector<string> emptyAddresses;
    int totalQuantity {};
    for (const Cell& cell : warehouse) {
        totalQuantity += cell.quantity;
        if (cell.quantity == 0) {
            emptyAddresses.push_back(cell.address);
        }
        if (isZoneAddress(cell.address, "А")) {
            zoneQuantities[0] += cell.quantity;
        } else if (isZoneAddress(cell.address, "Б")) {
            zoneQuantities[1] += cell.quantity;
        } else if (isZoneAddress(cell.address, "В")) {
            zoneQuantities[2] += cell.quantity;
        }
    }
    cout << fixed << setprecision(2);
    cout << "Загруженность склада: "
         << static_cast<double>(totalQuantity) * 100.0 / TOTAL_CAPACITY << " %\n";

    int zoneNumber {};
    for (const string& zone : zones) {
        cout << "Загруженность зоны " << zone << ": "
             << static_cast<double>(zoneQuantities[zoneNumber]) * 100.0 / ZONE_CAPACITY << " %\n";
        ++zoneNumber;
    }
    cout << "Заполненные ячейки:\n";
    for (const Cell& cell : warehouse) {
        if (cell.quantity > 0) {
            cout << cell.address << ": " << cell.product << " (" << cell.quantity << ")\n";
        }
    }
    cout << "Пустые ячейки:\n";
    int addressNumber {};
    for (const string& address : emptyAddresses) {
        if (addressNumber > 0) {
            cout << ", ";
        }
        cout << address;
        ++addressNumber;
    }
    cout << '\n';
}

void processCommand(vector<Cell>& warehouse, const string& commandLine) {
    istringstream input(commandLine);
    string command{};
    input >> command;
    if (command == "ADD") {
        string product{};
        int quantity {};
        string address{};
        input >> product >> quantity >> address;
        addProduct(warehouse, product, quantity, address);
    } else if (command == "REMOVE") {
        string product{};
        int quantity {};
        string address{};
        input >> product >> quantity >> address;
        removeProduct(warehouse, product, quantity, address);
    } else if (command == "INFO") {
        info(warehouse);
    } else if (!command.empty()) {
        cout << "Ошибка: Неизвестная команда\n";
    }
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
    for (const Cell& cell : warehouse) {
        if (cell.address == address) {
            return index;
        }
        ++index;
    }
    return -1;
}

bool isZoneAddress(const string& address, const string& zone) {
    return address.find(zone) == 0;
}