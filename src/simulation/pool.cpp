#include "pool.hpp"

template <typename T> Pool<T>::Pool() : l(0), r1(0), r2(0) {}
template <typename T>
Pool<T>::Pool(T p_l, T p_r1, T p_r2) : l(p_l), r1(p_r1), r2(p_r2) {
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
}

template <typename T>
Pool<T>::Pool(const Pool &p_pool) : l(p_pool.l), r1(p_pool.r1), r2(p_pool.r2) {}

template <typename T> Pool<T> &Pool<T>::operator=(const Pool &p_pool) {
    l = p_pool.l;
    r1 = p_pool.r1;
    r2 = p_pool.r2;
    return *this;
}

template <typename T>
Pool<T>::Pool(Pool &&p_pool) : l(p_pool.l), r1(p_pool.r1), r2(p_pool.r2) {}

template <typename T> Pool<T> &Pool<T>::operator=(Pool &&p_pool) {
    l = p_pool.l;
    r1 = p_pool.r1;
    r2 = p_pool.r2;
    return *this;
}

template <typename T> Pool<T>::~Pool() {}

template <typename T> const T &Pool<T>::getL() const { return l; }

template <typename T> const T &Pool<T>::getR1() const { return r1; }

template <typename T> const T &Pool<T>::getR2() const { return r2; }

template <typename T> void Pool<T>::setL(const T &p_l) {
    if (p_l <= 0) {
        throw std::invalid_argument("l must be greater than 0");
    }
    l = p_l;
}

template <typename T> void Pool<T>::setRs(const T &p_r1, const T &p_r2) {
    if (p_r1 <= 0) {
        throw std::invalid_argument("r1 must be greater than 0");
    }
    if (p_r2 <= 0) {
        throw std::invalid_argument("r2 must be greater than 0");
    }
    if (p_r2 >= p_r1) {
        throw std::invalid_argument("r2 must be less than r1");
    }
    r1 = p_r1;
    r2 = p_r2;
}

template class Pool<int>;
template class Pool<float>;
template class Pool<double>;
