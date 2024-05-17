
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
    Ball(T p_x, T p_y, T theta);
    Ball(const std::array<T, 2> &p_pos, T theta);

    Ball(const Ball &p_ball);
    Ball &operator=(const Ball &p_ball);
    Ball(Ball &&p_ball);
    Ball &operator=(Ball &&p_ball);

    ~Ball();
    std::array<T, 2> &getPos();
    T getTheta() const;
    void setPos(const std::array<T, 2> &p_pos);
    void setTheta(T p_theta);

  private:
    std::array<T, 2> pos;
    T theta;
};

#endif // BALL_HPP