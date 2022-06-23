#include <iostream>
#include <tchar.h>
#include <sstream>
#include <fstream>
#include <windows.h>
#include "Employee.h"

using namespace std;

void startCreator(string &binFileName, int amount) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    stringstream ss;
    ss << amount;
    string arguments = binFileName + ' ' + ss.str();

    bool flag = CreateProcess("Creator.exe", &arguments[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
                              NULL, &si, &pi);
    if (!flag)
        GetLastError();
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void startReporter(string &binFileName, string &reportFileName, double salary) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    stringstream ss;
    ss << salary;
    string arguments = binFileName + " " + reportFileName + " " + ss.str();
    bool flag = CreateProcess("Reporter.exe", &arguments[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
                              NULL, &si,
                              &pi);
    if (!flag) GetLastError();
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}

int main() {
    string binFileName;
    int amount;
    cout << "Enter binary file name" << endl;
    cin >> binFileName;
    cout << "Enter amount of employees" << endl;
    cin >> amount;

    startCreator(binFileName, amount);

    ifstream in(&binFileName[0], ios::binary);
    employee e;
    while (in.read((char *) &e, sizeof(employee))) {
        cout << e.num << " " << e.name << " " << e.hours << endl;
    }

    in.close();

    string reportFileName;
    double salary;
    cout << "Enter report file name" << endl;
    cin >> reportFileName;
    cout << "Enter salary" << endl;
    cin >> salary;
    startReporter(binFileName, reportFileName, salary);
    string line;
    in.open(&reportFileName[0]);
    while (getline(in, line))
        cout << line << endl;
    system("pause");
    return 0;
}