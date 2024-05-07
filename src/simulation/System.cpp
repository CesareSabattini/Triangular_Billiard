
#include "System.hpp"

template <typename T> System<T>::System() : time(0), ball(), pool() {}

template <typename T>
System<T>::System(T p_theta, T p_y, T p_l, T p_r1, T p_r2)
    : pool(p_l, p_r1, p_r2), time(0), ball(0, p_y, p_theta) {

    std::cout << "Ball created at position: " << 0 << ", " << p_y << std::endl;

    collisions.push_back(Collision<T>(0, p_y, p_theta));
}

template <typename T>
System<T>::System(const Ball<T> &p_ball, const Pool<T> &p_pool)
    : ball(p_ball), pool(p_pool), time(0) {}

template <typename T>
System<T>::System(const System &p_system)
    : ball(p_system.ball), pool(p_system.pool), time(p_system.time) {}

template <typename T> System<T> &System<T>::operator=(const System &p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    time = p_system.time;
    return *this;
}

template <typename T>
System<T>::System(System &&p_system)
    : ball(p_system.ball), pool(p_system.pool), time(p_system.time) {}

template <typename T> System<T> &System<T>::operator=(System &&p_system) {
    ball = p_system.ball;
    pool = p_system.pool;
    time = p_system.time;
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

template <typename T> void System<T>::throwTheBall() {

    const double alpha = atan((pool.getR1() - pool.getR2()) / pool.getL());

    std::cout << "Theta: " << ball.getTheta() << std::endl;
    std::cout << "L: " << pool.getL() << std::endl;

    if (abs(ball.getPos()[1]) >= pool.getR2() &&
        abs(ball.getPos()[1]) <= pool.getR1() && ball.getPos()[1] >= 0 &&
        abs(ball.getTheta()) <=
            atan((abs(ball.getPos()[1]) - pool.getR2()) / pool.getL())) {
        std::cout << "HERE";
        double newTheta = -ball.getTheta() + 2 * alpha;
        double newX = (ball.getPos()[1] + pool.getR1()) /
                      (-tan(ball.getTheta()) +
                       (pool.getR1() - pool.getR2()) / pool.getL());
        double newY = -pool.getR1() +
                      ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        collisions.push_back(Collision<T>(newX, newY, newTheta));
        ball.setPos({newX, newY});
    } else if (abs(ball.getPos()[1]) >= pool.getR2() &&
               abs(ball.getPos()[1]) <= pool.getR1() && ball.getPos()[1] < 0 &&
               abs(ball.getTheta()) <
                   atan((abs(ball.getPos()[1]) - pool.getR2()) / pool.getL())) {
        std::cout << "HERE";
        double newTheta = +ball.getTheta() - 2 * alpha;
        double newX = (-ball.getPos()[1] + pool.getR1()) /
                      (tan(ball.getTheta()) +
                       (pool.getR1() - pool.getR2()) / pool.getL());
        double newY =
            pool.getR1() - ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        collisions.push_back(Collision<T>(newX, newY, newTheta));
        ball.setPos({newX, newY});
    }
}

template <typename T> void System<T>::computeNextCollision() {

    if (collisions[collisions.size() - 1].getTheta() > 0) {
        double newTheta =
            -(collisions[collisions.size() - 1].getTheta() +
              2 * (atan(abs((pool.getR2() - pool.getR1()) / pool.getL()))));
        double newX =
            (pool.getR1() - collisions[collisions.size() - 1].getPos()[1] +
             tan(collisions[collisions.size() - 1].getTheta()) *
                 collisions[collisions.size() - 1].getPos()[0]) /
            (tan(collisions[collisions.size() - 1].getTheta()) +
             (pool.getR1() - pool.getR2()) / pool.getL());

        double newY =
            pool.getR1() - ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        collisions.push_back(Collision<T>(newX, newY, newTheta));
        ball.setPos({newX, newY});
    } else if (collisions[collisions.size() - 1].getTheta() < 0) {
        double newTheta =
            (collisions[collisions.size() - 1].getTheta() +
             2 * (atan(abs((pool.getR2() - pool.getR1()) / pool.getL()))));

        double newX = (pool.getR1() -
                       tan(collisions[collisions.size() - 1].getTheta()) *
                           collisions[collisions.size() - 1].getPos()[0] +
                       collisions[collisions.size() - 1].getPos()[1]) /
                      (-tan(collisions[collisions.size() - 1].getTheta()) +
                       (pool.getR1() - pool.getR2()) / pool.getL());

        double newY = -pool.getR1() +
                      ((pool.getR1() - pool.getR2()) / pool.getL()) * newX;

        collisions.push_back(Collision<T>(newX, newY, newTheta));
        ball.setPos({newX, newY});
    }
}

template <typename T> T System<T>::computeOutputY() {
    double y =
        collisions[collisions.size() - 1].getPos()[1] +
        tan(collisions[collisions.size() - 1].getTheta()) *
            (pool.getL() - collisions[collisions.size() - 1].getPos()[0]);
    return y;
}

template <typename T> void System<T>::simulate() {
    std::cout << "SIMULATION STARTED" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Initial ball position: " << ball.getPos()[0] << ", "
              << ball.getPos()[1] << std::endl;
    std::cout << "Initial pool parameters: "
              << " L= " << pool.getL() << ", "
              << "R1= " << pool.getR1() << ", "
              << "R2= " << pool.getR2() << std::endl;
    std::cout << "--------------------------------" << std::endl;

    throwTheBall();

    std::cout << "Ball thrown";
    std::cout << "HERE";

    if (ball.getPos()[0] < pool.getL()) {

        while (ball.getPos()[0] < pool.getL()) {

            computeNextCollision();

            if (ball.getPos()[0] < 0 || ball.getPos()[0] > pool.getL() ||
                ball.getPos()[1] > pool.getR1() ||
                ball.getPos()[1] < -pool.getR1()) {
                std::cout << "Ball out of bounds." << std::endl;

            } else {
                std::cout << "Time: " << time << std::endl;
                std::cout << "Ball position: " << ball.getPos()[0] << ", "
                          << ball.getPos()[1] << std::endl;

                std::cout << "--------------------------------" << std::endl;
            }
        }
    }

    else {
        std::cout << "Simulation ended, with output Y of:" << ball.getPos()[1]
                  << std::endl
                  << "and number of collisions: " << collisions.size()
                  << std::endl;
    }

    std::cout << "Simulation ended, with output Y of:" << computeOutputY()
              << std::endl;
}

template <typename T>
void System<T>::updateParams(T p_theta, T p_y, T p_l, T p_r1, T p_r2) {
    ball.setPos(std::array<T, 2>({0, p_y}));
    ball.setTheta(p_theta);
    pool.setL(p_l);
    pool.setRs(p_r1, p_r2);
    time = 0;
    collisions.clear();
}

template <typename T> void System<T>::reset() {
    ball.setPos({0, 0});
    time = 0;
    collisions.clear();
}

template class System<int>;
template class System<float>;
template class System<double>;