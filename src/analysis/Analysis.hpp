#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "../simulation/System.hpp"
#include "./Results.hpp"
#include <array>
#include <cmath>
#include <concepts>
#include <memory>
#include <random>
#include <vector>

template <typename T>
concept DoubleOrFloat = std::is_same_v<T, double> || std::is_same_v<T, float>;

template <typename T>
requires DoubleOrFloat<T>
class Analysis {

  public:
    Analysis(std::shared_ptr<System<T>> p_system, int n)
        : system(p_system), numSimulation(n) {}

    void generate() {
        std::default_random_engine generator;

        T lower_boundY = -system->getPool().getR1();
        T upper_boundY = system->getPool().getR1();
        T sigma1 = system->getPool().getR2() / 2;

        for (int i = 0; i < N; i++) {
            std::normal_distribution<T> distribution1(0, sigma1);
            T value;
            do {
                value = distribution1(generator);
            } while (value < lower_boundY || value > upper_boundY);
            inputs[i][0] = value;
        }

        T lower_boundT = -M_PI / 2;
        T upper_boundT = M_PI / 2;
        T sigma2 = M_PI / 6;

        for (int i = 0; i < N; i++) {
            std::normal_distribution<T> distribution2(0, sigma2);
            T value;
            do {
                value = distribution2(generator);
            } while (value < lower_boundT || value > upper_boundT);
            inputs[i][1] = value;
        }
    }

    void simulate() {
        for (int i = 0; i < N; i++) {
            system->updateParams(inputs[i]);
            outputs[i] = system->simulate();
            outputs[i][0] =
                system->getCollisions()[system->getCollisions().size() - 1]
                    .getPos()[1];
            outputs[i][1] =
                system->getCollisions()[system->getCollisions().size() - 1]
                    .getTheta();
        }
    }
    void analyze() {
        results.meanY = mean(outputs[0]);
        results.meanTheta = mean(outputs[1]);
        results.stdY = standardDeviation(outputs[0]);
        results.stdTheta = standardDeviation(outputs[1]);
    }
    void printResults() {
        std::cout << "Results: " << std::endl;
        std::cout << "Mean Y: " << results.meanY << std::endl;
        std::cout << "Mean Theta: " << results.meanTheta << std::endl;
        std::cout << "Standard Deviation Y: " << results.stdY << std::endl;
        std::cout << "Standard Deviation Theta: " << results.stdTheta
                  << std::endl;
    }

    T mean(std::array<T, N> values) {
        T sum = 0;
        for (int i = 0; i < values.size(); i++) {
            sum += values[i];
        }
        return sum / values.size();
    }
    T standardDeviation(std::array<T, N> values) {
        T mean = mean(values);
        T sum = 0;
        for (int i = 0; i < values.size(); i++) {
            sum += (values[i] - mean) * (values[i] - mean);
        }
        return std::sqrt(sum / values.size());
    }

    Results<T> getResults() { return results; }

  private:
    int numSimulations;
    std::shared_ptr<System<T>> system;
    std::array<std::array<T, 2>, N> inputs;
    std::array<T, numSimulations> outputs;
    Results<T> results;
};

#endif