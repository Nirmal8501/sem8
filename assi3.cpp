#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int parallelMin(const vector<int>& values) {
    int minVal = values[0];
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] < minVal) {
            minVal = values[i];
        }
    }
    return minVal;
}

int parallelMax(const vector<int>& values) {
    int maxVal = values[0];
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] > maxVal) {
            maxVal = values[i];
        }
    }
    return maxVal;
}

int parallelSum(const vector<int>& values) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < values.size(); ++i) {
        sum += values[i];
    }
    return sum;
}

float parallelAverage(const vector<int>& values) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < values.size(); ++i) {
        sum += values[i];
    }
    // return static_cast<double>(sum) / values.size();
    return sum * 1.0 /values.size();
}

int main() {
    vector<int> values = {3, 7, 2, 8, 1, 6, 5, 4, 9, 10};

    // Min operation
    int minVal = parallelMin(values);
    cout << "Min value: " << minVal << endl;

    // Max operation
    int maxVal = parallelMax(values);
    cout << "Max value: " << maxVal << endl;

    // Sum operation
    int sum = parallelSum(values);
    cout << "Sum: " << sum << endl;

    // Average operation
    double average = parallelAverage(values);
    cout << "Average: " << average << endl;

    return 0;
}
