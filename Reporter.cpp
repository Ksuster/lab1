#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Employee.h"

using namespace std;

int main(int argc, char *argv[]) {

    ifstream in(argv[0], ios::binary);
    ofstream out(argv[1]);
    out << "Report on file " << argv[0] << ":" << endl;
    out << "Id, hours, salary per hour, salary" << endl;

    double salary = atof(argv[2]);

    employee e;
    while (in.read((char *) &e, sizeof(employee))) {
        out << e.num << " " << e.name << " " << e.hours << " " << e.hours * salary << endl;
    }
    in.close();
    out.close();
    return 0;
}