
#include "Ball.hpp"

template <typename T> Ball<T>::Ball() {
    std::cout << "Ball created." << std::endl;
}

template <typename T>
Ball<T>::Ball(T p_x, T p_y, T p_vx, T p_vy)
    : pos({p_x, p_y}), vel({p_vx, p_vy}) {
    p_x >= 0
        ? std::cout << "Ball created at position: " << p_x << ", " << p_y
                    << std::endl
        : throw std::invalid_argument("x must be greater than or equal to 0");
    p_vx >= 0
        ? std::cout << "Ball created with velocity: " << p_vx << ", " << p_vy
                    << std::endl
        : throw std::invalid_argument("vx must be greater than or equal to 0");
}

template <typename T>
Ball<T>::Ball(const std::array<T, 2> &p_pos, const std::array<T, 2> &p_vel)
    : pos(p_pos), vel(p_vel) {
    p_pos[0] >= 0
        ? std::cout << "Ball created at position: " << p_pos[0] << ", "
                    << p_pos[1] << std::endl
        : throw std::invalid_argument("x must be greater than or equal to 0");
    p_vel[0] >= 0
        ? std::cout << "Ball created with velocity: " << p_vel[0] << ", "
                    << p_vel[1] << std::endl
        : throw std::invalid_argument("vx must be greater than or equal to 0");
}

template <typename T>
Ball<T>::Ball(const Ball &p_ball) : pos(p_ball.pos), vel(p_ball.vel) {
    std::cout << "Ball copied." << std::endl;
}

template <typename T> Ball<T> &Ball<T>::operator=(const Ball &p_ball) {
    pos = p_ball.pos;
    vel = p_ball.vel;
    std::cout << "Ball copied." << std::endl;
    return *this;
}

template <typename T>
Ball<T>::Ball(Ball &&p_ball) : pos(p_ball.pos), vel(p_ball.vel) {
    std::cout << "Ball moved." << std::endl;
}

template <typename T> Ball<T> &Ball<T>::operator=(Ball &&p_ball) {
    pos = p_ball.pos;
    vel = p_ball.vel;
    std::cout << "Ball moved." << std::endl;
    return *this;
}

template <typename T>
Ball<T>::Ball(T p_y, T p_theta, T p_vx)
    : pos({p_theta, p_y}), vel({p_vx, static_cast<T>((p_theta)) * p_vx}) {
    p_theta >= 0 && p_theta <= M_PI
        ? std::cout << "Ball created at position: " << p_theta << ", " << p_y
                    << std::endl
        : throw std::invalid_argument("x must be greater than or equal to 0");
    p_vx >= 0
        ? std::cout << "Ball created with velocity: " << p_vx << ", " << 0
                    << std::endl
        : throw std::invalid_argument("vx must be greater than or equal to 0");
}

template <typename T> Ball<T>::~Ball() {
    std::cout << "Ball destroyed." << std::endl;
}

template <typename T> std::array<T, 2> &Ball<T>::getPos() { return pos; }

template <typename T> std::array<T, 2> &Ball<T>::getVel() { return vel; }

template <typename T> void Ball<T>::setPos(const std::array<T, 2> &p_pos) {
    if (p_pos[0] >= 0) {
        pos = p_pos;
    } else {
        throw std::invalid_argument("x must be greater than or equal to 0");
    }
}

template <typename T> void Ball<T>::setVel(const std::array<T, 2> &p_vel) {
    if (p_vel[0] >= 0) {
        vel = p_vel;
    } else {
        throw std::invalid_argument("vx must be greater than or equal to 0");
    }
}

template class Ball<int>;
template class Ball<float>;
template class Ball<double>;