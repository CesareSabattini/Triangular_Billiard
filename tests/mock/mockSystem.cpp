#include "mockSystem.hpp"

template <typename T>
mock::MockSystem<T>::MockSystem() : simulation::System<T>() {}

template <typename T>
mock::MockSystem<T>::MockSystem(const T p_theta, const T p_y, const T p_l,
                                const T p_r1, const T p_r2)
    : simulation::System<T>(p_theta, p_y, p_l, p_r1, p_r2) {}

template <typename T> void mock::MockSystem<T>::simulate() {

  try {
    throwTheBall();
  } catch (std::invalid_argument &e) {
    return;
  }
  if (ball.getPos()[0] >= pool.getL()) {

    return;
  }
  if (ball.getPos()[0] < pool.getL()) {

    while (ball.getPos()[0] < pool.getL()) {

      try {

        computeNextCollision();
      } catch (std::invalid_argument &e) {

        break;
      } catch (std::exception &e) {

        break;
      }

      if (collisions[collisions.size() - 1].getPos()[0] >= pool.getL()) {

        break;
      }
    }

  } else {

    return;
  }
}

template class mock::MockSystem<double>;
template class mock::MockSystem<float>;
