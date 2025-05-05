#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "measure.cpp"
using namespace std;

void printV(vector<int> A) {
    for (int x : A) {
        cout << x << "\t";
    }
    cout << "\n";
}

int partition(vector<int>& A, int left, int right) {
    int index = left + rand() % (right - left + 1);
    int pivot = A[index]; 
    swap(A[index], A[right]);

    int i = left;
    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            swap(A[i], A[j]);
            i++;
        }
    }
    swap(A[i], A[right]);
    return i;
}

int quick_select(vector<int>& A, int k) {
    int left = 0;
    int right = A.size() - 1;
    int piv;
    k = k - 1;

    // Ensuring the random seed is only called once
    srand(time(0)); // Put this at the start of the program, not inside the partition

    while (left <= right) {
        piv = partition(A, left, right);
        if (piv == k) {
            return A[piv]; // Found the kth element
        }
        else if (piv > k) {
            right = piv - 1; // Look in the left part
        }
        else {
            left = piv + 1; // Look in the right part
        }
    }

    return -1; // k is out of bounds
}

int main() {
    // init
    int n = 160000000;
    int epoch = 1000;
    double qsum = 0, msum = 0;
    double k;
    vector<int> A;

    cout << "For input size N: " << n << "\nAverage of " << epoch << " runs\n";

    // Vector initialization
    std::mt19937 gen(0); 
    std::uniform_int_distribution<> dis(0, 99999999); 
    A = vector<int>(n);
    for (int i = 0; i < n; i++) {
        A[i] = dis(gen);
    }

    for (int i = 0; i < epoch; i++) {
        // qselect analysis
        auto start1 = measure_start();
        int x = quick_select(A, rand() % n);
        k = measure_end(start1);
        qsum += (k / epoch);
    }

    cout << "Quick select average : " << qsum << "\n";

    return 0;
}
