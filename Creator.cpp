#include <iostream>
#include <fstream>
#include <sstream>
#include "Employee.h"

using namespace std;

int main(int argc, char *argv[]) {
    fstream out(argv[0], ios::out | ios::binary);
    istringstream is(argv[1]);
    int count;
    is >> count;
    for (int i = 0; i < count; ++i) {
        employee e;
        cout << "Enter id\n";
        cin >> e.num;
        cout << "Enter name\n";
        cin >> e.name;
        cout << "Enter hours\n";
        cin >> e.hours;
        out.write((char *) &e, sizeof(employee));
    }
    out.close();
    return 0;
}