#ifndef MAX_SUB_SUM_H__
#define MAX_SUB_SUM_H__
#include <random>
#include <vector>

class Rand_int
{
public:
    Rand_int(int low, int high) : dist{low, high} {}
    int operator()() { return dist(re); }

private:
    std::default_random_engine re;
    std::uniform_int_distribution<> dist;
};
int MaxSubSum(const std::vector<int> &vec);

#endif