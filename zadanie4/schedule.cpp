#include "schedule.h"

void initSchedule(Schedule& schedule) {
    schedule.currentMonthIndex = 0;
    schedule.monthLengths = {30, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    schedule.disciplinesByDay.clear();
    schedule.disciplinesByDay.resize(schedule.monthLengths[0]);
}

vector<string> splitCommand(const string& commandLine) {
    istringstream input(commandLine);
    vector<string> tokens;
    string token{};
    while (input >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


bool isValidDay(const Schedule& schedule, int dayNumber) {
    return dayNumber >= 1 && dayNumber <= static_cast<int>(schedule.disciplinesByDay.size());
}

void addDiscipline(Schedule& schedule, int dayNumber, const string& discipline) {
    if (dayNumber < 1 || dayNumber > static_cast<int>(schedule.disciplinesByDay.size())) {
        cout << "Ошибка: В этом месяце всего " << schedule.disciplinesByDay.size() << " дней\n";
    } else {
        vector<string>& dayDisciplines = schedule.disciplinesByDay[dayNumber - 1];
        bool hasDuplicateDiscipline = false;
        for (const string& currentDiscipline : dayDisciplines) {
            if (currentDiscipline == discipline) {
                hasDuplicateDiscipline = true;
            }
        }
        if (hasDuplicateDiscipline) {
            cout << "Ошибка: Дисциплина " << discipline << " уже есть в этот день\n";
        } else {
            dayDisciplines.push_back(discipline);
            cout << "Добавлена дисциплина " << discipline << " на день " << dayNumber << '\n';
        }
    }
}


vector<vector<string>> buildNextMonth(const Schedule& schedule, int nextMonthLength) {
    vector<vector<string>> nextMonth(nextMonthLength);
    int currentDayNumber = 1;
    for (const vector<string>& disciplines : schedule.disciplinesByDay) {
        int targetDayNumber = currentDayNumber;
        if (targetDayNumber > nextMonthLength) {
            targetDayNumber = nextMonthLength;
        }
        vector<string>& targetDay = nextMonth[targetDayNumber - 1];
        for (const string& discipline : disciplines) {
            targetDay.push_back(discipline);
        }
        ++currentDayNumber;
    }
    return nextMonth;
}

void goToNextMonth(Schedule& schedule) {
    int nextMonthIndex = schedule.currentMonthIndex + 1;
    if (nextMonthIndex == static_cast<int>(schedule.monthLengths.size())) {
        nextMonthIndex = 0;
    }
    int nextMonthLength = schedule.monthLengths[nextMonthIndex];
    schedule.disciplinesByDay = buildNextMonth(schedule, nextMonthLength);
    schedule.currentMonthIndex = nextMonthIndex;
    cout << "Переход на следующий месяц\n";
}

void viewDay(const Schedule& schedule, int dayNumber) {
    if (!isValidDay(schedule, dayNumber)) {
        cout << "Ошибка: В этом месяце всего " << schedule.disciplinesByDay.size() << " дней\n";
        return;
    }
    const vector<string>& dayDisciplines = schedule.disciplinesByDay[dayNumber - 1];
    if (dayDisciplines.empty()) {
        cout << "В день " << dayNumber << " мы свободны!\n";
        return;
    }
    cout << "В день " << dayNumber << " занятия в университете: ";
    bool isFirstDiscipline = true;
    for (const string& discipline : dayDisciplines) {
        if (!isFirstDiscipline) {
            cout << ", ";
        }
        cout << discipline;
        isFirstDiscipline = false;
    }
    cout << '\n';
}

void processCommand(Schedule& schedule, const string& commandLine) {
    vector<string> tokens = splitCommand(commandLine);
    if (tokens.empty()) {
        return;
    }
    if (tokens[0] == "CLASS") {
        if (tokens.size() < 3) {
            cout << "Ошибка: Неверный формат команды CLASS\n";
            return;
        }
        addDiscipline(schedule, stoi(tokens[1]), tokens[2]);
        return;
    }
    if (tokens[0] == "NEXT") {
        goToNextMonth(schedule);
        return;
    }
    if (tokens[0] == "VIEW") {
        if (tokens.size() < 2) {
            cout << "Ошибка: Неверный формат команды VIEW\n";
            return;
        }
        viewDay(schedule, stoi(tokens[1]));
        return;
    }
    cout << "Ошибка: Неизвестная команда\n";
}
