#include "replace.hpp"

int main(int ac, char **av)
{
    if( ac != 4)
    {
        std::cout << "Usage: ./replace <filename> <string_to_find> <string_to_replace>" << std::endl;
        return 1;
    }
    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];
    std::ifstream inputFile(filename.c_str());
    if (!inputFile)
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    std::string content;
    std::string line;
    while (std::getline(inputFile, line))
    {
        content += line + "\n";
    }
    inputFile.close();
    size_t pos = 0;
    while ((pos = content.find(s1, pos)) != std::string::npos)
    {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }
    filename += ".replace";
    std::ofstream outputFile(filename.c_str());
    if (!outputFile)
    {
        std::cout << "Error: Could not create output file " << filename + ".replace" << std::endl;
        return 1;
    }
    outputFile << content;
    outputFile.close();
    return 0;
}
