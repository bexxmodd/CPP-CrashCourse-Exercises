#include <iostream>
#include <type_traits>


template<typename N>
concept NumTy = std::is_integral<N>::value 
    && std::is_unsigned<N>::value 
    && std::is_arithmetic<N>::value;

template<typename NumTy>
class PrimeNumberIterator
{
public:
    explicit PrimeNumberIterator(NumTy current);
    bool operator!=(NumTy x) const;
    PrimeNumberIterator& operator++();
    NumTy operator*() const;

private:
    NumTy _current{ 1 };
    bool is_prime(NumTy x);
};


template<typename NumTy>
class PrimeNumbersRange
{
public:
  explicit PrimeNumbersRange(NumTy min, NumTy max);
  [[nodiscard]] PrimeNumberIterator<NumTy> begin() const;
  [[nodiscard]] NumTy end() const;

private:
  const NumTy _min;
  const NumTy _max;
};
