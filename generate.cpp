#include "generate.h"
#include <random>
using namespace std;

vector<int> randomVector(size_t size, int min, int max)
{
    vector<int> data(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);

    for (auto &el : data)
        el = dist(gen);

    return data;
}
