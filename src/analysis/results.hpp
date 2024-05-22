#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <type_traits>

template <typename T> struct Results {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    T meanY;
    T meanTheta;
    T stdY;
    T stdTheta;
    T skewnessY;
    T skewnessTheta;
    T kurtosisY;
    T kurtosisTheta;
    Results()
        : meanY(0), meanTheta(0), stdY(0), stdTheta(0), skewnessY(0),
          skewnessTheta(0), kurtosisY(0), kurtosisTheta(0) {}
    Results(const T p_meanY, const T p_meanTheta, const T p_stdY,
            const T p_stdTheta, const T p_skewnessY, const T p_skewnessTheta,
            const T p_kurtosisY, const T p_kurtosisTheta)
        : meanY(p_meanY), meanTheta(p_meanTheta), stdY(p_stdY),
          stdTheta(p_stdTheta), skewnessY(p_skewnessY),
          skewnessTheta(p_skewnessTheta), kurtosisY(p_kurtosisY),
          kurtosisTheta(p_kurtosisTheta) {}
    Results(const Results &p_results)
        : meanY(p_results.meanY), meanTheta(p_results.meanTheta),
          stdY(p_results.stdY), stdTheta(p_results.stdTheta),
          skewnessY(p_results.skewnessY),
          skewnessTheta(p_results.skewnessTheta),
          kurtosisY(p_results.kurtosisY),
          kurtosisTheta(p_results.kurtosisTheta) {}
    Results &operator=(const Results &p_results) {
        meanY = p_results.meanY;
        meanTheta = p_results.meanTheta;
        stdY = p_results.stdY;
        stdTheta = p_results.stdTheta;
        skewnessY = p_results.skewnessY;
        skewnessTheta = p_results.skewnessTheta;
        kurtosisY = p_results.kurtosisY;
        kurtosisTheta = p_results.kurtosisTheta;
        return *this;
    }
    Results(Results &&p_results)
        : meanY(p_results.meanY), meanTheta(p_results.meanTheta),
          stdY(p_results.stdY), stdTheta(p_results.stdTheta),
          skewnessY(p_results.skewnessY),
          skewnessTheta(p_results.skewnessTheta),
          kurtosisY(p_results.kurtosisY),
          kurtosisTheta(p_results.kurtosisTheta) {}
    Results &operator=(Results &&p_results) {
        meanY = p_results.meanY;
        meanTheta = p_results.meanTheta;
        stdY = p_results.stdY;
        stdTheta = p_results.stdTheta;
        skewnessY = p_results.skewnessY;
        skewnessTheta = p_results.skewnessTheta;
        kurtosisY = p_results.kurtosisY;
        kurtosisTheta = p_results.kurtosisTheta;
        return *this;
    }
    ~Results() {}
};

#endif