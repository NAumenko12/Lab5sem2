#pragma once

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Schedule {
    int currentMonthIndex;
    vector<int> monthLengths;
    vector<vector<string>> disciplinesByDay;
};

void initSchedule(Schedule& schedule);
string processCommand(Schedule& schedule, const string& commandLine);
vector<string> splitCommand(const string& commandLine);
string viewDay(const Schedule& schedule, int dayNumber);
string addDiscipline(Schedule& schedule, int dayNumber, const string& discipline);
string goToNextMonth(Schedule& schedule);
vector<vector<string>> buildNextMonth(const Schedule& schedule, int nextMonthLength);
