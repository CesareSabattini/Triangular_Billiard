#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <type_traits>

template <typename T>
concept DoubleOrFloat = std::is_same_v<T, double> || std::is_same_v<T, float>;

#endif
