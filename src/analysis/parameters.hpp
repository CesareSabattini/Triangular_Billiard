#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

template <typename T> struct Parameters {

    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    int numSimulations;
    T meanY;
    T stdY;
    T meanTheta;
    T stdTheta;

    Parameters()
        : numSimulations(0), meanY(0), stdY(0), meanTheta(0), stdTheta(0) {}

    Parameters(const int p_numSimulations, const T p_meanY, const T p_stdY,
               const T p_meanTheta, const T p_stdTheta)
        : numSimulations(p_numSimulations), meanY(p_meanY), stdY(p_stdY),
          meanTheta(p_meanTheta), stdTheta(p_stdTheta) {}

    Parameters(const Parameters &p_parameters)
        : numSimulations(p_parameters.numSimulations),
          meanY(p_parameters.meanY), stdY(p_parameters.stdY),
          meanTheta(p_parameters.meanTheta), stdTheta(p_parameters.stdTheta) {}

    Parameters &operator=(const Parameters &p_parameters) {
        numSimulations = p_parameters.numSimulations;
        meanY = p_parameters.meanY;
        stdY = p_parameters.stdY;
        meanTheta = p_parameters.meanTheta;
        stdTheta = p_parameters.stdTheta;
        return *this;
    }

    Parameters(Parameters &&p_parameters)
        : numSimulations(p_parameters.numSimulations),
          meanY(p_parameters.meanY), stdY(p_parameters.stdY),
          meanTheta(p_parameters.meanTheta), stdTheta(p_parameters.stdTheta) {}

    Parameters &operator=(Parameters &&p_parameters) {
        numSimulations = p_parameters.numSimulations;
        meanY = p_parameters.meanY;
        stdY = p_parameters.stdY;
        meanTheta = p_parameters.meanTheta;
        stdTheta = p_parameters.stdTheta;
        return *this;
    }
};

#endif