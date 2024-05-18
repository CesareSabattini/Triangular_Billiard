#include "mockSystem.hpp"

template <typename T> void MockSystem<T>::simulate() {

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

template class MockSystem<double>;
template class MockSystem<float>;
template class MockSystem<int>;
