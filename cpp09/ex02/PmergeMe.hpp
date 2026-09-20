#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

struct Pair
{
    int winner;
    int loser;

    Pair(): winner(0), loser(0) {};
    Pair(int w, int l) : winner(w), loser(l) {};
};


class PmergeMe
{
    private:
        std::vector <int> m_vector;
        std::deque <int> m_deque;

    public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void sortVector(std::vector<int> &sequence);
        void insertVector(std::vector<int> &sorted, int element);

        void insertDeque(std::deque<int> &sorted, int elemnt);
        void sortDeque(std::deque<int> &sequence);

        bool hasDuplicates(std::vector<int> vec);
        void displayData() const;
        void displayData(std::vector<int> vec) const;



        std::deque<int> &get_deque();
        std::vector<int> &get_vector();


};

#endif
