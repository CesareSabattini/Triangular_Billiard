#include "../src/analysis/analysis.hpp"
#include "doctest.h"

TEST_CASE("Testing meanY and meanTheta functions") {
    std::shared_ptr<simulation::System<double>> system =
        std::make_shared<simulation::System<double>>(0.5, 0.0, 10.0, 1E3, 10);

    Analysis::Parameters<double> parameters(1E3, 0.0, 0.1, 0.0, 0.1);

    Analysis::Analyzer<double> analyzer(system, parameters);

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

    std::shared_ptr<simulation::System<double>> system =
        std::make_shared<simulation::System<double>>();
    system->getPool().setL(10.0);
    system->getPool().setRs(1E3, 0.5);

    Analysis::Parameters<double> parameters(1E3, 0.0, 0.1, 0.0, 0.1);

    Analysis::Analyzer<double> analyzer(system, parameters);

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

TEST_CASE("Test skewnessY and skewnessTheta") {
    std::shared_ptr<simulation::System<double>> system =
        std::make_shared<simulation::System<double>>();
    system->getPool().setL(10.0);
    system->getPool().setRs(1E3, 0.5);

    Analysis::Parameters<double> parameters(1E3, 0.0, 0.1, 0.0, 0.1);

    Analysis::Analyzer<double> analyzer(system, parameters);

    SUBCASE("Test skewness functions with appropriate positive values") {
        std::vector<std::array<double, 2>> data = {{-2.0, -M_PI / 4},
                                                   {-1.0, -M_PI / 8},
                                                   {0.0, 0},
                                                   {1.0, M_PI / 8},
                                                   {2.0, M_PI / 4}};

        analyzer.setOutput(data);
        double skewnessY = analyzer.skewnessY();
        CHECK(skewnessY == doctest::Approx(0.0).epsilon(0.001));

        double skewnessTheta = analyzer.skewnessTheta();
        CHECK(skewnessTheta == doctest::Approx(0.0).epsilon(0.001));
    }

    SUBCASE("Test skewness functions with appropriate negative values") {
        std::vector<std::array<double, 2>> data = {{-2.0, -M_PI / 4},
                                                   {-1.0, -M_PI / 8},
                                                   {0.0, 0},
                                                   {1.0, M_PI / 8},
                                                   {2.0, M_PI / 4}};

        analyzer.setOutput(data);
        double skewnessY = analyzer.skewnessY();
        CHECK(skewnessY == doctest::Approx(0.0).epsilon(0.001));

        double skewnessTheta = analyzer.skewnessTheta();
        CHECK(skewnessTheta == doctest::Approx(0.0).epsilon(0.001));
    }

    SUBCASE("Test skewness functions with empty vector") {
        std::vector<std::array<double, 2>> data = {};

        analyzer.setOutput(data);

        CHECK_THROWS_AS(analyzer.skewnessY(), std::invalid_argument);
        CHECK_THROWS_AS(analyzer.skewnessTheta(), std::invalid_argument);
    }

    SUBCASE("Test skewness with data out of range") {
        std::vector<std::array<double, 2>> data = {
            {system->getPool().getR1() + 1, 0},
            {2.0, M_PI / 8},
            {3.0, M_PI / 6},
            {4.0, M_PI / 4},
            {5.0, M_PI / 2},
            {6.0, M_PI}};

        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.skewnessY(), std::invalid_argument);
        CHECK_THROWS_AS(analyzer.skewnessTheta(), std::invalid_argument);
    }

    SUBCASE("Test skewness with single data pair") {
        std::vector<std::array<double, 2>> data = {{0.0, 0}};
        analyzer.setOutput(data);

        double skewnessY = analyzer.skewnessY();
        CHECK(skewnessY == doctest::Approx(0));

        double skewnessTheta = analyzer.skewnessTheta();
        CHECK(skewnessTheta == doctest::Approx(0));
    }
}


TEST_CASE("Test kurtosisY and kurtosisTheta") {
    std::shared_ptr<simulation::System<double>> system =
        std::make_shared<simulation::System<double>>();
    system->getPool().setL(10.0);
    system->getPool().setRs(1E3, 0.5);

    Analysis::Parameters<double> parameters(1E3, 0.0, 0.1, 0.0, 0.1);

    Analysis::Analyzer<double> analyzer(system, parameters);

    SUBCASE("Test kurtosis functions with appropriate positive values") {
        std::vector<std::array<double, 2>> data = {{1.0, 0},
                                                   {2.0, M_PI / 8},
                                                   {3.0, M_PI / 6},
                                                   {4.0, M_PI / 4},
                                                   {5.0, M_PI / 2}};
        analyzer.setOutput(data);
        double kurtosisY = analyzer.kurtosisY();
        double kurtosisTheta = analyzer.kurtosisTheta();

        CHECK(kurtosisY == doctest::Approx(1.8).epsilon(0.001));
        CHECK(kurtosisTheta == doctest::Approx(1.8).epsilon(0.001));
    }

    SUBCASE("Test kurtosis functions with appropriate negative values") {
        std::vector<std::array<double, 2>> data = {{-1.0, 0},
                                                   {-2.0, -M_PI / 8},
                                                   {-3.0, -M_PI / 6},
                                                   {-4.0, -M_PI / 4},
                                                   {-5.0, -M_PI / 2}};
        analyzer.setOutput(data);
        double kurtosisY = analyzer.kurtosisY();
        double kurtosisTheta = analyzer.kurtosisTheta();

        CHECK(kurtosisY == doctest::Approx(1.8).epsilon(0.001)); 
        CHECK(kurtosisTheta == doctest::Approx(1.8).epsilon(0.001));
    }

    SUBCASE("Test kurtosis functions with empty vector") {
        std::vector<std::array<double, 2>> data = {};
        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.kurtosisY(), std::invalid_argument);
        CHECK_THROWS_AS(analyzer.kurtosisTheta(), std::invalid_argument);
    }

    SUBCASE("Test kurtosis with data out of range") {
        std::vector<std::array<double, 2>> data = {
            {system->getPool().getR1() + 1, 0},
            {2.0, M_PI / 8},
            {3.0, M_PI / 6},
            {4.0, M_PI / 4},
            {5.0, M_PI / 2},
            {6.0, M_PI}};
        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.kurtosisY(), std::invalid_argument);
        CHECK_THROWS_AS(analyzer.kurtosisTheta(), std::invalid_argument);
    }

    SUBCASE("Test kurtosis with single data pair") {
        std::vector<std::array<double, 2>> data = {{2, 0}};
        analyzer.setOutput(data);
        CHECK_THROWS_AS(analyzer.kurtosisY(), std::invalid_argument);
        CHECK_THROWS_AS(analyzer.kurtosisTheta(), std::invalid_argument);
    }
}
