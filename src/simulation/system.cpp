
#include "system.hpp"

template <typename T> System<T>::System() : ball(), pool() {}

template <typename T>
System<T>::System(T p_theta, T p_y, T p_l, T p_r1, T p_r2)
    : ball(0, p_y, p_theta), pool(p_l, p_r1, p_r2) {
    if (p_y < -p_r1 || p_y > p_r1)
        throw std::invalid_argument("y must be between -R1 and R1");
    else {

        collisions.push_back(Collision<T>(0, p_y, p_theta));
    }
}

template <typename T>
System<T>::System(const Ball<T> &p_ball, const Pool<T> &p_pool)
    : ball(p_ball), pool(p_pool) {}

template <typename T>
System<T>::System(const System &p_system)
    : ball(p_system.ball), pool(p_system.pool) {}

template <typename T> System<T> &System<T>::operator=(const System &p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    return *this;
}

template <typename T>
System<T>::System(System &&p_system)
    : ball(p_system.ball), pool(p_system.pool) {}

template <typename T> System<T> &System<T>::operator=(System &&p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    return *this;
}

template <typename T> System<T>::~System() {}

template <typename T> Ball<T> &System<T>::getBall() { return ball; }

template <typename T> Pool<T> &System<T>::getPool() { return pool; }

template <typename T> std::vector<Collision<T>> &System<T>::getCollisions() {
    return collisions;
}

template <typename T> void System<T>::throwTheBall() {

    const T alpha =
        static_cast<T>(std::atan((pool.getR1() - pool.getR2()) / pool.getL()));

    if (std::abs(ball.getPos()[1]) >= pool.getR2() &&
        std::abs(ball.getPos()[1]) <= pool.getR1() && ball.getPos()[1] >= 0 &&
        std::abs(ball.getTheta()) <=
            std::atan((std::abs(ball.getPos()[1]) - pool.getR2()) /
                      pool.getL()) &&
        ball.getTheta() < 0) {

        T newTheta = ball.getTheta() + 2 * alpha;
        T newX = static_cast<T>((-ball.getPos()[1] + pool.getR1()) /
                                (std::tan(ball.getTheta()) +
                                 (pool.getR1() - pool.getR2()) / pool.getL()));
        T newY =
            pool.getR1() - ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        if (newTheta > M_PI / 2 || newTheta < -M_PI / 2)
            throw std::invalid_argument(
                "the ball can't escape due to skewness!");
        else {
            collisions.push_back(Collision<T>(newX, newY, newTheta));
            ball.setPos({newX, newY});
        }

    } else if (std::abs(ball.getPos()[1]) >= pool.getR2() &&
               std::abs(ball.getPos()[1]) <= pool.getR1() &&
               ball.getPos()[1] < 0 &&
               std::abs(ball.getTheta()) <
                   std::atan((std::abs(ball.getPos()[1]) - pool.getR2()) /
                             pool.getL()) &&
               ball.getTheta() > 0) {

        T newTheta = ball.getTheta() - 2 * alpha;
        T newX = static_cast<T>((ball.getPos()[1] + pool.getR1()) /
                                (-std::tan(ball.getTheta()) +
                                 (pool.getR1() - pool.getR2()) / pool.getL()));
        T newY = -static_cast<T>(pool.getR1() +
                                 ((pool.getR1() - pool.getR2()) / pool.getL()) *
                                     newX);

        if (newTheta > M_PI / 2 || newTheta < -M_PI / 2)
            throw std::invalid_argument(
                "the ball can't escape due to skewness!");
        else {
            collisions.push_back(Collision<T>(newX, newY, newTheta));
            ball.setPos({newX, newY});
        }
    }
}

template <typename T> void System<T>::computeNextCollision() {

    if (collisions[collisions.size() - 1].getTheta() >= 0) {
        T newTheta = -static_cast<T>(
            (collisions[collisions.size() - 1].getTheta() +
             2 * (std::atan(
                     std::abs((pool.getR2() - pool.getR1()) / pool.getL())))));

        T newX = static_cast<T>(
            (pool.getR1() - collisions[collisions.size() - 1].getPos()[1] +
             std::tan(collisions[collisions.size() - 1].getTheta()) *
                 collisions[collisions.size() - 1].getPos()[0]) /
            (std::tan(collisions[collisions.size() - 1].getTheta()) +
             (pool.getR1() - pool.getR2()) / pool.getL()));

        T newY =
            pool.getR1() - ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        if (newX >= pool.getL()) {
            ball.setPos({pool.getL(), computeOutputY()});
            std::cout << "Simulation ended, with output Y of: "
                      << computeOutputY() << std::endl;
            collisions.push_back(
                Collision<T>(pool.getL(), computeOutputY(),
                             collisions[collisions.size() - 1].getTheta()));

        } else {
            collisions.push_back(Collision<T>(newX, newY, newTheta));
            ball.setPos({newX, newY});
        }
    } else if (collisions[collisions.size() - 1].getTheta() < 0) {
        T newTheta = -static_cast<T>(
            (collisions[collisions.size() - 1].getTheta() -
             2 * (std::atan(
                     std::abs((pool.getR2() - pool.getR1()) / pool.getL())))));

        T newX = static_cast<T>(
            (pool.getR1() -
             std::tan(collisions[collisions.size() - 1].getTheta()) *
                 collisions[collisions.size() - 1].getPos()[0] +
             collisions[collisions.size() - 1].getPos()[1]) /
            (-std::tan(collisions[collisions.size() - 1].getTheta()) +
             (pool.getR1() - pool.getR2()) / pool.getL()));

        T newY = -pool.getR1() +
                 ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        if (newX >= pool.getL()) {
            ball.setPos({pool.getL(), computeOutputY()});
            collisions.push_back(
                Collision<T>(pool.getL(), computeOutputY(),
                             collisions[collisions.size() - 1].getTheta()));

            std::cout << "Simulation ended, with output Y of: "
                      << computeOutputY() << std::endl;

        } else {
            collisions.push_back(Collision<T>(newX, newY, newTheta));
            ball.setPos({newX, newY});
        }
    }
}

template <typename T> T System<T>::computeOutputY() {
    T y = static_cast<T>(
        collisions[collisions.size() - 1].getPos()[1] +
        std::tan(collisions[collisions.size() - 1].getTheta()) *
            (pool.getL() - collisions[collisions.size() - 1].getPos()[0]));
    return y;
}

template <typename T> void System<T>::simulate() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "SIMULATION STARTED" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Initial ball position: " << ball.getPos()[0] << ", "
              << ball.getPos()[1] << std::endl;
    std::cout << "Pool parameters: "
              << " L= " << pool.getL() << ", "
              << "R1= " << pool.getR1() << ", "
              << "R2= " << pool.getR2() << std::endl;
    std::cout << "--------------------------------" << std::endl;

    try {
        throwTheBall();
    } catch (std::invalid_argument &e) {
        // cas di grandi inclinazione delle pareti e traiettorie non radenti
        std::cout << "the ball can't escape due to skewness!" << std::endl;
        return;
    }
    if (ball.getPos()[0] >= pool.getL()) {
        std::cout << "Simulation ended, with output Y of: " << ball.getPos()[1]
                  << std::endl;
        return;
    }
    if (ball.getPos()[0] < pool.getL()) {

        while (ball.getPos()[0] < pool.getL()) {

            try {

                computeNextCollision();
            } catch (std::invalid_argument &e) {
                std::cout << "the ball can't escape!" << std::endl;
                break;
            } catch (std::exception &e) {
                std::cout << "the ball can't escape!" << std::endl;
                break;
            }

            if (collisions[collisions.size() - 1].getPos()[0] >= pool.getL()) {
                std::cout << "Simulation ended, with output Y of: "
                          << computeOutputY() << std::endl;
                break;
            } else {
                std::cout << "COLLISION NUMBER: " << collisions.size()
                          << std::endl;
                std::cout << "Ball position: " << ball.getPos()[0] << ", "
                          << ball.getPos()[1] << std::endl;
                std::cout << "Ball angle: "
                          << collisions[collisions.size() - 1].getTheta()
                          << std::endl;
                std::cout << "--------------------------------" << std::endl;
            }
        }

    } else {
        std::cout << "Simulation ended, with output Y of: " << ball.getPos()[1]
                  << std::endl;
    }
}

template <typename T>
void System<T>::updateParams(T p_theta, T p_y, T p_l, T p_r1, T p_r2) {
    reset();
    ball.setPos(std::array<T, 2>({0, p_y}));
    ball.setTheta(p_theta);
    pool.setL(p_l);
    pool.setRs(p_r1, p_r2);
    collisions.clear();
    collisions.push_back(Collision<T>(0, p_y, p_theta));
}

template <typename T> void System<T>::updateParams(std::array<T, 2> inputY_T) {
    reset();
    ball.setPos({0, inputY_T[0]});
    ball.setTheta(inputY_T[1]);
    collisions.clear();
    collisions.push_back(Collision<T>(0, inputY_T[0], ball.getTheta()));
}

template <typename T> void System<T>::reset() {
    ball.setPos({0, 0});
    ball.setTheta(0);
    collisions.clear();
    collisions.push_back(Collision<T>(0, 0, 0));
}

template class System<int>;
template class System<float>;
template class System<double>;