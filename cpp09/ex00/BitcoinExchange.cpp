#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : db(other.db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        db = other.db;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase()
{
    std::ifstream file("data.csv");

    if (!file.is_open())
    {
        std::cerr << "Error opening database file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date;
        std::string rateStr;
        if (std::getline(ss, date, ',')
            && std::getline(ss, rateStr))
        {
            double rate;
            std::stringstream convert(rateStr);
            if (!(convert >> rate))
            {
                std::cerr << "Invalid rate in database: "
                          << rateStr
                          << std::endl;
                continue;
            }
            db[date] = rate;
        }
    }
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line ))
    {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        if (!(std::getline(ss, date, '|')
        && std::getline(ss, valueStr)))
            {
                std::cerr << "Error: bad input => "
                        << line
                        << std::endl;
                continue;
            }
            date = trim(date);
            valueStr = trim(valueStr);
            if (!isValidDate(date))
            {
                std::cerr << "Error: bad input => "
                        << line
                        << std::endl;
                continue;
            }
            if (!isValidValue(valueStr))
            {
                std::cerr << "Error: bad input => "
                        << line
                        << std::endl;
                continue;
            }
            //
            double value;
            std::stringstream convert(valueStr);
            if (!(convert >> value))
            {
                std::cerr << "Error: bad input => "
              << line
              << std::endl;
                continue;
            }
            if (value < 0)
            {
                std::cerr << "Error: not a positive number."
                        << std::endl;
                continue;
            }
            if (value > 1000)
            {
                std::cerr << "Error: too large a number."
                        << std::endl;
                continue;
            }
            double rate = getRate(date);
            std::cout << date << " => " << value << " = "
                      << value * rate
                      << std::endl;
        }
}

double BitcoinExchange::getRate(const std::string& date)
{
    std::map<std::string, double>::iterator it = db.find(date);
    if(it != db.end())
        return it->second;
    std::map<std::string, double>::iterator lower = db.lower_bound(date);
    if(lower == db.begin())
    {
        return lower->second;
    }
    else
    {
        --lower;
        return lower->second;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    // length
    if (date.length() != 10)
        return false;

    // '-' positions
    if (date[4] != '-' || date[7] != '-')
        return false;
    // digits

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    // extract year/month/day
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    // month check
    if (month < 1 || month > 12)
        return false;

    // leap year check
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    // day check
    int daysInMonth;
    switch (month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            daysInMonth = isLeapYear ? 29 : 28;
            break;
        default:
            return false;
    }

    if (day < 1 || day > daysInMonth)
        return false;

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value)
{
    if (value.empty())
        return false;

    double valuestr;
    std::stringstream ss(value);

    if (!(ss >> valuestr))
        return false;

    char extra;
    if (ss >> extra)
        return false;

    return true;
}

std::string BitcoinExchange::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}
