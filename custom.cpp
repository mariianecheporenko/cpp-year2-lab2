#include "custom.h"
#include "generate.h"
#include "measure.h"
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

using namespace std;

// Parallel none_of that divides work among K threads

template <typename Iterator, typename Predicate>
bool custom(Iterator first, Iterator last, Predicate pred, size_t num_threads) {
    auto length = distance(first, last);
    if (length == 0) return true;

    size_t block_size = length / num_threads;

    vector<thread> threads(num_threads);
    vector<bool> results(num_threads, true);

    Iterator block_start = first;
    for (size_t i = 0; i < num_threads; ++i) {
        Iterator block_end = block_start;
        if (i == num_threads - 1) {
            block_end = last;
        } else {
            advance(block_end, block_size);
        }

        // Each thread checks its chunk with std::none_of

        threads[i] = thread([i, block_start, block_end, pred, &results]() {
            results[i] = none_of(block_start, block_end, pred);
        });

        block_start = block_end;
    }

    for (auto &t : threads) {
        t.join();
    }

    // Is true only if ALL chunks had no matches
    return all_of(results.begin(), results.end(), [](bool val) { return val; });
}

// Measures performance with different thread counts K
void measure_custom() {
    cout << "\n=== Custom none_of implementation study ===" << endl;

    vector<size_t> sizes = {1000000, 5000000, 10000000};
    vector<int> test_threads;

    unsigned int hw_threads = thread::hardware_concurrency();
    cout << "Hardware threads available: " << hw_threads << endl;

    for (size_t i = 1; i <= 2 * hw_threads; ++i) {
        test_threads.push_back(i);
    }

    for (auto size : sizes) {
        cout << "\n--- Testing with vector size: " << size << " ---" << endl;
        auto data = randomVector(size, 1, 100);

        auto pred = [](int x) { return x < 0; }; //worst case, always false

        cout << "K (threads) | Time (ms)" << endl;
        cout << "--------|----------" << endl;

        double best_time = numeric_limits<double>::max();
        size_t best_threads = 1;

        for (auto num_threads : test_threads) {
            auto test_data = data;

            timeit([&test_data, pred, num_threads]() {
                custom(test_data.begin(), test_data.end(), pred, num_threads);
            }, 3);

            auto start = chrono::high_resolution_clock::now();
            custom(test_data.begin(), test_data.end(), pred, num_threads);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;

            cout << num_threads << "       | " << duration << " ms" << endl;

            if (duration < best_time) {
                best_time = duration;
                best_threads = num_threads;
            }
        }

        cout << "Best performance with K = " << best_threads << " (" << best_time << " ms)" << endl;
        cout << "Processor hardware threads = " << hw_threads << endl;
        cout << "K / hw_threads ratio = " << static_cast<double>(best_threads) / hw_threads << endl;    }
}