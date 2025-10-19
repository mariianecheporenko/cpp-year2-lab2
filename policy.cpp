#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include "generate.h"
#include "measure.h"

using namespace std;

void policy() {
    cout << "\n=== std::none_of with execution policies ===" << endl;
    
    vector<size_t> sizes = {1000000, 5000000, 10000000};
    
    for (auto size : sizes) {
        cout << "\nTesting with vector size: " << size << endl;
        auto data = randomVector(size, 1, 100);
        
        auto pred = [](int x) { return x < 0; };
        
        cout << "Sequential: ";
        timeit([&data, pred]() {
            none_of(execution::seq, data.begin(), data.end(), pred);
        }, 5);
        
        cout << "Parallel: ";
        timeit([&data, pred]() {
            none_of(execution::par, data.begin(), data.end(), pred);
        }, 5);
        
        cout << "Unsequenced: ";
        timeit([&data, pred]() {
            none_of(execution::unseq, data.begin(), data.end(), pred);
        }, 5);
        
        cout << "Parallel unsequenced: ";
        timeit([&data, pred]() {
            none_of(execution::par_unseq, data.begin(), data.end(), pred);
        }, 5);
    }
}