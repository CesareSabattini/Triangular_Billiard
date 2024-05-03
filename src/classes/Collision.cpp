#include"Collision.hpp"

template <typename T>

Collision<T>::Collision(T p_x, T p_y, T p_time)
: pos({p_x, p_y}), time(p_time) {
    p_x>=0 ? std::cout << "Collision created at position: " << p_x << ", " << p_y << std::endl : throw std::invalid_argument("x must be greater than or equal to 0");
    p_time>=0 ? std::cout << "Collision created at time: " << p_time << std::endl : throw std::invalid_argument("time must be greater than or equal to 0");
}

template <typename T>
Collision<T>::~Collision() {
    std::cout << "Collision destroyed." << std::endl;
}

template <typename T>
std::array<T,2>& Collision<T>::getPos() const {
    return pos;
}

template <typename T>

T Collision<T>::getTime() const {
    return time;
}



