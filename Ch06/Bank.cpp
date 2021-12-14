#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <type_traits>

template<typename N>
concept Numberish = std::is_arithmetic<N>::value;

template<Numberish N, Numberish M>
class Logger
{
public:
    virtual ~Logger() = default;
    virtual void log_transfer(N from, N to, M amount);
};

template<Numberish N, Numberish M>
class ConsoleLogger : public Logger<N, M>
{
public:
    void log_transfer(N from, N to, M amount) override
    {
        std::cout << "[CONS] " << from << " -> " 
                  << to << ": " << amount << std::endl;
    }
};

template<Numberish N, Numberish M>
struct Bank
{
    Bank(Logger<N, M> &logger) : logger(logger) {}
    void make_transfer(N to, N from, M amount)
    {
        logger.log_transfer(from, to, amount);
    }

private:
    Logger<N, M> &logger;
};

int main()
{
    ConsoleLogger<long, double> logger;
    Bank<long, double> bank { logger };
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.00);
}