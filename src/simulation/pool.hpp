#ifndef POOL_HPP
#define POOL_HPP

#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace simulation::components {

template <typename T>

class Pool {
  public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

    Pool();
    Pool(const T p_l, const T p_r1, const T p_r2);

    Pool(const Pool &p_pool);
    Pool &operator=(const Pool &p_pool);
    Pool(Pool &&p_pool);
    Pool &operator=(Pool &&p_pool);

    ~Pool();
    const T &getL() const;
    const T &getR1() const;
    const T &getR2() const;

    void setL(const T &p_l);
    void setRs(const T &p_r1, const T &p_r2);

  private:
    T l;
    T r1;
    T r2;
};

} // namespace simulation::components

#endif // POOL_HPP