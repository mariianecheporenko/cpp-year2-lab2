#ifndef CUSTOM_NONE_OF_H
#define CUSTOM_NONE_OF_H

#include <vector>
#include <functional>
#include <thread>
#include <algorithm>

template <typename Iterator, typename Predicate>
bool custom(Iterator first, Iterator last, Predicate pred, size_t num_threads);

void measure_custom();

#endif