#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../utils/concept.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace simulation::components {

template <typename T>
requires DoubleOrFloat<T>
class Collision {
  public:
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

} // namespace simulation::components

#endif // COLLISION_HPP