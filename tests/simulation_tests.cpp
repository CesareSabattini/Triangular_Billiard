#include "../src/simulation/System.hpp"
#include "doctest.h"

TEST_CASE("System class tests") {
    SUBCASE("System constructor") {
        // r1<r2
        CHECK_THROWS_AS(System<double>(-1.0, 0.0, 10.0, 1.0, 5),
                        std::invalid_argument);
        // l<0
        CHECK_THROWS_AS(System<double>(0.0, 0.0, -10.0, 1.0, 0.5),
                        std::invalid_argument);

        // r1<0
        CHECK_THROWS_AS(System<double>(0.0, 0.0, 10.0, -1.0, 0.5),
                        std::invalid_argument);

        // r2<0
        CHECK_THROWS_AS(System<double>(0.0, 0.0, 10.0, 1.0, -0.5),
                        std::invalid_argument);

        // theta out of range
        CHECK_THROWS_AS(System<double>(M_PI, 0.0, 10.0, 1.0, 0.5),
                        std::invalid_argument);

        // y out of range
        CHECK_THROWS_AS(System<double>(10.0, -1.0, 10.0, 1.0, 0.5),
                        std::invalid_argument);

        // l=0
        CHECK_THROWS_AS(System<double>(0.0, 0.0, 0.0, 1.0, 0.5),
                        std::invalid_argument);

        // correct one
        CHECK_NOTHROW(System<double>(0.5, 0.0, 10.0, 1.0, 0.5));
    }

    SUBCASE("System computeNextCollision tests") {
        System<double> system;

        system.updateParams(M_PI / 4, 0, 10.0, 1.0, 0.5);

        CHECK(system.getCollisions().size() == 1);
        system.computeNextCollision();

        CHECK(system.getCollisions().size() == 2);
        Collision<double> &newCollision = system.getCollisions().back();
        CHECK(newCollision.getTheta() ==
              doctest::Approx(-0.885).epsilon(0.001));
        CHECK(newCollision.getPos()[0] == doctest::Approx(0.95).epsilon(0.01));
        CHECK(newCollision.getPos()[1] == doctest::Approx(0.95).epsilon(0.01));
    }

    SUBCASE("System updateParams tests") {
        System<double> system(0.0, 0.0, 10.0, 1.0, 0.5);
        system.updateParams(M_PI / 4, 0.5, 10.0, 1.0, 0.5);
        CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
        CHECK(system.getBall().getPos()[1] == doctest::Approx(0.5));
        CHECK(system.getBall().getTheta() == doctest::Approx(M_PI / 4));
        CHECK(system.getPool().getL() == doctest::Approx(10.0));
        CHECK(system.getPool().getR1() == doctest::Approx(1.0));
        CHECK(system.getPool().getR2() == doctest::Approx(0.5));
        CHECK(system.getTime() == doctest::Approx(0.0));
        CHECK(system.getCollisions().size() == 1);
        CHECK(system.getCollisions().back().getPos()[0] ==
              doctest::Approx(0.0));
        CHECK(system.getCollisions().back().getPos()[1] ==
              doctest::Approx(0.5));
        CHECK(system.getCollisions().back().getTheta() ==
              doctest::Approx(M_PI / 4));

        system.updateParams({0.5, M_PI / 4});
        CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
        CHECK(system.getBall().getPos()[1] == doctest::Approx(0.5));
        CHECK(system.getBall().getTheta() == doctest::Approx(M_PI / 4));
        CHECK(system.getTime() == doctest::Approx(0.0));
        CHECK(system.getCollisions().size() == 1);
        CHECK(system.getCollisions().back().getPos()[0] ==
              doctest::Approx(0.0));
        CHECK(system.getCollisions().back().getPos()[1] ==
              doctest::Approx(0.5));
        CHECK(system.getCollisions().back().getTheta() ==
              doctest::Approx(M_PI / 4));
    }

    SUBCASE("System::computeOutputY() tests") {
        System<double> system(0.0, 0.0, 10.0, 1.0, 0.5);
        system.updateParams(M_PI / 4, 0.5, 10.0, 1.0, 0.5);

        CHECK(system.computeOutputY() == doctest::Approx(10.5));

        system.updateParams(-M_PI / 4, -0.5, 10.0, 1.0, 0.5);
        CHECK(system.computeOutputY() == doctest::Approx(-10.5));

        system.updateParams(0, 0.0, 10.0, 1.0, 0.5);
        CHECK(system.computeOutputY() == doctest::Approx(0.0));

        system.updateParams(0, 0.5, 10.0, 1.0, 0.5);
        CHECK(system.computeOutputY() == doctest::Approx(0.5));

        system.updateParams(0, -0.5, 10.0, 1.0, 0.5);
        system.computeNextCollision();
        CHECK(system.computeOutputY() == doctest::Approx(-0.5));
    }

    SUBCASE("System::throwTheBall() tests") {
        System<double> system;
        system.updateParams(-M_PI / 6, 1.5, 10.0, 2.0, 1.0);
        const double alpha = std::atan((2.0 - 1.0) / 10.0);
        double expectedTheta = -M_PI / 6 + 2 * alpha;
        double expectedX =
            (-1.5 + 2.0) / (std::tan(-M_PI / 6) + ((2.0 - 1.0) / 10.0));
        double expectedY = 2.0 - ((2.0 - 1.0) / 10.0) * expectedX;

        CHECK_THROWS_AS(system.throwTheBall(), std::invalid_argument);
        Collision<double> &lastCollision = system.getCollisions().back();

        CHECK(lastCollision.getTheta() == doctest::Approx(expectedTheta));
        CHECK(lastCollision.getPos()[0] == doctest::Approx(expectedX));
        CHECK(lastCollision.getPos()[1] == doctest::Approx(expectedY));

        system.updateParams(M_PI / 6, -1.5, 10.0, 2.0, 1.0);
        expectedTheta = M_PI / 6 - 2 * alpha;
        expectedX = (1.5 + 2.0) / (-std::tan(M_PI / 6) + ((2.0 - 1.0) / 10.0));
        expectedY = -2.0 + ((2.0 - 1.0) / 10.0) * expectedX;

        CHECK_THROWS_AS(system.throwTheBall(), std::invalid_argument);
        lastCollision = system.getCollisions().back();

        CHECK(lastCollision.getTheta() == doctest::Approx(expectedTheta));
        CHECK(lastCollision.getPos()[0] == doctest::Approx(expectedX));
        CHECK(lastCollision.getPos()[1] == doctest::Approx(expectedY));
    }

    SUBCASE("System::simulate() tests") {
        System<double> system;
        system.updateParams(M_PI / 6, 0.5, 10.0, 1.0, 0.5);

        system.simulate();

        auto &collisions = system.getCollisions();
        REQUIRE(collisions.size() > 0);

        auto finalPos = system.getBall().getPos();
        CHECK(finalPos[0] == doctest::Approx(10.0));

        double outputY = system.computeOutputY();
        CHECK(outputY == doctest::Approx(collisions.back().getPos()[1]));
    }

    SUBCASE("System::reset() tests") {
        System<double> system;
        system.updateParams(M_PI / 6, 0.5, 10.0, 1.0, 0.5);

        system.simulate();
        system.reset();

        CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
        CHECK(system.getBall().getPos()[1] == doctest::Approx(0.0));
        CHECK(system.getBall().getTheta() == doctest::Approx(0.0));
        CHECK(system.getTime() == doctest::Approx(0.0));
        CHECK(system.getCollisions().size() == 1);
        CHECK(system.getCollisions().back().getPos()[0] ==
              doctest::Approx(0.0));
        CHECK(system.getCollisions().back().getPos()[1] ==
              doctest::Approx(0.0));
        CHECK(system.getCollisions().back().getTheta() == doctest::Approx(0.0));
    }
}