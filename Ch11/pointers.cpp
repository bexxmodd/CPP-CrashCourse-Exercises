#include "../test_base.h"
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

class IllegalCopy: virtual public std::exception
{
public:
    explicit IllegalCopy(unsigned int err_num, const std::string& msg)
        : err_number(err_num), err_message(msg) {}
    ~IllegalCopy() throw() = default;
    const char* what() const throw() { return err_message.c_str(); }
    unsigned int get_error_num() const throw() { return err_number; }

private:
    unsigned int err_number;
    std::string err_message;
};

template<typename T>
class UniquePtr
{
public:
    UniquePtr() : m_data(nullptr) {}
    UniquePtr(T* data) : m_data(data) {}
    UniquePtr(UniquePtr& rhs) noexcept : m_data(std::move(rhs.m_data))
    {
        rhs.m_data = nullptr;
    }

    ~UniquePtr() = default;

    void operator=(const UniquePtr& rhs)
    {
        throw IllegalCopy(99, "Can't make a copy of a unique pointer");
    }

    bool operator==(const UniquePtr& rhs) const
    {
        return m_data == nullptr && rhs.m_data == nullptr;
    }

    bool operator!=(const UniquePtr& rhs) const
    {
        return m_data != nullptr || rhs.m_data != nullptr;
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }
    
private:
    T* m_data;
};

auto my_deleter = [](int* x) {
    std::cout << "Deleting an in at " << x << std::endl;
    delete x;
};

std::unique_ptr<int, decltype(my_deleter)> shr_ptr { new int, my_deleter };


TEST_CASE("Testing custom UniquePtr Constructor", "[UniquePtr]")
{
    int arr[] = { 1, 2, 3 };
    UniquePtr<int> a { arr };
    UniquePtr<int> b;
    REQUIRE(a != b);

    SECTION("trying to copy throws an exception")
    {
        REQUIRE_THROWS(b = a);
    }

    SECTION("Construct new UniquePtr from old UniquePtr")
    {
        UniquePtr<int> d { a };
        REQUIRE(d != a);
        REQUIRE(a == b);
    }

    SECTION("test [] operator")
    {
        long arr[] = { 99, 66, 0 };
        UniquePtr<long> e { arr };
        REQUIRE(e[0] == 99);

        e[0] = 1;
        REQUIRE(e[0] == 1);
    }
}
