#include <iostream>
#include <cstdio>
#include <random>

struct Logger {
	virtual ~Logger() = default;
	virtual void log_transfer(long from, long to, double amount, const char *note) = 0;
};

struct ConsoleLogger : Logger {
	void log_transfer(long from, long to, double amount, const char *note) override
	{
		printf("[cons] %ld -> %ld: %f || %s\n", from, to, amount, note);
	}
};

struct FileLogger : Logger {
	void log_transfer(long from, long to, double amount, const char *note) override
	{
		printf("[file] %ld,%ld,%f || %s\n", from, to, amount, note);
	}
};

struct AccountDatabase {
	virtual ~AccountDatabase() = default;
	virtual void set_amount(long id, double amount)=0;
	virtual void retrieve(long id, double amount)=0;
};

struct InMemoryAccountDatabase : AccountDatabase {
	void set_amount(long id, double amount) override
	{
		std::cout << "You have successfully deposited: $" << amount
				  << " to the account #" << id << std::endl;
	}

	void retrieve(long id, double amount) override
	{
		std::cout << "Retrieved: $" << amount
				  << " from account #" << id << std::endl;
	}
};

struct Bank {
	static int current_id;

	Bank(Logger* logger, AccountDatabase* acc_db)
		: id(current_id++), logger{ logger }, accDb{ acc_db } {}

	void set_logger(Logger* new_logger)
	{
				logger = new_logger;
	}
	void make_transfer(long from, long to, double amount)
	{
		char note[] = "I'm a note!";
		if (logger) logger->log_transfer(from, to, amount, note);
	}

	void set_amount(double amount)
	{
		accDb->set_amount(id, amount);
	}

	void retrieve(double amount)
	{
		accDb->retrieve(id, amount);
	}

private:
	long id;
	Logger* logger;
	AccountDatabase* accDb;
};

int Bank::current_id = 1;

int main() {
	ConsoleLogger logger;
	InMemoryAccountDatabase db;
	Bank bank5 { &logger, &db };
	Bank bank4 { &logger, &db };
	Bank bank3 { &logger, &db };
	Bank bank { &logger, &db };
	bank.set_amount(60.35);
	bank.retrieve(112.11);
	bank.make_transfer(1, 33, 343.21);
	return 0;
}
