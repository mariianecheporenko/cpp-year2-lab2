#include <iostream>
#include <vector>
#include <algorithm>
#include "generate.h"
#include "measure.h"

using namespace std;

void standard() {
    cout << "\n=== Standard std::none_of (no policy) ===" << endl;
    
    vector<size_t> sizes = {1000000, 5000000, 10000000};
    
    for (auto size : sizes) {
        cout << "\nTesting with vector size: " << size << endl;
        auto data = randomVector(size, 1, 100);
        
        auto pred = [](int x) { return x < 0; };
        
        cout << "Time: ";
        timeit([&data, pred]() {
            none_of(data.begin(), data.end(), pred);
        }, 5);
    }
}