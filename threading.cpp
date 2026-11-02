#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std;

#define NUMBERS 1000000
#define NUM_THREADS 8

int random_values[NUMBERS];
long long partial_sums[NUM_THREADS] = {0};

void calculate_sum(int id) {
    cout << "Thread " << id << " started." << endl;

    int start = id * NUMBERS / NUM_THREADS;
    int end = (id + 1) * NUMBERS / NUM_THREADS;

    long long sum = 0;

    for (int i = start; i < end; i++) {
        sum += random_values[i];
    }

    partial_sums[id] = sum;

    cout << "Thread " << id
         << " finished. Partial sum: " << sum << endl;
}

int main() {

    srand(time(NULL));

    cout << "Generating " << NUMBERS << " random numbers..." << endl;

    for (int i = 0; i < NUMBERS; i++) {
        random_values[i] = rand() % 100;
    }

    cout << "Number generation completed." << endl;

    vector<thread> threads;

    cout << "Starting " << NUM_THREADS << " threads..." << endl;

    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(calculate_sum, i));
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }


    long long total_sum = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += partial_sums[i];
    }

    double average = (double)total_sum / NUMBERS;

    cout << "Average: " << average << endl;

    return 0;
}
