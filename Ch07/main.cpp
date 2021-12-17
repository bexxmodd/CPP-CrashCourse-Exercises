#include <ostream>
#include <iostream>
#include <cstdint>

class UnsignedBigInt
{
private:
    uint32_t __data;

public:
    UnsignedBigInt() = default;

    UnsignedBigInt(uint32_t&& value) 
        : __data(value) {}

    UnsignedBigInt operator+(int other) const
    {
        auto result = __data + other;
        if (result < other)
            throw std::runtime_error("Overflow occurred");
        return result;
    }

    UnsignedBigInt operator-(UnsignedBigInt other) const
    {
        auto result = __data - other.__data;
        if (result < other.__data)
            throw std::runtime_error("Overflow occurred");
        return result;
    }

    operator int() const
    {
        return __data;
    }

    operator long() const
    {
        return __data;
    }

    friend std::ostream& operator<<(std::ostream& os, UnsignedBigInt& num)
    {
        os << +num.__data;
        return os;
    }
};


int main()
{
    UnsignedBigInt big { 0xff800 };
    std::cout << 0xff800 << std::endl;
    std::cout << big << std::endl;
    UnsignedBigInt summed = big + 200;
    std::cout << "Summed: " << summed << std::endl;
    int upped = summed + 33;
    std::cout << "Updated: " << upped << std::endl;

    UnsignedBigInt leftover = summed - UnsignedBigInt{ 5 };
    std::cout << "Leftover: " << leftover << std::endl;

    int converted = leftover;
    long a = leftover;
}
