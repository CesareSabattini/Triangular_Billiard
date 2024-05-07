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
    Collision(T p_x, T p_y, T theta, T p_time);
    Collision() = default;
    Collision(T p_x, T p_y, T p_theta);
    ~Collision();
    std::array<T, 2> getPos() const;
    double getTheta() const;
    void setTheta(double p_theta);
    T getTime() const;
    void setTime(const T &p_time);

  private:
    std::array<T, 2> pos;
    /*
    theta rispetto all'asse x
    */
    double theta;
    T time;
};

#endif // COLLISION_HPP