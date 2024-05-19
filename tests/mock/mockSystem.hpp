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

    MockSystem();
    MockSystem(const T p_theta, const T p_y, const T p_l, const T p_r1,
               const T p_r2);

    void simulate() override;
};

#endif // MOCK_SYSTEM_HPP