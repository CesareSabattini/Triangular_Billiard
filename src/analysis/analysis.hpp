#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "../simulation/system.hpp"
#include "./results.hpp"
#include "parameters.hpp"
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
    Analyzer(std::shared_ptr<simulation::System<T>> p_system,
             Parameters<T> p_parameters);

    void generate();

    void simulate();

    void analyze();

    T meanY();

    T meanTheta();

    T standardDeviationY();
    T standardDeviationTheta();
    T skewnessY();
    T skewnessTheta();
    T kurtosisY();
    T kurtosisTheta();
    void printResults();
    Results<T> getResults();
    void setOutput(const std::vector<std::array<T, 2>> &p_outputs);

  private:
    std::shared_ptr<simulation::System<T>> system;
    Parameters<T> parameters;
    std::vector<std::array<T, 2>> inputs;
    std::vector<std::array<T, 2>> outputs;
    Results<T> results;
};
} // namespace Analysis
#endif