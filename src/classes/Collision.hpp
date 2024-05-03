#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <type_traits>
#include <stdexcept>
#include <iostream>
#include<array>

template <typename T>
class Collision
{
public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    Collision(
        T p_x,
        T p_y,
        T p_time
    );
    ~Collision();
    std::array<T,2>& getPos() const;
    T getTime() const;

private:
std::array<T,2> pos;
T time;
};


#endif // COLLISION_HPP