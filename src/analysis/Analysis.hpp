#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "../simulation/System.hpp"
#include "./Results.hpp"
#include <array>
#include <cmath>
#include <concepts>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

namespace Analysis {

template <typename T>
concept DoubleOrFloat = std::is_same_v<T, double> || std::is_same_v<T, float>;

template <typename T>
requires DoubleOrFloat<T>
class Analyzer {

  public:
    Analyzer(std::shared_ptr<System<T>> p_system, int n)
        : system(p_system), numSimulations(n) {

        if (numSimulations <= 0) {
            throw std::invalid_argument(
                "Number of simulations must be greater than 0.");
        }
    }

    void generate() {
        std::random_device rd;
        std::mt19937 generator(rd());

        T lower_boundY = -system->getPool().getR1();
        T upper_boundY = system->getPool().getR1();
        T sigma1 = system->getPool().getR2() / 2;

        for (int i = 0; i < numSimulations; i++) {
            std::normal_distribution<T> distribution1(0, sigma1);
            T value;
            do {
                value = distribution1(generator);
            } while (value < lower_boundY || value > upper_boundY);
            inputs.push_back({value, 0});
        }

        T lower_boundT = -M_PI / 2;
        T upper_boundT = M_PI / 2;
        T sigma2 = M_PI / 6;

        for (int i = 0; i < numSimulations; i++) {
            std::normal_distribution<T> distribution2(0, sigma2);
            T value;
            do {
                value = distribution2(generator);
            } while (value < lower_boundT || value > upper_boundT);
            inputs[i][1] = value;
        }
    }

    void simulate() {
        for (int i = 0; i < numSimulations; i++) {
            system->updateParams(inputs[i]);
            system->simulate();
            std::cout << "Simulation " << i + 1 << " completed." << std::endl;

            outputs.push_back(
                {system->getCollisions()[system->getCollisions().size() - 1]
                     .getPos()[1],
                 0});

            outputs[i][1] =
                system->getCollisions()[system->getCollisions().size() - 1]
                    .getTheta();

            system->reset();
        }
    }
    void analyze() {
        results.meanY = meanY(outputs);
        results.meanTheta = meanTheta(outputs);
        results.stdY = standardDeviationY(outputs);
        results.stdTheta = standardDeviationTheta(outputs);
    }
    void printResults() {
        std::cout << "Results: " << std::endl;
        std::cout << "Mean Y: " << results.meanY << std::endl;
        std::cout << "Mean Theta: " << results.meanTheta << std::endl;
        std::cout << "Standard Deviation Y: " << results.stdY << std::endl;
        std::cout << "Standard Deviation Theta: " << results.stdTheta
                  << std::endl;
    }

    T meanY(const std::vector<std::array<T, 2>> &values) {
        if (std::find_if(values.begin(), values.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[0] < -system->getPool().getR1() ||
                                    elem[0] > system->getPool().getR1();
                         }))
            throw std::invalid_argument("Y values must be in [-r1, r1].");
        else {
            if (values.empty())
                throw std::invalid_argument("Empty vector.");

            if (values.size() == 1)
                return values[0][0];

            T sum = std::accumulate(
                values.begin(), values.end(), T(0),
                [](const T &a, const std::array<T, 2> &b) { return a + b[0]; });

            return sum / values.size();
        }
    }

    T meanTheta(const std::vector<std::array<T, 2>> &values) {

        if (std::find_if(values.begin(), values.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         })) {
            throw std::invalid_argument(
                "Theta values must be in [-pi/2, pi/2].");

        } else {
            if (values.empty())
                throw std::invalid_argument("Empty vector.");

            if (values.size() == 1)
                return values[0][1];

            T sum = std::accumulate(
                values.begin(), values.end(), T(0),
                [](const T &a, const std::array<T, 2> &b) { return a + b[1]; });

            return sum / values.size();
        }
    }

    T standardDeviationY(const std::vector<std::array<T, 2>> &values) {
        if (values.empty())
            return T(0);

        T m = meanY(values);

        T sum_squares =
            std::accumulate(values.begin(), values.end(), T(0),
                            [m](const T &a, const std::array<T, 2> &b) {
                                return (a + (b[0] - m) * (b[0] - m));
                            });

        return std::sqrt(sum_squares / (values.size() - 1));
    }

    T standardDeviationTheta(const std::vector<std::array<T, 2>> &values) {
        if (values.empty())
            return T(0);

        T m = meanTheta(values);

        T sum_squares =
            std::accumulate(values.begin(), values.end(), T(0),
                            [m](const T &a, const std::array<T, 2> &b) {
                                return (a + (b[1] - m) * (b[1] - m));
                            });

        return std::sqrt(sum_squares / (values.size() - 1));
    }

    Results<T> getResults() { return results; }

  private:
    int numSimulations;
    std::shared_ptr<System<T>> system;
    std::vector<std::array<T, 2>> inputs;
    std::vector<std::array<T, 2>> outputs;
    Results<T> results;
};
} // namespace Analysis
#endif