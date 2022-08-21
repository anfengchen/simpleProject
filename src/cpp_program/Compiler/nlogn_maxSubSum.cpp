#include "max_sub_sum.h"

using std::vector;

int MaxSubSum(const vector<int> &vec)
{
    if (vec.size() == 0)
        return 0;
    if (vec.size() == 1)
        return vec[0];

    int mid = vec.size() / 2;

    vector<int> firstPart(vec.begin(), vec.begin() + mid);
    auto secondPart = vector<int>(vec.begin() + mid, vec.end());

    auto firstMax = MaxSubSum(firstPart);
    auto secondMax = MaxSubSum(secondPart);
    auto max = firstMax > secondMax ? firstMax : secondMax;

    auto maxFirstSum = 0;
    auto maxSecondSum = 0;
    auto sum = 0;
    auto iter = firstPart.crbegin();
    while (iter != firstPart.crend())
    {
        sum += *iter++;
        if (sum > maxFirstSum)
        {
            maxFirstSum = sum;
        }
    }

    sum = 0;
    auto iterSecond = secondPart.cbegin();
    while (iterSecond != secondPart.cend())
    {
        sum += *iterSecond++;
        if (sum > maxSecondSum)
        {
            maxSecondSum = sum;
        }
    }
    return (maxFirstSum + maxSecondSum) > max ? (maxFirstSum + maxSecondSum) : max;
}