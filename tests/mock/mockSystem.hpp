#ifndef MOCK_SYSTEM_HPP
#define MOCK_SYSTEM_HPP

#include "../src/simulation/system.hpp"

namespace mock {

template <typename T> class MockSystem : public simulation::System<T> {
  public:
    using simulation::System<T>::throwTheBall;
    using simulation::System<T>::computeNextCollision;
    using simulation::System<T>::computeOutputY;
    using simulation::System<T>::collisions;
    using simulation::System<T>::ball;
    using simulation::System<T>::pool;

    MockSystem();
    MockSystem(const T p_theta, const T p_y, const T p_l, const T p_r1,
               const T p_r2);

    void simulate() override;
};
} // namespace mock

#endif // MOCK_SYSTEM_HPP