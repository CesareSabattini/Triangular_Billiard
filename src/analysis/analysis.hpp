#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "../simulation/system.hpp"
#include "./results.hpp"
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
        inputs.clear();
        outputs.clear();
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

        T lower_boundT = -static_cast<T>(M_PI / 2);
        T upper_boundT = static_cast<T>(M_PI / 2);
        T sigma2 = static_cast<T>(M_PI / 6);

        for (std::allocator<std::array<double, 2>>::size_type i = 0;
             i < static_cast<std::allocator<std::array<double, 2>>::size_type>(
                     numSimulations);
             i++) {
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
            system->updateParams(inputs[static_cast<
                std::allocator<std::array<double, 2>>::size_type>(i)]);
            system->simulate();
            std::cout << "Simulation " << i + 1 << " completed." << std::endl;

            if (system->getCollisions()[system->getCollisions().size() - 1]
                    .getPos()[0] == system->getPool().getL()) {
                outputs.push_back(
                    {system->getCollisions()[system->getCollisions().size() - 1]
                         .getPos()[1],
                     system->getCollisions()[system->getCollisions().size() - 1]
                         .getTheta()});
            }
            system->reset();
        }
    }
    void analyze() {
        results.meanY = meanY();
        results.meanTheta = meanTheta();
        results.stdY = standardDeviationY();
        results.stdTheta = standardDeviationTheta();
    }
    void printResults() {
        std::cout << "Results: " << std::endl;
        std::cout << "Mean Y: " << results.meanY << std::endl;
        std::cout << "Mean Theta: " << results.meanTheta << std::endl;
        std::cout << "Standard Deviation Y: " << results.stdY << std::endl;
        std::cout << "Standard Deviation Theta: " << results.stdTheta
                  << std::endl;
    }

    T meanY() {

        auto it =
            std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[0] < -system->getPool().getR1() ||
                                    elem[0] > system->getPool().getR1();
                         });

        if (it != outputs.end()) {
            throw std::invalid_argument(
                "MeanY: Y outputs must be in [-r1, r1].");
        } else {
            if (outputs.empty())
                throw std::invalid_argument("Empty vector.");

            if (outputs.size() == 1)
                return outputs[0][0];

            T sum =
                std::accumulate(outputs.begin(), outputs.end(), T(0),
                                [this](const T &a, const std::array<T, 2> &b) {
                                    return a + b[0];
                                });

            return sum / static_cast<T>(outputs.size());
        }
    }

    T meanTheta() {

        auto it =
            std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

        if (it != outputs.end()) {
            throw std::invalid_argument(
                "Theta outputs must be in [-pi/2, pi/2].");

        } else {
            if (outputs.empty())
                throw std::invalid_argument("Empty vector.");

            if (outputs.size() == 1)
                return outputs[0][1];

            T sum =
                std::accumulate(outputs.begin(), outputs.end(), T(0),
                                [this](const T &a, const std::array<T, 2> &b) {
                                    return a + b[1];
                                });

            return sum / static_cast<T>(outputs.size());
        }
    }

    T standardDeviationY() {

        auto it =
            std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[0] < -system->getPool().getR1() ||
                                    elem[0] > system->getPool().getR1();
                         });

        if (it != outputs.end())
            throw std::invalid_argument("Y outputs must be in [-r1, r1].");
        else {
            if (outputs.empty())
                throw std::invalid_argument("Empty vector.");

            T m = meanY();

            T sum_squares =
                std::accumulate(outputs.begin(), outputs.end(), T(0),
                                [m](const T &a, const std::array<T, 2> &b) {
                                    return (a + (b[0] - m) * (b[0] - m));
                                });

            return std::sqrt(sum_squares / static_cast<T>(outputs.size()));
        }
    }

    T standardDeviationTheta() {

        auto it =
            std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                             return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

        if (it != outputs.end())
            throw std::invalid_argument("Y outputs must be in [-r1, r1].");
        else {
            if (outputs.empty())
                throw std::invalid_argument("Empty vector.");

            T m = meanTheta();

            T sum_squares =
                std::accumulate(outputs.begin(), outputs.end(), T(0),
                                [m](const T &a, const std::array<T, 2> &b) {
                                    return (a + (b[1] - m) * (b[1] - m));
                                });

            return std::sqrt(sum_squares / static_cast<T>(outputs.size()));
        }
    }

    Results<T> getResults() { return results; }

    // for testing purposes only
    void setOutput(const std::vector<std::array<T, 2>> &p_outputs) {
        outputs = p_outputs;
    }

  private:
    std::shared_ptr<System<T>> system;
    int numSimulations;
    std::vector<std::array<T, 2>> inputs;
    std::vector<std::array<T, 2>> outputs;
    Results<T> results;
};
} // namespace Analysis
#endif