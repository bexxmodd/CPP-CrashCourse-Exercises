#include <iostream>

#include "../catch.hpp"

#include "Primes.h"

template<typename NumTy>
PrimeNumberIterator<NumTy>::PrimeNumberIterator(NumTy current)
    : _current(current) {}

template<typename NumTy>
bool PrimeNumberIterator<NumTy>::operator!=(NumTy x) const
{
    return x >= _current;
}

template<typename NumTy>
PrimeNumberIterator<NumTy>& PrimeNumberIterator<NumTy>::operator++()
{
    NumTy tmp = _current;
    while (!is_prime(++tmp))
        ;
    _current = tmp;
    return *this;
}

template<typename NumTy>
NumTy PrimeNumberIterator<NumTy>::operator*() const
{
    return _current;
}

template<typename NumTy>
bool PrimeNumberIterator<NumTy>::is_prime(NumTy x)
{
    if (x % 2 == 0 || x % 3 == 0)
        return false;

    for (int i = 2; i * i < x; i = i + 6)
    {
        if (x % i == 0 || x % (i+2) == 0)
            return false;
    }
    return true;
}

template<typename NumTy>
PrimeNumbersRange<NumTy>::PrimeNumbersRange(NumTy min, NumTy max)
    : _min(min), _max(max) {}

template<typename NumTy>
[[nodiscard]] PrimeNumberIterator<NumTy> PrimeNumbersRange<NumTy>::begin() const
{
    return PrimeNumberIterator<NumTy>{ _min };
}

template<typename NumTy>
[[nodiscard]] NumTy PrimeNumbersRange<NumTy>::end() const { return _max; }

int main(int argc, char **argv)
{
    // if (argc < 2)
    //     std::cout << "Please provide m"
    for (const auto i : PrimeNumbersRange<short>{ 9, 50})
        std::cout << i << ", ";
    std::cout << std::endl;
    return 0;
}
