
#ifndef BALL_HPP
#define BALL_HPP

#include "../utils/concept.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace simulation::components {

template <typename T>
requires DoubleOrFloat<T>

class Ball {

  public:
    Ball();
    Ball(const T p_x, const T p_y, const T theta);
    Ball(const std::array<T, 2> &p_pos, T theta);

    Ball(const Ball &p_ball);
    Ball &operator=(const Ball &p_ball);
    Ball(const Ball &&p_ball);
    Ball &operator=(const Ball &&p_ball);

    ~Ball();
    const std::array<T, 2> &getPos() const;
    const T &getTheta() const;
    void setPos(const std::array<T, 2> &p_pos);
    void setTheta(const T p_theta);

  private:
    std::array<T, 2> pos;
    T theta;
};
} // namespace simulation::components

#endif // BALL_HPP