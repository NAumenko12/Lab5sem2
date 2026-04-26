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
void processCommand(Schedule& schedule, const string& commandLine);
vector<string> splitCommand(const string& commandLine);
void viewDay(const Schedule& schedule, int dayNumber);
void addDiscipline(Schedule& schedule, int dayNumber, const string& discipline);
bool isValidDay(const Schedule& schedule, int dayNumber);
void goToNextMonth(Schedule& schedule);
vector<vector<string>> buildNextMonth(const Schedule& schedule, int nextMonthLength);
