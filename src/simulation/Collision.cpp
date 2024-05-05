#include "Collision.hpp"

template <typename T>

Collision<T>::Collision(T p_x, T p_y, T p_vx, T p_vy, T p_time)
    : pos({p_x, p_y}), vel({p_vx, p_vy}), time(p_time) {
    p_x >= 0 ? std::cout << "Collision created at position: " << p_x << ", "
                         << p_y << std::endl
             : throw std::invalid_argument(
                   "Collision: x must be greater than or equal to 0");
    p_vx >= 0 ? std::cout << "Collision created with velocity: " << p_vx << ", "
                          << p_vy << std::endl
              : throw std::invalid_argument(
                    "Collision: vx must be greater than or equal to 0");
    p_time >= 0
        ? std::cout << "Collision created at time: " << p_time << std::endl
        : throw std::invalid_argument(
              "time must be greater than or equal to 0");
}

template <typename T>
Collision<T>::Collision(T p_x, T p_y, T p_time)
    : pos({p_x, p_y}), time(p_time) {
    p_x >= 0 ? std::cout << "Collision created at position: " << p_x << ", "
                         << p_y << std::endl
             : throw std::invalid_argument(
                   "Collision: x must be greater than or equal to 0");
    p_time >= 0
        ? std::cout << "Collision created at time: " << p_time << std::endl
        : throw std::invalid_argument(
              "time must be greater than or equal to 0");
}

template <typename T> Collision<T>::~Collision() {
    std::cout << "Collision destroyed." << std::endl;
}

template <typename T> std::array<T, 2> Collision<T>::getPos() const {
    return pos;
}

template <typename T> std::array<T, 2> &Collision<T>::getVel() { return vel; }

template <typename T> void Collision<T>::setVel(const std::array<T, 2> &p_vel) {
    vel = p_vel;
}

template <typename T>

T Collision<T>::getTime() const {
    return time;
}

template class Collision<int>;
template class Collision<float>;
template class Collision<double>;
