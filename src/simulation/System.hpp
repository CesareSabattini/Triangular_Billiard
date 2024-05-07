#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Ball.hpp"
#include "Collision.hpp"
#include "Pool.hpp"
#include <mutex>
#include <type_traits>
#include <vector>

template <typename T> class System {
  public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    System();
    System(T p_theta, T p_y, T p_l, T p_r1, T p_r2);
    System(const Ball<T> &p_ball, const Pool<T> &p_pool);
    System(const System &p_system);
    System &operator=(const System &p_system);
    System(System &&p_system);
    System &operator=(System &&p_system);
    ~System();

    Ball<T> &getBall();
    Pool<T> &getPool();
    T getTime() const;
    std::vector<Collision<T>> &getCollisions();
    void setTime(const T &p_time);
    void computeNextCollision();
    void computeNextBallVel();
    T computeOutputY();
    void throwTheBall();
    void simulate();
    void updateParams(T p_theta, T p_y, T p_l, T p_r1, T p_r2);
    void reset();

  private:
    Ball<T> ball;
    Pool<T> pool;
    T time;
    std::vector<Collision<T>> collisions;
};

#endif // SYSTEM_HPP