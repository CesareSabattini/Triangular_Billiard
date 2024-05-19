#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "ball.hpp"
#include "collision.hpp"
#include "pool.hpp"
#include <mutex>
#include <type_traits>
#include <vector>

template <typename T> class System {
  public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    System();
    System(const T p_theta, const T p_y, const T p_l, const T p_r1,
           const T p_r2);
    System(const Ball<T> &p_ball, const Pool<T> &p_pool);
    System(const System &p_system);
    System &operator=(const System &p_system);
    System(System &&p_system);
    System &operator=(System &&p_system);
    ~System();

    Ball<T> &getBall();
    Pool<T> &getPool();
    std::vector<Collision<T>> &getCollisions();
    void computeNextCollision();
    T computeOutputY();
    void throwTheBall();
    virtual void simulate();
    void updateParams(const T p_theta, const T p_y, const T p_l, const T p_r1,
                      T p_r2);
    void updateParams(const std::array<T, 2> &inputCoordinates);
    void reset();

  protected:
    Ball<T> ball;
    Pool<T> pool;
    std::vector<Collision<T>> collisions;
};

#endif // SYSTEM_HPP