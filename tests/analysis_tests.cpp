#include "../src/analysis/Analysis.hpp"
#include "doctest.h"

TEST_CASE("Testing meanY and meanTheta functions") {
    // qui si assume che i metodi di system siano corretti. La correttezza può
    // essere verificata in simulation_tests.cpp
    std::shared_ptr<System<double>> system =
        std::make_shared<System<double>>(0.5, 0.0, 10.0, 1E3, 10);
    const int numSimulations = 1E3;
    Analysis::Analyzer<double> analyzer(system, numSimulations);

    SUBCASE("Test mean functions with appropriate positive "
            "values") {

        std::vector<std::array<double, 2>> data = {{1.0, 0},
                                                   {2.0, M_PI / 8},
                                                   {3.0, M_PI / 6},
                                                   {4.0, M_PI / 4},
                                                   {5.0, M_PI / 2}};

        analyzer.setOutput(data);

        double meanYResult = analyzer.meanY();
        CHECK(meanYResult == doctest::Approx(3.0).epsilon(0.001));

        double meanThetaResult = analyzer.meanTheta();
        CHECK(meanThetaResult == doctest::Approx(0.654).epsilon(0.001));
    }

    SUBCASE("Test mean functions with appropriate negative "
            "values") {

        std::vector<std::array<double, 2>> data = {{-100.0, 0},
                                                   {-255.0, -M_PI / 8},
                                                   {-355.0, -M_PI / 6},
                                                   {-443.0, -M_PI / 4},
                                                   {-59.0, -M_PI / 2}};
        analyzer.setOutput(data);

        double meanYResult = analyzer.meanY();
        CHECK(meanYResult == doctest::Approx(-242.4));

        double meanThetaResult = analyzer.meanTheta();
        CHECK(meanThetaResult == doctest::Approx(-0.654).epsilon(0.001));
    }

    SUBCASE("Test mean functions with empty vector") {
        std::vector<std::array<double, 2>> data = {};
        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.meanY(), std::invalid_argument);

        CHECK_THROWS_AS(analyzer.meanTheta(), std::invalid_argument);
    }

    SUBCASE("Test mean with data out of range") {
        std::vector<std::array<double, 2>> data = {
            {system->getPool().getR1() + 1, 0},
            {2.0, M_PI / 8},
            {3.0, M_PI / 6},
            {4.0, M_PI / 4},
            {5.0, M_PI / 2},
            {6.0, M_PI}};

        analyzer.setOutput(data);

        CHECK_THROWS_AS(analyzer.meanY() && analyzer.meanTheta(),
                        std::invalid_argument);
    };

    SUBCASE("Test mean with single data pair") {
        std::vector<std::array<double, 2>> data = {{2, 0}};

        analyzer.setOutput(data);

        CHECK(analyzer.meanY() == doctest::Approx(2));
        CHECK(analyzer.meanTheta() == doctest::Approx(0));
    };
}

TEST_CASE("Testing standardDeviationY and standardDeviationTheta functions") {

    std::shared_ptr<System<double>> system = std::make_shared<System<double>>();
    system->getPool().setL(10.0);
    system->getPool().setRs(1E3, 0.5);

    const int numSimulations = 1E3;
    Analysis::Analyzer<double> analyzer(system, numSimulations);

    SUBCASE("Test std functions with appropriate positive "
            "values") {

        std::vector<std::array<double, 2>> data = {{1.0, 0},
                                                   {2.0, M_PI / 8},
                                                   {3.0, M_PI / 6},
                                                   {4.0, M_PI / 4},
                                                   {5.0, M_PI / 2}};

        analyzer.setOutput(data);
        double stdY = analyzer.standardDeviationY();
        CHECK(stdY == doctest::Approx(1.414).epsilon(0.001));

        double stdTheta = analyzer.standardDeviationTheta();
        CHECK(stdTheta == doctest::Approx(0.52).epsilon(0.01));
    }

    SUBCASE("Test std functions with appropriate negative "
            "values") {

        std::vector<std::array<double, 2>> data = {{-100.0, 0},
                                                   {-255.0, -M_PI / 8},
                                                   {-355.0, -M_PI / 6},
                                                   {-443.0, -M_PI / 4},
                                                   {-59.0, -M_PI / 2}};

        analyzer.setOutput(data);
        double stdY = analyzer.standardDeviationY();
        CHECK(stdY == doctest::Approx(146.28).epsilon(0.01));

        double stdTheta = analyzer.standardDeviationTheta();
        CHECK(stdTheta == doctest::Approx(0.52).epsilon(0.01));
    }

    SUBCASE("Test std functions with empty vector") {
        std::vector<std::array<double, 2>> data =
            std::vector<std::array<double, 2>>();

        std::cout << data.size() << std::endl;

        analyzer.setOutput(data);

        CHECK_THROWS_AS(analyzer.standardDeviationY(), std::invalid_argument);

        CHECK_THROWS_AS(analyzer.standardDeviationTheta(),
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

        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.standardDeviationY() &&
                            analyzer.standardDeviationTheta(),
                        std::invalid_argument);
    };

    SUBCASE("Test std with single data pair") {
        std::vector<std::array<double, 2>> data = {{2, 0}};
        analyzer.setOutput(data);

        double stdY = analyzer.standardDeviationY();
        CHECK(stdY == doctest::Approx(0));

        double stdTheta = analyzer.standardDeviationTheta();
        CHECK(stdTheta == doctest::Approx(0));
    };
}
