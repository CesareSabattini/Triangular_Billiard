#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <type_traits>

template <typename T> struct Results {
  static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
  T meanY;
  T meanTheta;
  T stdY;
  T stdTheta;
  Results() : meanY(0), meanTheta(0), stdY(0), stdTheta(0) {}
  Results(T p_meanY, T p_meanTheta, T p_stdY, T p_stdTheta)
      : meanY(p_meanY), meanTheta(p_meanTheta), stdY(p_stdY),
        stdTheta(p_stdTheta) {}
  Results(const Results &p_results)
      : meanY(p_results.meanY), meanTheta(p_results.meanTheta),
        stdY(p_results.stdY), stdTheta(p_results.stdTheta) {}
  Results &operator=(const Results &p_results) {
    meanY = p_results.meanY;
    meanTheta = p_results.meanTheta;
    stdY = p_results.stdY;
    stdTheta = p_results.stdTheta;
    return *this;
  }
  Results(Results &&p_results)
      : meanY(p_results.meanY), meanTheta(p_results.meanTheta),
        stdY(p_results.stdY), stdTheta(p_results.stdTheta) {}
  Results &operator=(Results &&p_results) {
    meanY = p_results.meanY;
    meanTheta = p_results.meanTheta;
    stdY = p_results.stdY;
    stdTheta = p_results.stdTheta;
    return *this;
  }
  ~Results() {}
};

#endif