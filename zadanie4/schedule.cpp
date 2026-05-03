#include "schedule.h"

bool initSchedule(Schedule& schedule) {
    bool isReady = true;
    schedule.currentMonthIndex = 0;
    schedule.monthLengths = {30, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    schedule.disciplinesByDay.clear();
    schedule.disciplinesByDay.resize(schedule.monthLengths[0]);
    return isReady;
}

vector<string> splitCommand(const string& commandLine) {
    istringstream input(commandLine);
    vector<string> tokens{};
    for (string token{}; input >> token;) {
        tokens.push_back(token);
    }
    return tokens;
}

string addDiscipline(Schedule& schedule, int dayNumber, const string& discipline) {
    string message{};
    int maxDays = schedule.disciplinesByDay.size();
    if (dayNumber < 1 || dayNumber > maxDays) {
        message = "Ошибка: В этом месяце всего " + to_string(maxDays) + " дней";
    } else {
        vector<string>& disciplines = schedule.disciplinesByDay[dayNumber - 1];
        bool isFound = false;
        for (const string& currentDiscipline : disciplines) {
            if (currentDiscipline == discipline) {
                isFound = true;
            }
        }
        if (isFound) {
            message = "Ошибка: Дисциплина " + discipline + " уже есть в этот день";
        } else {
            disciplines.push_back(discipline);
            message = "Добавлена дисциплина " + discipline + " на день " + to_string(dayNumber);
        }
    }
    return message;
}

vector<vector<string>> buildNextMonth(const Schedule& schedule, int nextMonthLength) {
    vector<vector<string>> nextMonth(nextMonthLength);
    int dayNumber = 1;
    for (const vector<string>& disciplines : schedule.disciplinesByDay) {
        int newDay = dayNumber;
        if (newDay > nextMonthLength) {
            newDay = nextMonthLength;
        }
        for (const string& discipline : disciplines) {
            nextMonth[newDay - 1].push_back(discipline);
        }
        ++dayNumber;
    }
    return nextMonth;
}


string goToNextMonth(Schedule& schedule) {
    string message{};
    int nextMonth = schedule.currentMonthIndex + 1;
    int monthCount = schedule.monthLengths.size();
    if (nextMonth == monthCount) {
        nextMonth = 0;
    }
    schedule.disciplinesByDay = buildNextMonth(schedule, schedule.monthLengths[nextMonth]);
    schedule.currentMonthIndex = nextMonth;
    message = "Переход на следующий месяц";
    return message;
}


string viewDay(const Schedule& schedule, int dayNumber) {
    string message{};
    int maxDays = schedule.disciplinesByDay.size();
    if (dayNumber < 1 || dayNumber > maxDays) {
        message = "Ошибка: В этом месяце всего " + to_string(maxDays) + " дней";
    } else {
        const vector<string>& disciplines = schedule.disciplinesByDay[dayNumber - 1];
        if (disciplines.empty()) {
            message = "В день " + to_string(dayNumber) + " мы свободны!";
        } else {
            message = "В день " + to_string(dayNumber) + " занятия в университете: ";
            bool isFirstDiscipline = true;
            for (const string& discipline : disciplines) {
                if (!isFirstDiscipline) {
                    message += ", ";
                }
                message += discipline;
                isFirstDiscipline = false;
            }
        }
    }
    return message;
}


string processCommand(Schedule& schedule, const string& commandLine) {
    string message{};
    vector<string> tokens = splitCommand(commandLine);
    string command{};
    if(!tokens.empty()){
        command = tokens[0];
    }
    if (command == "CLASS"){
        if (tokens.size() < 3){
            message = "Ошибка: Неверный формат команды CLASS";
        } else{
            message = addDiscipline(schedule, stoi(tokens[1]), tokens[2]);
        }
    } else if (command == "NEXT"){
        message = goToNextMonth(schedule);
    } else if (command == "VIEW"){
        if (tokens.size() < 2) {
            message = "Ошибка: Неверный формат команды VIEW";
        } else {
            message = viewDay(schedule, stoi(tokens[1]));
        }
    } else if (!command.empty()){
        message = "Ошибка: Неизвестная команда";
    }
    return message;
}
