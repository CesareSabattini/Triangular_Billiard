#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T> class Collision {
  public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    Collision() = default;
    Collision(const T p_x, const T p_y, const T p_theta);
    ~Collision();
    const std::array<T, 2> &getPos() const;
    const T &getTheta() const;
    void setTheta(const T p_theta);

  private:
    std::array<T, 2> pos = {0, 0};
    T theta;
};

#endif // COLLISION_HPP