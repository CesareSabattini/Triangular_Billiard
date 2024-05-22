#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <type_traits>

namespace Analysis {
template <typename T> struct Parameters {

    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    int numSimulations;
    T meanY;
    T stdY;
    T meanTheta;
    T stdTheta;

    Parameters();
    Parameters(const int p_numSimulations, const T p_meanY, const T p_stdY,
               const T p_meanTheta, const T p_stdTheta);

    Parameters(const Parameters &p_parameters);

    Parameters &operator=(const Parameters &p_parameters);

    Parameters(Parameters &&p_parameters);
    Parameters &operator=(Parameters &&p_parameters);
};

} // namespace Analysis
#endif