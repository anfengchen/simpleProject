#include "max_sub_sum.h"
#include <iostream>
using std::vector;
int count;
int MaxSubSum(const vector<int> &vec)
{
    if (count++ == 0)
    {
        std::cout << "O(n2) MaxSubSum run\n";
    }
    int max = 0;
    for (auto i = 0; i < vec.size(); ++i)
    {
        int sum = 0;
        for (auto j = i; j < vec.size(); ++j)
        {
            sum += vec[j];
            if (sum > max)
            {
                max = sum;
            }
        }
    }
    return max;
}