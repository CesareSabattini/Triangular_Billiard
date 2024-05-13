#include "../analysis/Analysis.hpp" // Assumendo che le tue funzioni siano dichiarate qui
#include "doctest.h"

TEST_CASE("Testing meanY and meanTheta functions") {
    // qui si assume che i metodi di system siano corretti. La correttezza può
    // essere verificata in simulation_tests.cpp
    std::shared_ptr<System<double>> system = std::make_shared<System<double>>();
    const int numSimulations = 1E3;
    Analysis::Analyzer<double> analyzer(system, numSimulations);

    SUBCASE("Test mean functions with appropriate positive "
            "values") {

        std::vector<std::array<double, 2>> data = {{1.0, 0},
                                                   {2.0, M_PI / 8},
                                                   {3.0, M_PI / 6},
                                                   {4.0, M_PI / 4},
                                                   {5.0, M_PI / 2}};
        CHECK(analyzer.meanY(data) == doctest::Approx(3.0) &&
              analyzer.meanTheta(data) == doctest::Approx(0.654));
    }

    SUBCASE("Test mean functions with appropriate negative "
            "values") {

        std::vector<std::array<double, 2>> data = {{-100.0, 0},
                                                   {-255.0, -M_PI / 8},
                                                   {-355.0, -M_PI / 6},
                                                   {-443.0, -M_PI / 4},
                                                   {-59.0, -M_PI / 2}};
        CHECK(analyzer.meanY(data) == doctest::Approx(-242.4) &&
              analyzer.meanTheta(data) == doctest::Approx(-0.654));
    }

    SUBCASE("Test mean functions with empty vector") {
        std::vector<std::array<double, 2>> data = {};
        CHECK_THROWS_AS(analyzer.meanY(data) && analyzer.meanTheta(data),
                        std::invalid_argument);
    }

    SUBCASE("Test mean with data out of range") {
        std::vector<std::array<double, 2>> data = {
            {system->getPool().getR1() + 1, 0},
            {2.0, M_PI / 8},
            {3.0, M_PI / 6},
            {4.0, M_PI / 4},
            {5.0, M_PI / 2},
            {6.0, M_PI}};

        CHECK_THROWS_AS(analyzer.meanY(data) && analyzer.meanTheta(data),
                        std::invalid_argument);
    };

    SUBCASE("Test mean with single data pair") {
        std::vector<std::array<double, 2>> data = {{2, 0}};

        CHECK(analyzer.meanY(data) == doctest::Approx(2) &&
              analyzer.meanTheta(data) == doctest::Approx(0));
    };
}

TEST_CASE("Testing standardDeviationY and standardDeviationTheta functions") {

    std::shared_ptr<System<double>> system = std::make_shared<System<double>>();
    const int numSimulations = 1E3;
    Analysis::Analyzer<double> analyzer(system, numSimulations);

    SUBCASE("Test std functions with appropriate positive "
            "values") {

        std::vector<std::array<double, 2>> data = {{1.0, 0},
                                                   {2.0, M_PI / 8},
                                                   {3.0, M_PI / 6},
                                                   {4.0, M_PI / 4},
                                                   {5.0, M_PI / 2}};
        CHECK(analyzer.standardDeviationY(data) == doctest::Approx(1.581) &&
              analyzer.standardDeviationTheta(data) == doctest::Approx(0.785));
    }

    SUBCASE("Test std functions with appropriate negative "
            "values") {

        std::vector<std::array<double, 2>> data = {{-100.0, 0},
                                                   {-255.0, -M_PI / 8},
                                                   {-355.0, -M_PI / 6},
                                                   {-443.0, -M_PI / 4},
                                                   {-59.0, -M_PI / 2}};
        CHECK(analyzer.standardDeviationY(data) == doctest::Approx(1.581) &&
              analyzer.standardDeviationTheta(data) == doctest::Approx(0.785));
    }

    SUBCASE("Test std functions with empty vector") {
        std::vector<std::array<double, 2>> data = {};
        CHECK_THROWS_AS(analyzer.standardDeviationY(data) &&
                            analyzer.standardDeviationTheta(data),
                        std::invalid_argument);
    }

    SUBCASE("Test std with data out of range") {
        std::vector<std::array<double, 2>> data = {
            {system->getPool().getR1() + 1, 0},
            {2.0, M_PI / 8},
            {3.0, M_PI / 6},
            {4.0, M_PI / 4},
            {5.0, M_PI / 2},
            {6.0, M_PI}};

        CHECK_THROWS_AS(analyzer.standardDeviationY(data) &&
                            analyzer.standardDeviationTheta(data),
                        std::invalid_argument);
    };

    SUBCASE("Test std with single data pair") {
        std::vector<std::array<double, 2>> data = {{2, 0}};

        CHECK(analyzer.standardDeviationY(data) == doctest::Approx(0) &&
              analyzer.standardDeviationTheta(data) == doctest::Approx(0));
    };
}