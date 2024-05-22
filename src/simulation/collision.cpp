#include "collision.hpp"

template <typename T>
simulation::components::Collision<T>::Collision(const T p_x, const T p_y,
                                                const T p_theta)
    : pos({p_x, p_y}), theta(p_theta) {
    if (p_theta < -M_PI / 2 || p_theta > M_PI / 2) {
        throw std::invalid_argument(
            "theta must be between -half pi and half pi");

    } else if (p_x < 0) {
        throw std::invalid_argument("x must be greater than or equal to 0");
    }
}

template <typename T> simulation::components::Collision<T>::~Collision() {}

template <typename T>
const std::array<T, 2> &simulation::components::Collision<T>::getPos() const {
    return pos;
}

template <typename T>
const T &simulation::components::Collision<T>::getTheta() const {
    return theta;
}

template <typename T>
void simulation::components::Collision<T>::setTheta(const T p_theta) {
    theta = p_theta;
}

template class simulation::components::Collision<int>;
template class simulation::components::Collision<float>;
template class simulation::components::Collision<double>;
