#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

class BitcoinExchange {
  private:
    std::map<std::string, double> db;
  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase();
    void processInput(const std::string& filename);
    bool isValidDate(const std::string& date);
    bool isValidValue(const std::string& value);
    double getRate(const std::string& date);
    std::string trim(const std::string& str);
};

#endif
