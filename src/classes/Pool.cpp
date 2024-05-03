#include "Pool.hpp"


template <typename T>
Pool<T>::Pool(T p_l, T p_r1, T p_r2)
: l(p_l), r1(p_r1), r2(p_r2) {
    if (l <= 0) {
        throw std::invalid_argument("l must be greater than 0");
    }
    if (r1 <= 0) {
        throw std::invalid_argument("r1 must be greater than 0");
    }
    if (r2 <= 0) {
        throw std::invalid_argument("r2 must be greater than 0");
    }
    if (r2 >= r1) {
        throw std::invalid_argument("r2 must be less than r1");
    }
    std::cout << "Pool created with dimensions: " << l << ", " << r1 << ", " << r2 << std::endl;
}

template <typename T>
Pool<T>::~Pool() {
    std::cout << "Pool destroyed." << std::endl;
}

template <typename T>
const T& Pool<T>::getL() const {
    return l;
}

template class Pool<int>;
template class Pool<float>;
template class Pool<double>;
