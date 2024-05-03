#ifndef POOL_HPP
#define POOL_HPP

#include <type_traits>
#include <stdexcept>
#include <iostream>


template <typename T>

class Pool
{
    public:
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    Pool(
        T p_l,
        T p_r1,
        T p_r2
    );
    ~Pool();
    const T& getL() const;

private:

    const T l;
    const T r1;
    const T r2;
    
};

#endif // POOL_HPP