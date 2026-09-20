
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "ta dkhel shi 5 dnwamer\n";
        return 0;
    }

    try
    {
        PmergeMe A(argc, argv);

        std::cout << "Befor:\t";
        A.displayData();

        std::vector<int> &S1 = A.get_vector();
        std::deque<int> &S2 = A.get_deque();

        clock_t startVec = clock();
        A.sortVector(S1);
        clock_t endVec = clock();

        double timeVec = double(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

        clock_t startDeq = clock();
        A.sortDeque(S2);
        clock_t endDeq = clock();
        double timeDeq = double(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;

        std::cout << "After:\t";
        A.displayData();

        std::cout << "Time to process a range of " << S1.size() << " elements with std::vector : "
                  << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;

        std::cout << "Time to process a range of " << S2.size()
                  << " elements with std::deque  : " << std::fixed << std::setprecision(5) << timeDeq << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
