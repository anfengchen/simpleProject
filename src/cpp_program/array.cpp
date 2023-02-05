#include <istream>
using namespace std;
void copy_fct();
void print();
void increment();
void copy_fct()
{
    int v1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v2[10];
    for (auto i = 0; i != 10; ++i)
    {
        v2[i] = v1[i];
    }
}

void increment()
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &x : v)
    {
        ++x;
    }
}

void print()
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto x : v)
    {
        cout << x << '\n';
    }
}