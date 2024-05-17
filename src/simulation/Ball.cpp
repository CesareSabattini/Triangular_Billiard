
#include "Ball.hpp"

template <typename T> Ball<T>::Ball() {}

template <typename T>
Ball<T>::Ball(T p_x, T p_y, T p_theta) : pos({p_x, p_y}), theta(p_theta) {
    if (p_x < 0) {
        throw std::invalid_argument(
            "Ball: x must be greater than or equal to 0");
    }
    if (p_theta >= -M_PI / 2 && p_theta <= M_PI / 2) {
        theta = p_theta;
    } else {
        throw std::invalid_argument(
            "Ball: theta must be between -half pi and half pi");
    }
}

template <typename T>
Ball<T>::Ball(const std::array<T, 2> &p_pos, const T p_theta)
    : pos(p_pos), theta(p_theta) {
    if (p_theta < -M_PI / 2 || p_theta > M_PI / 2)
        throw std::invalid_argument(
            "Ball: theta must be between -half pi and half pi");
    if (p_pos[0] < 0)
        throw std::invalid_argument(
            "Ball: x must be greater than or equal to 0");
}

template <typename T>
Ball<T>::Ball(const Ball &p_ball) : pos(p_ball.pos), theta(p_ball.theta) {
    std::cout << "Ball copied." << std::endl;
}

template <typename T> Ball<T> &Ball<T>::operator=(const Ball &p_ball) {
    pos = p_ball.pos;
    theta = p_ball.theta;
    std::cout << "Ball copied." << std::endl;
    return *this;
}

template <typename T>
Ball<T>::Ball(Ball &&p_ball) : pos(p_ball.pos), theta(p_ball.theta) {
    std::cout << "Ball moved." << std::endl;
}

template <typename T> Ball<T> &Ball<T>::operator=(Ball &&p_ball) {
    pos = p_ball.pos;
    theta = p_ball.theta;
    std::cout << "Ball moved." << std::endl;
    return *this;
}

template <typename T> Ball<T>::~Ball() {}

template <typename T> std::array<T, 2> &Ball<T>::getPos() { return pos; }

template <typename T> void Ball<T>::setPos(const std::array<T, 2> &p_pos) {
    if (p_pos[0] >= 0) {
        pos = p_pos;
    } else {
        throw std::invalid_argument(
            "Ball: x must be greater than or equal to 0");
    }
}

template <typename T> void Ball<T>::setTheta(double p_theta) {
    if (p_theta >= -M_PI / 2 && p_theta <= M_PI / 2) {
        theta = p_theta;
    } else {
        throw std::invalid_argument(
            "Ball: theta must be between -half pi and half pi");
    }
}

template <typename T> double Ball<T>::getTheta() const { return theta; }

template class Ball<int>;
template class Ball<float>;
template class Ball<double>;