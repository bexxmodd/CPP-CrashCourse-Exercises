#include <iostream>
#include <cstdio>

template<typename T>
concept Bankable = std::is_arithmetic<T>::value;

template<Bankable N, Bankable M>
struct Logger
{
    virtual ~Logger() = default;
    virtual void log_transfer(N from, N to, M amount) = 0;
};

template<Bankable N, Bankable M>
struct ConsoleLogger : Logger<N, M>
{
    void log_transfer(N from, N to, M amount) override
    {
        printf("[cons] %ld -> %ld: %f\n", from, to, amount);
    }
};

template<Bankable N, Bankable M>
struct FileLogger : Logger<N, M>
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

struct Account
{
    long id;
    double balance;

    virtual ~Account() = default;
    friend std::ostream& operator<<(std::ostream& os, const Account& acc);
};

enum AccTy { Savings, Checking };

struct SavingsAccount : Account
{
    AccTy account_type = AccTy::Savings;
};

struct CheckingAccount: Account
{
    AccTy account_type = AccTy::Checking;
};

std::ostream& operator<<(std::ostream& os, const Account& acc)
{
    os << acc.id;
    return os;
}

template<class T>
struct Bank
{
    T account;

    Bank() {};

    Bank(T account_number)
        : account(account_number) {}

    Bank(Logger<long, double> *logger) 
        : _logger{ logger } {}

    ~Bank() = default;

    void set_logger(Logger<long, double> *new_logger)
    {
        _logger = new_logger;
    }

    void make_transfer(long from, long to, double amount)
    {
        if (_logger)
            _logger->log_transfer(from, to, amount);
    }

private:
    Logger<long, double> *_logger{};
};

int main()
{
    ConsoleLogger<long, double> logger;
    SavingsAccount acc1;
    acc1.id = 24;
    Bank bank { acc1 };
    bank.set_logger(&logger);
    bank.make_transfer(1000, 2000, 49.95);
    bank.make_transfer(2000, 4000, 20.00);
    std::cout << "ACCOUNT #" << bank.account << std::endl;

    Bank<CheckingAccount> bank2 { };
    bank2.account.id = 9999;
    bank2.set_logger(&logger);
    bank2.make_transfer(bank2.account.id, bank.account.id, 199.99);
}