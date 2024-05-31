#include "analysis.hpp"

namespace Analysis {
template <typename T>
Analyzer<T>::Analyzer(std::shared_ptr<simulation::System<T>> p_system,
                      Parameters<T> p_parameters)
    : system(p_system), parameters(p_parameters) {

  if (p_parameters.numSimulations <= 0) {
    throw std::invalid_argument(
        "Number of simulations must be greater than 0.");
  }

  if (p_parameters.meanY < -system->getPool().getR1() ||
      p_parameters.meanY > system->getPool().getR1()) {
    throw std::invalid_argument("Mean Y must be in [-r1, r1].");
  }

  if (p_parameters.stdY <= 0) {
    throw std::invalid_argument(
        "Standard deviation of Y must be greater than 0.");
  }

  if (p_parameters.meanTheta < -M_PI / 2 || p_parameters.meanTheta > M_PI / 2) {
    throw std::invalid_argument("Mean Theta must be in [-pi/2, pi/2].");
  }

  if (p_parameters.stdTheta <= 0) {
    throw std::invalid_argument(
        "Standard deviation of Theta must be greater than 0.");
  }
}

template <typename T> Analyzer<T>::~Analyzer() {}

template <typename T> void Analyzer<T>::generate() {
  inputs.clear();
  outputs.clear();
  std::random_device rd;
  std::mt19937 generator(rd());

  T lower_boundY = -system->getPool().getR1();
  T upper_boundY = system->getPool().getR1();

  for (int i = 0; i < parameters.numSimulations; i++) {
    std::normal_distribution<T> distribution1(parameters.meanY,
                                              parameters.stdY);
    T value;
    do {
      value = distribution1(generator);
    } while (value < lower_boundY || value > upper_boundY);
    inputs.push_back({value, 0});
  }

  T lower_boundT = -static_cast<T>(M_PI / 2);
  T upper_boundT = static_cast<T>(M_PI / 2);

  for (std::allocator<std::array<double, 2>>::size_type i = 0;
       i < static_cast<std::allocator<std::array<double, 2>>::size_type>(
               parameters.numSimulations);
       i++) {
    std::normal_distribution<T> distribution2(parameters.meanTheta,
                                              parameters.stdTheta);
    T value;
    do {
      value = distribution2(generator);
    } while (value < lower_boundT || value > upper_boundT);
    inputs[i][1] = value;
  }
}

template <typename T> void Analyzer<T>::simulate() {
  for (int i = 0; i < parameters.numSimulations; i++) {
    system->updateParams(
        inputs[static_cast<std::allocator<std::array<double, 2>>::size_type>(
            i)]);
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

template <typename T> void Analyzer<T>::analyze() {
  results.outputSize = outputs.size();
  results.meanY = meanY();
  results.meanTheta = meanTheta();
  results.stdY = stdMeanY();
  results.stdTheta = stdMeanTheta();
  results.skewnessY = skewnessY();
  results.skewnessTheta = skewnessTheta();
  results.kurtosisY = kurtosisY();
  results.kurtosisTheta = kurtosisTheta();
}

template <typename T> T Analyzer<T>::meanY() {

  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[0] < -system->getPool().getR1() ||
                                  elem[0] > system->getPool().getR1();
                         });

  if (it != outputs.end()) {
    throw std::invalid_argument("MeanY: Y outputs must be in [-r1, r1].");
  } else {
    if (outputs.empty())
      throw std::invalid_argument("Empty vector.");

    if (outputs.size() == 1)
      return outputs[0][0];

    T sum = std::accumulate(
        outputs.begin(), outputs.end(), T(0),
        [this](const T &a, const std::array<T, 2> &b) { return a + b[0]; });

    return sum / static_cast<T>(outputs.size());
  }
}

template <typename T> T Analyzer<T>::meanTheta() {

  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

  if (it != outputs.end()) {
    throw std::invalid_argument("Theta outputs must be in [-pi/2, pi/2].");

  } else {
    if (outputs.empty())
      throw std::invalid_argument("Empty vector.");

    if (outputs.size() == 1)
      return outputs[0][1];

    T sum = std::accumulate(
        outputs.begin(), outputs.end(), T(0),
        [this](const T &a, const std::array<T, 2> &b) { return a + b[1]; });

    return sum / static_cast<T>(outputs.size());
  }
}

template <typename T> T Analyzer<T>::standardDeviationY() {

  auto it = std::find_if(outputs.begin(), outputs.end(),
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

    T sum_squares = std::accumulate(outputs.begin(), outputs.end(), T(0),
                                    [m](const T &a, const std::array<T, 2> &b) {
                                      return (a + (b[0] - m) * (b[0] - m));
                                    });

    return std::sqrt(sum_squares / static_cast<T>(outputs.size()));
  }
}

template <typename T> T Analyzer<T>::stdMeanY() {
  T stdDevY = standardDeviationY();
  return stdDevY / std::sqrt(static_cast<T>(outputs.size()));
}
template <typename T> T Analyzer<T>::standardDeviationTheta() {

  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

  if (it != outputs.end())
    throw std::invalid_argument("Y outputs must be in [-r1, r1].");
  else {
    if (outputs.empty())
      throw std::invalid_argument("Empty vector.");

    T m = meanTheta();

    T sum_squares = std::accumulate(outputs.begin(), outputs.end(), T(0),
                                    [m](const T &a, const std::array<T, 2> &b) {
                                      return (a + (b[1] - m) * (b[1] - m));
                                    });

    return std::sqrt(sum_squares / static_cast<T>(outputs.size()));
  }
}

template <typename T> T Analyzer<T>::stdMeanTheta() {
  T stdDevTheta = standardDeviationTheta();
  return stdDevTheta / std::sqrt(static_cast<T>(outputs.size()));
}

template <typename T> T Analyzer<T>::skewnessY() {
  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[0] < -system->getPool().getR1() ||
                                  elem[0] > system->getPool().getR1();
                         });

  if (it != outputs.end())
    throw std::invalid_argument("Y outputs must be in [-r1, r1].");

  if (outputs.empty())
    throw std::invalid_argument("Empty vector.");

  T mean = meanY();
  T std_dev = standardDeviationY();
  T n = static_cast<T>(outputs.size());

  if (n < 3 || std_dev == T(0)) {
    return T(0);
  }

  T skewness = std::accumulate(
                   outputs.begin(), outputs.end(), T(0),
                   [mean, std_dev](const T &acc, const std::array<T, 2> &elem) {
                     T z = (elem[0] - mean) / std_dev;
                     return acc + z * z * z;
                   }) /
               n;

  return skewness * (std::sqrt(n * (n - 1)) / (n - 2));
}

template <typename T> T Analyzer<T>::skewnessTheta() {
  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

  if (it != outputs.end())
    throw std::invalid_argument("Theta outputs must be in [-pi/2, pi/2].");

  if (outputs.empty())
    throw std::invalid_argument("Empty vector.");

  T mean = meanTheta();
  T std_dev = standardDeviationTheta();
  T n = static_cast<T>(outputs.size());

  if (n < 3 || std_dev == T(0)) {
    return T(0);
  }

  T skewness = std::accumulate(
                   outputs.begin(), outputs.end(), T(0),
                   [mean, std_dev](const T &acc, const std::array<T, 2> &elem) {
                     T z = (elem[1] - mean) / std_dev;
                     return acc + z * z * z;
                   }) /
               n;

  return skewness * (std::sqrt(n * (n - 1)) / (n - 2));
}

template <typename T> T Analyzer<T>::kurtosisY() {
  if (outputs.size() < 2)
    throw std::invalid_argument("Need at least two data points.");

  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[0] < -system->getPool().getR1() ||
                                  elem[0] > system->getPool().getR1();
                         });

  if (it != outputs.end())
    throw std::invalid_argument("Y outputs must be in [-r1, r1].");

  T mean = meanY();
  T std_dev = standardDeviationY();
  T n = static_cast<T>(outputs.size());

  T kurtosis = std::accumulate(
                   outputs.begin(), outputs.end(), T(0),
                   [mean, std_dev](const T &acc, const std::array<T, 2> &elem) {
                     T z = (elem[0] - mean) / std_dev;
                     return acc + z * z * z * z;
                   }) /
               n;

  return (kurtosis - 3);
}

template <typename T> T Analyzer<T>::kurtosisTheta() {
  if (outputs.size() < 2)
    throw std::invalid_argument("At least two data points need.");

  auto it = std::find_if(outputs.begin(), outputs.end(),
                         [this](const std::array<T, 2> &elem) {
                           return elem[1] < -M_PI / 2 || elem[1] > M_PI / 2;
                         });

  if (it != outputs.end())
    throw std::invalid_argument("Theta outputs must be in [-pi/2, pi/2].");

  T mean = meanTheta();
  T std_dev = standardDeviationTheta();
  T n = static_cast<T>(outputs.size());

  T kurtosis = std::accumulate(
                   outputs.begin(), outputs.end(), T(0),
                   [mean, std_dev](const T &acc, const std::array<T, 2> &elem) {
                     T z = (elem[1] - mean) / std_dev;
                     return acc + z * z * z * z;
                   }) /
               n;

  return (kurtosis - 3);
}

template <typename T> void Analyzer<T>::printResults() {
  std::cout << "Results: " << std::endl;
  std::cout << "Mean Y: " << results.meanY << std::endl;
  std::cout << "Mean Theta: " << results.meanTheta << std::endl;
  std::cout << "Standard Deviation Y: " << results.stdY << std::endl;
  std::cout << "Standard Deviation Theta: " << results.stdTheta << std::endl;
  std::cout << "Skewness Y: " << results.skewnessY << std::endl;
  std::cout << "Skewness Theta: " << results.skewnessTheta << std::endl;
  std::cout << "Kurtosis Y: " << results.kurtosisY << std::endl;
  std::cout << "Kurtosis Theta: " << results.kurtosisTheta << std::endl;
}

template <typename T> Results<T> Analyzer<T>::getResults() { return results; }
template <typename T>
void Analyzer<T>::setOutput(const std::vector<std::array<T, 2>> &p_outputs) {
  outputs = p_outputs;
}

template class Analyzer<double>;
template class Analyzer<float>;

} // namespace Analysis
