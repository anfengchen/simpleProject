#include "max_sub_sum.h"
using std::vector;
int MaxSubSum(const vector<int> &vec)
{
    int max = 0;
    int sum = 0;
    for (auto elem : vec)
    {
        sum += elem;
        if (sum > max)
        {
            max = sum;
        }
        if (sum < 0)
        {
            sum = 0;
        }
    }
    return max;
}