#include <iostream>
#include <chrono>
using namespace std;

    

chrono::high_resolution_clock::time_point measure_start() {
    auto start = chrono::high_resolution_clock::now();
    return start;
}

double measure_end(chrono::high_resolution_clock::time_point start) {
    for (int i = 0; i < 1000000; ++i) {
        int x = i * i;
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;
    double durationms = duration.count();
    //cout << "Execution time: " << durationms << " ms" << endl;

    return durationms;
}
