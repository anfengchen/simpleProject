#include "max_sub_sum.h"

using std::vector;

int MaxSubSum(const vector<int> &vec)
{
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