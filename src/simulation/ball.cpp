
#include "ball.hpp"

template <typename T> simulation::components::Ball<T>::Ball() {}

template <typename T>
simulation::components::Ball<T>::Ball(const T p_x, const T p_y, const T p_theta)
    : pos({p_x, p_y}), theta(p_theta) {
  if (p_x < 0) {
    throw std::invalid_argument("Ball: x must be greater than or equal to 0");
  }
  if (p_theta >= -M_PI / 2 && p_theta <= M_PI / 2) {
    theta = p_theta;
  } else {
    throw std::invalid_argument(
        "Ball: theta must be between -half pi and half pi");
  }
}

template <typename T>
simulation::components::Ball<T>::Ball(const std::array<T, 2> &p_pos,
                                      const T p_theta)
    : pos(p_pos), theta(p_theta) {
  if (p_theta < -M_PI / 2 || p_theta > M_PI / 2)
    throw std::invalid_argument(
        "Ball: theta must be between -half pi and half pi");
  if (p_pos[0] < 0)
    throw std::invalid_argument("Ball: x must be greater than or equal to 0");
}

template <typename T>
simulation::components::Ball<T>::Ball(const Ball &p_ball)
    : pos(p_ball.pos), theta(p_ball.theta) {
  std::cout << "Ball copied." << std::endl;
}

template <typename T>
simulation::components::Ball<T> &
simulation::components::Ball<T>::operator=(const Ball &p_ball) {
  pos = p_ball.pos;
  theta = p_ball.theta;
  std::cout << "Ball copied." << std::endl;
  return *this;
}

template <typename T>
simulation::components::Ball<T>::Ball(const Ball &&p_ball)
    : pos(p_ball.pos), theta(p_ball.theta) {
  std::cout << "Ball moved." << std::endl;
}

template <typename T>
simulation::components::Ball<T> &
simulation::components::Ball<T>::operator=(const Ball &&p_ball) {
  pos = p_ball.pos;
  theta = p_ball.theta;
  std::cout << "Ball moved." << std::endl;
  return *this;
}

template <typename T> simulation::components::Ball<T>::~Ball() {}

template <typename T>
const std::array<T, 2> &simulation::components::Ball<T>::getPos() const {
  return pos;
}

template <typename T>
void simulation::components::Ball<T>::setPos(const std::array<T, 2> &p_pos) {
  if (p_pos[0] >= 0) {
    pos = p_pos;
  } else {
    throw std::invalid_argument("Ball: x must be greater than or equal to 0");
  }
}

template <typename T>
void simulation::components::Ball<T>::setTheta(const T p_theta) {
  if (p_theta >= -M_PI / 2 && p_theta <= M_PI / 2) {
    theta = p_theta;
  } else {
    throw std::invalid_argument(
        "Ball: theta must be between -half pi and half pi");
  }
}

template <typename T>
const T &simulation::components::Ball<T>::getTheta() const {
  return theta;
}

template class simulation::components::Ball<float>;
template class simulation::components::Ball<double>;