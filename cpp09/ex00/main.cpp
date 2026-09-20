#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
  if(ac != 2)
  {
    std::cerr << "Usage: " << av[0] << " <input_file>" << std::endl;
    return 1;
  }

  BitcoinExchange btc;
  btc.loadDatabase();
  btc.processInput(av[1]);
  return 0;
}
