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

template <typename T>
concept DoubleOrFloat = std::is_same_v<T, double> || std::is_same_v<T, float>;

template <typename T>
requires DoubleOrFloat<T>
class Analysis {

  public:
    Analysis(std::shared_ptr<System<T>> p_system, int n)
        : system(p_system), numSimulations(n) {}

    void generate() {
        std::default_random_engine generator;

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

            outputs.push_back(
                {system->getCollisions()[system->getCollisions().size() - 1]
                     .getPos()[1],
                 0});

            outputs[i][1] =
                system->getCollisions()[system->getCollisions().size() - 1]
                    .getTheta();
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
        if (values.empty())
            return T(0);
        T sum = std::accumulate(
            values.begin(), values.end(), T(0),
            [](const T &a, const std::array<T, 2> &b) { return a + b[0]; });

        return sum / values.size();
    }

    T meanTheta(const std::vector<std::array<T, 2>> &values) {
        if (values.empty())
            return T(0);
        T sum = std::accumulate(
            values.begin(), values.end(), T(0),
            [](const T &a, const std::array<T, 2> &b) { return a + b[1]; });

        return sum / values.size();
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

#endif