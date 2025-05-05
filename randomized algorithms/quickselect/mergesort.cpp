#include <iostream>
#include <vector>
#include <random>
#include "measure.cpp"
// Merge function to combine two sorted halves into a sorted result
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays to hold the left and right subarrays
    std::vector<int> L(n1), R(n2);

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into the original array
    int i = 0; // Initial index of left subarray
    int j = 0; // Initial index of right subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function to divide and conquer the array
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}
int main() {
    // init
    int n = 160000000;
    int epoch = 1;
    double qsum = 0;
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
        auto start1 = measure_start();
        mergeSort(A, 0, n - 1);
        k = measure_end(start1);
        cout << i + 1 << " run : " << k << " msecs\n";
        qsum += k;
    }

    cout << "Mergesort : " << qsum / epoch << "\n";

    return 0;
}


