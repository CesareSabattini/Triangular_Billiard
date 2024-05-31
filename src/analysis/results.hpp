#ifndef RESULTS_HPP
#define RESULTS_HPP

#include "../utils/concept.hpp"
#include <type_traits>

namespace Analysis {

template <typename T>

requires DoubleOrFloat<T>

struct Results {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    int outputSize;
    T meanY;
    T meanTheta;
    T stdY;
    T stdTheta;
    T skewnessY;
    T skewnessTheta;
    T kurtosisY;
    T kurtosisTheta;
    Results();
    Results(const int outputSize, const T p_meanY, const T p_meanTheta,
            const T p_stdY, const T p_stdTheta, const T p_skewnessY,
            const T p_skewnessTheta, const T p_kurtosisY,
            const T p_kurtosisTheta);
    Results(const Results &p_results);
    Results &operator=(const Results &p_results);
    Results(Results &&p_results);
    Results &operator=(Results &&p_results);
    ~Results();
};
} // namespace Analysis
#endif