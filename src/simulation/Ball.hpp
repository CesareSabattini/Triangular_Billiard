
#ifndef BALL_HPP
#define BALL_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T> class Ball {

    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

  public:
    Ball();
    Ball(T p_x, T p_y, T p_vx, T p_vy);
    Ball(const std::array<T, 2> &p_pos, const std::array<T, 2> &p_vel);
    Ball(T p_y, T p_theta, T p_vx);

    Ball(const Ball &p_ball);
    Ball &operator=(const Ball &p_ball);
    Ball(Ball &&p_ball);
    Ball &operator=(Ball &&p_ball);

    ~Ball();
    std::array<T, 2> &getPos();
    std::array<T, 2> &getVel();
    void setPos(const std::array<T, 2> &p_pos);
    void setVel(const std::array<T, 2> &p_vel);

  private:
    std::array<T, 2> pos;
    std::array<T, 2> vel;
};

#endif // BALL_HPP