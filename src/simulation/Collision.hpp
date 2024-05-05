#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <array>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T> class Collision {
  public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    Collision(T p_x, T p_y, T p_vx, T p_vy, T p_time);

    Collision(T p_x, T p_y, T p_time);
    ~Collision();
    std::array<T, 2> getPos() const;
    std::array<T, 2> &getVel();
    void setVel(const std::array<T, 2> &p_vel);
    T getTime() const;

  private:
    std::array<T, 2> pos;
    std::array<T, 2> vel;
    T time;
};

#endif // COLLISION_HPP