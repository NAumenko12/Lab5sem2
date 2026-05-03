#include "port.h"

int main() {
    Port port{};
    string maxStack{};
    string numSections{};
    cout << "Введите максимальный размер стека: \n ";
    getline(cin, maxStack);
    cout << "Введите количество секций судна: \n ";
    getline(cin, numSections);
    initPort(port, stoi(maxStack), stoi(numSections));
    for (string command{}; getline(cin, command); ) {
        string message = processCommand(port, command);
        cout << message << '\n';
    }
    return 0;
}
