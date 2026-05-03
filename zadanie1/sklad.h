#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

const int ZONES = 3;
const int RACKS = 14;
const int SECTIONS = 4;
const int SHELVES = 8;
const int MAX_PER_CELL = 10;
const int TOTAL_CAPACITY = ZONES * RACKS * SECTIONS * SHELVES * MAX_PER_CELL;
const int ZONE_CAPACITY = RACKS * SECTIONS * SHELVES * MAX_PER_CELL;

struct Cell {
    string address;
    string product;
    int quantity;
};

int findCellIndex(const vector<Cell>& warehouse, const string& address);
bool isZoneAddress(const string& address, const string& zone);
string buildAddress(const string& zone, int rack, int section, int shelf);
vector<Cell> createWarehouse();
string addProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address);
string removeProduct(vector<Cell>& warehouse, const string& product, int quantity, const string& address);
string info(const vector<Cell>& warehouse);
string processCommand(vector<Cell>& warehouse, const string& commandLine);
