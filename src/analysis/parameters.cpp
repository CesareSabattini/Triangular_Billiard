#include "parameters.hpp"

namespace Analysis {

template <typename T>
Parameters<T>::Parameters()
    : numSimulations(0), meanY(0), stdY(0), meanTheta(0), stdTheta(0) {}

template <typename T>
Parameters<T>::Parameters(const int p_numSimulations, const T p_meanY,
                          const T p_stdY, const T p_meanTheta,
                          const T p_stdTheta)
    : numSimulations(p_numSimulations), meanY(p_meanY), stdY(p_stdY),
      meanTheta(p_meanTheta), stdTheta(p_stdTheta) {}

template <typename T>
Parameters<T>::Parameters(const Parameters<T> &p_parameters)
    : numSimulations(p_parameters.numSimulations), meanY(p_parameters.meanY),
      stdY(p_parameters.stdY), meanTheta(p_parameters.meanTheta),
      stdTheta(p_parameters.stdTheta) {}

template <typename T>
Parameters<T> &Parameters<T>::operator=(const Parameters &p_parameters) {
    numSimulations = p_parameters.numSimulations;
    meanY = p_parameters.meanY;
    stdY = p_parameters.stdY;
    meanTheta = p_parameters.meanTheta;
    stdTheta = p_parameters.stdTheta;
    return *this;
}

template <typename T>
Parameters<T>::Parameters(Parameters<T> &&p_parameters)
    : numSimulations(p_parameters.numSimulations), meanY(p_parameters.meanY),
      stdY(p_parameters.stdY), meanTheta(p_parameters.meanTheta),
      stdTheta(p_parameters.stdTheta) {}

template <typename T>
Parameters<T> &Parameters<T>::operator=(Parameters &&p_parameters) {
    numSimulations = p_parameters.numSimulations;
    meanY = p_parameters.meanY;
    stdY = p_parameters.stdY;
    meanTheta = p_parameters.meanTheta;
    stdTheta = p_parameters.stdTheta;
    return *this;
}

template struct Parameters<float>;
template struct Parameters<double>;
} // namespace Analysis