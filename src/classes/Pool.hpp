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

    Pool(const Pool& p_pool);
    Pool& operator=(const Pool& p_pool);
    Pool(Pool&& p_pool);
    Pool& operator=(Pool&& p_pool);

    ~Pool();
    const T& getL() const;
    const T& getR1() const;
    const T& getR2() const;
    


private:

     T l;
     T r1;
     T r2;
    
};

#endif // POOL_HPP