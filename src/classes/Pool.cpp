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
Pool<T>::Pool(const Pool& p_pool)
: l(p_pool.l), r1(p_pool.r1), r2(p_pool.r2) {
    std::cout << "Pool copied." << std::endl;
}

template <typename T>
Pool<T>& Pool<T>::operator=(const Pool& p_pool) {
    l = p_pool.l;
    r1 = p_pool.r1;
    r2 = p_pool.r2;
    std::cout << "Pool copied." << std::endl;
    return *this;
}

template <typename T>
Pool<T>::Pool(Pool&& p_pool)
: l(p_pool.l), r1(p_pool.r1), r2(p_pool.r2) {
    std::cout << "Pool moved." << std::endl;
}

template <typename T>
Pool<T>& Pool<T>::operator=(Pool&& p_pool) {
    l = p_pool.l;
    r1 = p_pool.r1;
    r2 = p_pool.r2;
    std::cout << "Pool moved." << std::endl;
    return *this;
}


template <typename T>
Pool<T>::~Pool() {
    std::cout << "Pool destroyed." << std::endl;
}

template <typename T>
const T& Pool<T>::getL() const {
    return l;
}

template <typename T>
const T& Pool<T>::getR1() const {
    return r1;
}

template <typename T>
const T& Pool<T>::getR2() const {
    return r2;
}


template class Pool<int>;
template class Pool<float>;
template class Pool<double>;
