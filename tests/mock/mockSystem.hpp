#ifndef MOCK_SYSTEM_HPP
#define MOCK_SYSTEM_HPP

#include "../src/simulation/system.hpp"

template <typename T> class MockSystem : public System<T> {
  public:
    using System<T>::throwTheBall;
    using System<T>::computeNextCollision;
    using System<T>::computeOutputY;
    using System<T>::collisions;
    using System<T>::ball;
    using System<T>::pool;

    MockSystem() : System<T>() {}
    MockSystem(T p_theta, T p_y, T p_l, T p_r1, T p_r2)
        : System<T>(p_theta, p_y, p_l, p_r1, p_r2) {}

    void simulate() override;
};

#endif // MOCK_SYSTEM_HPP