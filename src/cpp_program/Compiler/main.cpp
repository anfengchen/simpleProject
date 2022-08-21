#include "max_sub_sum.h"
#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;
int main()
{
    Rand_int RandomIntGenerator(-40, 100);
    vector<int> vec;
    for (auto i = 0; i < 1000; ++i)
    {
        vec.push_back(RandomIntGenerator());
    }
    int max = 0;
    auto t0 = high_resolution_clock::now();
    for (auto i = 0; i < 100; ++i)
    {
        max = MaxSubSum(vec);
    }
    auto t1 = high_resolution_clock::now();
    cout << "max = " << max << '\n';
    cout << "calculate duration: " << duration_cast<milliseconds>(t1 - t0).count() << "msec\n";
}
