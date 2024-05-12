#include "Collision.hpp"

template <typename T>

Collision<T>::Collision(T p_x, T p_y, T p_theta, T p_time)
    : pos({p_x, p_y}), theta(p_theta), time(p_time) {
    p_x >= 0
        ?: throw std::invalid_argument(
               "Collision: x must be greater than or equal to 0");

    p_time >= 0
        ?: throw std::invalid_argument(
               "time must be greater than or equal to 0");
}

template <typename T>
Collision<T>::Collision(T p_x, T p_y, T p_theta)
    : pos({p_x, p_y}), theta(p_theta) {
    if (p_theta < -M_PI / 2 || p_theta > M_PI / 2) {
        throw std::invalid_argument(
            "theta must be between -half pi and half pi");

    } else if (p_x < 0) {
        throw std::invalid_argument("x must be greater than or equal to 0");
    }
}

template <typename T> Collision<T>::~Collision() {}

template <typename T> std::array<T, 2> Collision<T>::getPos() const {
    return pos;
}

template <typename T> double Collision<T>::getTheta() const { return theta; }

template <typename T> void Collision<T>::setTheta(double p_theta) {
    theta = p_theta;
}

template <typename T>

T Collision<T>::getTime() const {
    return time;
}

template <typename T> void Collision<T>::setTime(const T &p_time) {
    time = p_time;
}

template class Collision<int>;
template class Collision<float>;
template class Collision<double>;
