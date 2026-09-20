
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        std::string arg = argv[i];

        if (arg.find_first_not_of("0123456789 ") != std::string::npos)
            throw std::invalid_argument("Error: invalid character found");

        std::stringstream ss(arg);
        std::string token;
        long num;

        while (ss >> token)
        {
            char *end;
            num = std::strtol(token.c_str(), &end, 10);
            if (num < 0)
                throw std::invalid_argument("Error: numbers must be positive");
            if (num > __INT_MAX__)
                throw std::invalid_argument("Error: too large number");

            m_vector.push_back(num);
            m_deque.push_back(num);
        }
        i++;
    }

    if (hasDuplicates(m_vector))
        throw std::invalid_argument("Error: duplicate number found");
}

PmergeMe::PmergeMe(const PmergeMe &copy) : m_vector(copy.m_vector), m_deque(copy.m_deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        m_vector = other.m_vector;
        m_deque = other.m_deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int> &PmergeMe::get_vector()
{
    return m_vector;
}

std::deque<int> &PmergeMe::get_deque()
{
    return m_deque;
}

void PmergeMe::displayData() const
{
    for (std::vector<int>::const_iterator it = m_vector.begin(); it != m_vector.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displayData(std::vector<int> vec) const
{
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << "-";
    }
    std::cout << std::endl;
}

bool PmergeMe::hasDuplicates(std::vector<int> vec)
{
    std::sort(vec.begin(), vec.end());

    if (std::adjacent_find(vec.begin(), vec.end()) != vec.end())
        return true;

    return false;
}

static size_t getJacobsthalSeq(size_t n)
{

    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        size_t result = getJacobsthalSeq(n - 1) + 2 * getJacobsthalSeq(n - 2);
        return result;
    }
}

void PmergeMe::insertVector(std::vector<int> &sorted, int element)
{
    // Standard Binary Search using std::lower_bound
    std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);
    sorted.insert(it, element);
}

void PmergeMe::sortVector(std::vector<int> &sequence)
{
    if (sequence.size() <= 1)
        return;

    bool hasStraggler = (sequence.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler)
    {
        straggler = sequence.back();
        sequence.pop_back();
    }

    std::vector<Pair> pairs;
    std::vector<int> winners;

    size_t i = 0;
    while (i < sequence.size())
    {
        int a = sequence[i];
        int b = sequence[i + 1];
        if (a > b)
        {
            pairs.push_back(Pair(a, b));
            winners.push_back(a);
        }
        else
        {
            pairs.push_back(Pair(b, a));
            winners.push_back(b);
        }
        i = i + 2;
    }

    sortVector(winners);
    // displayData(winners);

    // Unwinding happens here
    std::vector<int> mainChain = winners;
    std::vector<int> pendChain;
    i = 0;
    while (i < mainChain.size())
    {
        size_t j = 0;
        while (j < pairs.size())
        {
            if (pairs[j].winner == mainChain[i])
            {
                pendChain.push_back(pairs[j].loser);
                pairs.erase(pairs.begin() + j);
                break;
            }
            j++;
        }
        i++;
    }

    sequence.clear();
    sequence.push_back(pendChain[0]);
    sequence.insert(sequence.end(), mainChain.begin(), mainChain.end());

    size_t pendIndex = 1;
    size_t jackobSequence = 3;

    while (pendIndex < pendChain.size())
    {

        size_t nextCount = getJacobsthalSeq(jackobSequence) - getJacobsthalSeq(jackobSequence - 1);

        if (nextCount > pendChain.size() - pendIndex)
            nextCount = pendChain.size() - pendIndex;
        size_t i = pendIndex + nextCount;
        while (i > pendIndex)
        {
            insertVector(sequence, pendChain[i - 1]);
            i--;
        }

        pendIndex = pendIndex + nextCount;
        jackobSequence++;
    }

    if (hasStraggler)
        insertVector(sequence, straggler);
}

void PmergeMe::insertDeque(std::deque<int> &sorted, int element)
{
    std::deque<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), element);

    sorted.insert(it, element);
}

void PmergeMe::sortDeque(std::deque<int> &sequence)
{
    if (sequence.size() <= 1)
        return;

    bool hasStraggler = (sequence.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler)
    {
        straggler = sequence.back();
        sequence.pop_back();
    }

    std::deque<Pair> pairs;
    std::deque<int> winners;

    size_t i = 0;
    while (i < sequence.size())
    {
        int a = sequence[i];
        int b = sequence[i + 1];

        if (a > b)
        {
            pairs.push_back(Pair(a, b));
            winners.push_back(a);
        }
        else
        {
            pairs.push_back(Pair(b, a));
            winners.push_back(b);
        }
        i = i + 2;
    }

    sortDeque(winners);

    std::deque<int> mainChain = winners;
    std::deque<int> pendchain;

    i = 0;
    while (i < mainChain.size())
    {
        size_t j = 0;
        while (j < pairs.size())
        {
            if (pairs[j].winner == mainChain[i])
            {
                pendchain.push_back(pairs[j].loser);
                pairs.erase(pairs.begin() + j);
                break;
            }
            j++;
        }
        i++;
    }

    sequence.clear();
    sequence.push_back(pendchain[0]);
    sequence.insert(sequence.end(), mainChain.begin(), mainChain.end());

    size_t pendIndex = 1;
    size_t jackobSequence = 3;
    while (pendIndex < pendchain.size())
    {
        size_t nextCount = getJacobsthalSeq(jackobSequence) - getJacobsthalSeq(jackobSequence - 1);
        if (nextCount > pendchain.size() - pendIndex)
            nextCount = pendchain.size() - pendIndex;

        size_t i = pendIndex + nextCount;
        while (i > pendIndex)
        {
            insertDeque(sequence, pendchain[i - 1]);
            i--;
        }

        pendIndex = pendIndex + nextCount;
        jackobSequence++;
    }

    if (hasStraggler)
        insertDeque(sequence, straggler);
}
