#include "collision.hpp"

template <typename T>
Collision<T>::Collision(const T p_x, const T p_y, const T p_theta)
    : pos({p_x, p_y}), theta(p_theta) {
    if (p_theta < -M_PI / 2 || p_theta > M_PI / 2) {
        throw std::invalid_argument(
            "theta must be between -half pi and half pi");

    } else if (p_x < 0) {
        throw std::invalid_argument("x must be greater than or equal to 0");
    }
}

template <typename T> Collision<T>::~Collision() {}

template <typename T> const std::array<T, 2> &Collision<T>::getPos() const {
    return pos;
}

template <typename T> const T &Collision<T>::getTheta() const { return theta; }

template <typename T> void Collision<T>::setTheta(const T p_theta) {
    theta = p_theta;
}

template class Collision<int>;
template class Collision<float>;
template class Collision<double>;
