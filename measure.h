#ifndef MEASURE_H
#define MEASURE_H

#include <iostream>
#include <chrono>
#include <format>
using namespace std;


template <class F>
void timeit(F &&f, int repeat = 1)
{
    using namespace std::chrono;
    auto start = system_clock::now();

    while (repeat--)
        f();

    auto end = system_clock::now();
    auto duration = end - start;

    if (duration > 100000ns)
        cout << std::format("{:%S}", duration) << " sec" << std::endl;
    else
        cout << duration << " ns" << std::endl;
}




#endif