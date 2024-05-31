#include "./mock/mockSystem.hpp"
#include "doctest.h"

TEST_CASE("System class tests") {
  SUBCASE("System constructor") {
    CHECK_THROWS_AS(mock::MockSystem<double>(-1.0, 0.0, 10.0, 1.0, 5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(0.0, 0.0, -10.0, 1.0, 0.5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(0.0, 0.0, 10.0, -1.0, 0.5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(0.0, 0.0, 10.0, 1.0, -0.5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(M_PI, 0.0, 10.0, 1.0, 0.5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(10.0, -1.0, 10.0, 1.0, 0.5),
                    std::invalid_argument);

    CHECK_THROWS_AS(mock::MockSystem<double>(0.0, 0.0, 0.0, 1.0, 0.5),
                    std::invalid_argument);

    CHECK_NOTHROW(mock::MockSystem<double>(0.5, 0.0, 10.0, 1.0, 0.5));
  }

  SUBCASE("System computeNextCollision tests") {
    mock::MockSystem<double> system;

    system.updateParams(M_PI / 4, 0, 10.0, 1.0, 0.5);

    CHECK(system.getCollisions().size() == 1);
    system.computeNextCollision();

    CHECK(system.getCollisions().size() == 2);
    simulation::components::Collision<double> &newCollision =
        system.getCollisions().back();
    CHECK(newCollision.getTheta() == doctest::Approx(-0.885).epsilon(0.001));
    CHECK(newCollision.getPos()[0] == doctest::Approx(0.95).epsilon(0.01));
    CHECK(newCollision.getPos()[1] == doctest::Approx(0.95).epsilon(0.01));
  }

  SUBCASE("System updateParams tests") {
    mock::MockSystem<double> system(0.0, 0.0, 10.0, 1.0, 0.5);
    system.updateParams(M_PI / 4, 0.5, 10.0, 1.0, 0.5);
    CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getBall().getPos()[1] == doctest::Approx(0.5));
    CHECK(system.getBall().getTheta() == doctest::Approx(M_PI / 4));
    CHECK(system.getPool().getL() == doctest::Approx(10.0));
    CHECK(system.getPool().getR1() == doctest::Approx(1.0));
    CHECK(system.getPool().getR2() == doctest::Approx(0.5));
    CHECK(system.getCollisions().size() == 1);
    CHECK(system.getCollisions().back().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getCollisions().back().getPos()[1] == doctest::Approx(0.5));
    CHECK(system.getCollisions().back().getTheta() ==
          doctest::Approx(M_PI / 4));

    system.updateParams({0.5, M_PI / 4});
    CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getBall().getPos()[1] == doctest::Approx(0.5));
    CHECK(system.getBall().getTheta() == doctest::Approx(M_PI / 4));
    CHECK(system.getCollisions().size() == 1);
    CHECK(system.getCollisions().back().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getCollisions().back().getPos()[1] == doctest::Approx(0.5));
    CHECK(system.getCollisions().back().getTheta() ==
          doctest::Approx(M_PI / 4));
  }

  SUBCASE("System::computeOutputY() tests") {
    mock::MockSystem<double> system(0.0, 0.0, 10.0, 1.0, 0.5);
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
    mock::MockSystem<double> system;
    system.updateParams(-M_PI / 20, 1E3 - 1, 10.0, 1E3, 1.0);
    double alpha =
        std::atan((system.getPool().getR1() - system.getPool().getR2()) /
                  system.getPool().getL());
    double expectedTheta = system.getBall().getTheta() + 2 * alpha;
    double expectedX =
        (-system.getBall().getPos()[1] + system.getPool().getR1()) /
        (std::tan(system.getBall().getTheta()) +
         (system.getPool().getR1() - system.getPool().getR2()) /
             system.getPool().getL());
    double expectedY = system.getPool().getR1() -
                       ((system.getPool().getR1() - system.getPool().getR2()) /
                        system.getPool().getL()) *
                           expectedX;

    CHECK_THROWS_AS(system.throwTheBall(), std::invalid_argument);

    system.updateParams(-M_PI / 40, 4.9, 10.0, 5.0, 1.0);
    alpha = std::atan((system.getPool().getR1() - system.getPool().getR2()) /
                      system.getPool().getL());
    expectedTheta = system.getBall().getTheta() + 2 * alpha;
    expectedX = (-system.getBall().getPos()[1] + system.getPool().getR1()) /
                (std::tan(system.getBall().getTheta()) +
                 (system.getPool().getR1() - system.getPool().getR2()) /
                     system.getPool().getL());
    expectedY = system.getPool().getR1() -
                ((system.getPool().getR1() - system.getPool().getR2()) /
                 system.getPool().getL()) *
                    expectedX;
    system.throwTheBall();

    simulation::components::Collision<double> &lastCollision =
        system.getCollisions().back();

    CHECK(lastCollision.getTheta() == doctest::Approx(expectedTheta));
    CHECK(lastCollision.getPos()[0] == doctest::Approx(expectedX));
    CHECK(lastCollision.getPos()[1] == doctest::Approx(expectedY));
  }

  SUBCASE("System::simulate() tests") {
    mock::MockSystem<double> system;
    system.updateParams(M_PI / 6, 0, 10.0, 1.0, 0.5);

    system.simulate();

    auto &collisions = system.getCollisions();
    REQUIRE(collisions.size() > 0);

    auto finalPos = system.getBall().getPos();
    CHECK(finalPos[0] == doctest::Approx(10.0));

    double outputY = system.computeOutputY();
    CHECK(outputY == doctest::Approx(collisions.back().getPos()[1]));
  }

  SUBCASE("System::reset() tests") {
    mock::MockSystem<double> system;
    system.updateParams(M_PI / 6, 0.5, 10.0, 1.0, 0.5);

    system.simulate();
    system.reset();

    CHECK(system.getBall().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getBall().getPos()[1] == doctest::Approx(0.0));
    CHECK(system.getBall().getTheta() == doctest::Approx(0.0));
    CHECK(system.getCollisions().size() == 1);
    CHECK(system.getCollisions().back().getPos()[0] == doctest::Approx(0.0));
    CHECK(system.getCollisions().back().getPos()[1] == doctest::Approx(0.0));
    CHECK(system.getCollisions().back().getTheta() == doctest::Approx(0.0));
  }
}