
#include "System.hpp"

template <typename T> System<T>::System() : time(0), ball(), pool() {
    std::cout << "System created." << std::endl;
}

template <typename T>
System<T>::System(T p_theta, T p_vx, T p_y, T p_l, T p_r1, T p_r2)
    : pool(p_l, p_r1, p_r2), time(0), ball(p_y, p_theta, p_vx) {
    p_y > -p_r1 &&p_y < p_r1
        ? std::cout << "Ball created at position: " << p_theta << ", " << p_vx
                    << ", " << p_y << std::endl
        : throw std::invalid_argument(
              "y must be greater than -r1 and less than r1");

    std::cout << "System created with ball at position: " << p_theta << ", "
              << p_vx << ", " << p_y << std::endl;
    collisions.push_back(Collision<T>(0, p_y, p_vx, p_vx * tan(p_theta), 0));
}

template <typename T>
System<T>::System(const Ball<T> &p_ball, const Pool<T> &p_pool)
    : ball(p_ball), pool(p_pool), time(0) {
    std::cout << "System created with ball at position: " << ball.getPos()[0]
              << ", " << ball.getPos()[1] << std::endl;
}

template <typename T>
System<T>::System(const System &p_system)
    : ball(p_system.ball), pool(p_system.pool), time(p_system.time) {
    std::cout << "System copied." << std::endl;
}

template <typename T> System<T> &System<T>::operator=(const System &p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    time = p_system.time;
    std::cout << "System copied." << std::endl;
    return *this;
}

template <typename T>
System<T>::System(System &&p_system)
    : ball(p_system.ball), pool(p_system.pool), time(p_system.time) {
    std::cout << "System moved." << std::endl;
}

template <typename T> System<T> &System<T>::operator=(System &&p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    time = p_system.time;
    std::cout << "System moved." << std::endl;
    return *this;
}

template <typename T> System<T>::~System() {
    std::cout << "System destroyed." << std::endl;
}

template <typename T> Ball<T> &System<T>::getBall() { return ball; }

template <typename T> Pool<T> &System<T>::getPool() { return pool; }

template <typename T> T System<T>::getTime() const { return time; }

template <typename T> std::vector<Collision<T>> &System<T>::getCollisions() {
    return collisions;
}

template <typename T> void System<T>::setTime(const T &p_time) {
    if (p_time >= 0) {
        time = p_time;
    } else {
        throw std::invalid_argument("time must be greater than or equal to 0");
    }
}

template <typename T> void System<T>::computeNextCollision() {

    if (ball.getPos()[1] > 0) {
        T collisionX =
            (-ball.getPos()[1] -
             abs(ball.getVel()[1] / ball.getVel()[0]) * ball.getPos()[0] +
             ((pool.getR2() - pool.getR1()) / pool.getL()) * pool.getL() -
             pool.getR2()) /
            (-abs(ball.getVel()[1] / ball.getVel()[0]) +
             (pool.getR2() - pool.getR1()) / pool.getL());

        T collisionY = ((-pool.getR2() + pool.getR1()) / pool.getL()) *
                           (collisionX - pool.getL()) +
                       pool.getR2();

        T collisionTime =
            time + (collisionX - ball.getPos()[0]) / ball.getVel()[0];

        if (collisionX < 0 || collisionX > pool.getL()) {
            collisions.push_back(
                Collision<T>(pool.getL(), computeOutputY(), 0));
            ball.setPos({pool.getL(), computeOutputY()});
        } else {
            collisions.push_back(
                Collision<T>(collisionX, collisionY, collisionTime));
            ball.setPos({collisionX, collisionY});
        }

    } else if (ball.getPos()[1] < 0) {

        T collisionX =
            (-ball.getPos()[1] -
             abs(ball.getVel()[1] / ball.getVel()[0]) * ball.getPos()[0] +
             ((pool.getR2() - pool.getR1()) / pool.getL()) * pool.getL() -
             pool.getR2()) /
            (-abs(ball.getVel()[1] / ball.getVel()[0]) +
             (pool.getR2() - pool.getR1()) / pool.getL());

        T collisionY = ((pool.getR2() - pool.getR1()) / pool.getL()) *
                           (collisionX - pool.getL()) -
                       pool.getR2();

        T collisionTime = (collisionX - ball.getPos()[0]) / ball.getVel()[0];
        if (collisionX < 0 || collisionX > pool.getL()) {
            collisions.push_back(
                Collision<T>(pool.getL(), computeOutputY(), 0));
            ball.setPos({pool.getL(), computeOutputY()});
        } else {
            collisions.push_back(
                Collision<T>(collisionX, collisionY, collisionTime));
            ball.setPos({collisionX, collisionY});
        }

    } else if (ball.getPos()[1] == 0) {
        T collisionX = 0;
        if (ball.getVel()[0] > 0) {
            T collisionX =
                (-ball.getPos()[1] -
                 abs(ball.getVel()[1] / ball.getVel()[0]) * ball.getPos()[0] +
                 ((pool.getR2() - pool.getR1()) / pool.getL()) * pool.getL() -
                 pool.getR2()) /
                (-abs(ball.getVel()[1] / ball.getVel()[0]) +
                 (pool.getR2() - pool.getR1()) / pool.getL());

            T collisionY = ((-pool.getR2() + pool.getR1()) / pool.getL()) *
                               (collisionX - pool.getL()) +
                           pool.getR2();

            T collisionTime =
                time + (collisionX - ball.getPos()[0]) / ball.getVel()[0];

            if (collisionX < 0 || collisionX > pool.getL()) {
                collisions.push_back(
                    Collision<T>(pool.getL(), computeOutputY(), 0));
                ball.setPos({pool.getL(), computeOutputY()});
            } else {
                collisions.push_back(
                    Collision<T>(collisionX, collisionY, collisionTime));
                ball.setPos({collisionX, collisionY});
            }

        } else {
            T collisionX =
                (-ball.getPos()[1] -
                 abs(ball.getVel()[1] / ball.getVel()[0]) * ball.getPos()[0] +
                 ((pool.getR2() - pool.getR1()) / pool.getL()) * pool.getL() -
                 pool.getR2()) /
                (-abs(ball.getVel()[1] / ball.getVel()[0]) +
                 (pool.getR2() - pool.getR1()) / pool.getL());

            T collisionY = ((pool.getR2() - pool.getR1()) / pool.getL()) *
                               (collisionX - pool.getL()) -
                           pool.getR2();

            T collisionTime =
                (collisionX - ball.getPos()[0]) / ball.getVel()[0];
            collisions.push_back(
                Collision<T>(collisionX, collisionY, collisionTime));
            ball.setPos({collisionX, collisionY});
            std::cout << "Collision at: " << collisionX << ", " << collisionY
                      << std::endl;
            std::cout << "Ball position: " << ball.getPos()[0] << ", "
                      << ball.getPos()[1] << std::endl;
        }
    }
}

template <typename T> void System<T>::computeNextBallVel() {
    T newVx = sqrt(
        (pow(ball.getVel()[0], 2) + pow(ball.getVel()[1], 2)) /
        (1 +
         pow(tan(2 * atan(abs((pool.getR2() - pool.getR1()) / pool.getL())) -
                 atan(abs(ball.getVel()[1] / ball.getVel()[0]))),
             2)));

    if (ball.getVel()[1] < 0) {
        T newVy =
            newVx *
            tan(2 * atan(abs((pool.getR2() - pool.getR1()) / pool.getL())) -
                atan(abs(ball.getVel()[1] / ball.getVel()[0])));
        collisions[collisions.size() - 1].setVel({newVx, newVy});
        ball.setVel({newVx, newVy});
    } else {

        T newVy =
            -newVx *
            tan(2 * atan(abs((pool.getR2() - pool.getR1()) / pool.getL())) -
                atan(abs(ball.getVel()[1] / ball.getVel()[0])));
        collisions[collisions.size() - 1].setVel({newVx, newVy});
        ball.setVel({newVx, newVy});
    }
}

template <typename T> T System<T>::computeOutputY() {
    return collisions[collisions.size() - 1].getPos()[1] +
           (ball.getVel()[1] / ball.getVel()[0]) *
               (pool.getL() - collisions[collisions.size() - 1].getPos()[0]);
}

template <typename T> void System<T>::simulate() {

    while (ball.getPos()[0] < pool.getL() && ball.getPos()[0] > 0) {

        computeNextCollision();
        computeNextBallVel();
        time = collisions[collisions.size() - 1].getTime();

        if (ball.getPos()[0] < 0 || ball.getPos()[0] > pool.getL() ||
            ball.getPos()[1] > pool.getR1() ||
            ball.getPos()[1] < -pool.getR1()) {
            std::cout << "Ball out of bounds." << std::endl;

        } else {
            std::cout << "Time: " << time << std::endl;
            std::cout << "Ball position: " << ball.getPos()[0] << ", "
                      << ball.getPos()[1] << std::endl;
            std::cout << "Ball velocity: " << ball.getVel()[0] << ", "
                      << ball.getVel()[1] << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
    }

    std::cout << "Simulation ended, with output Y of:" << computeOutputY()
              << std::endl;
}

template <typename T> void System<T>::reset() {
    ball.setPos({0, 0});
    time = 0;
    collisions.clear();
    std::cout << "System reset." << std::endl;
}

template class System<int>;
template class System<float>;
template class System<double>;