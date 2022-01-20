#include <cstdio>
#include <cstdlib>
#include <memory>
#include <atomic>

// #include "../test_base.h"

class Hal
{
public:
    Hal(std::shared_ptr<FILE> file)
        : m_file(file), count(++m_count) {  }

    Hal(const Hal& other) 
        : m_file(other.m_file), count(++other.m_count) { }

    ~Hal()
    { 
        fprintf(m_file.get(), "Stop, Dave!\n");
        m_count--;
    }

    int write_status()
    {
        return fprintf(m_file.get(),
                "I'm completely operational -> %ld\n",
                count);
    }
    
private:
    std::shared_ptr<FILE> m_file;
    const size_t count;
    static std::atomic<size_t> m_count;
};

std::atomic<size_t> Hal::m_count{};

int main()
{
    auto file = fopen("hal.txt", "a");
    if (!file) return errno;
    fprintf(file, "======= start ======\n");

    std::shared_ptr<FILE> shared_file { file, fclose };
    auto hal1 = Hal(shared_file);
    printf("\tUse Count: %ld\n", shared_file.use_count());
    hal1.write_status();

    auto hal2 = Hal(shared_file);
    hal2.write_status();
    printf("\tUse Count: %ld\n", shared_file.use_count());

    auto hal3 = Hal(shared_file);
    hal3.write_status();
    printf("\tUse Count: %ld\n", shared_file.use_count());

    auto hal4 = Hal(hal1);
    hal4.write_status();
    printf("\tUse Count: %ld\n", shared_file.use_count());

    fprintf(file, "======= end ======\n");
    return 0;
}

