#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "../utils/concept.hpp"
#include "ball.hpp"
#include "collision.hpp"
#include "pool.hpp"
#include <mutex>
#include <type_traits>
#include <vector>

namespace simulation {
template <typename T>
requires DoubleOrFloat<T>

class System {
  public:
    System();
    System(const T p_theta, const T p_y, const T p_l, const T p_r1,
           const T p_r2);
    System(const components::Ball<T> &p_ball,
           const components::Pool<T> &p_pool);
    System(const System &p_system);
    System &operator=(const System &p_system);
    System(System &&p_system);
    System &operator=(System &&p_system);
    ~System();

    components::Ball<T> &getBall();
    components::Pool<T> &getPool();
    std::vector<components::Collision<T>> &getCollisions();
    void computeNextCollision();
    T computeOutputY();
    void throwTheBall();
    virtual void simulate();
    void updateParams(const T p_theta, const T p_y, const T p_l, const T p_r1,
                      T p_r2);
    void updateParams(const std::array<T, 2> &inputCoordinates);
    void reset();

  protected:
    components::Ball<T> ball;
    components::Pool<T> pool;
    std::vector<components::Collision<T>> collisions;
};

} // namespace simulation
#endif // SYSTEM_HPP