#include <iostream>
#include <string>

using std::cout;
using std::endl;

constexpr int GetSize()
{
    return 5;
}

const int MAX_FILES = 20;
const int LIMIT = MAX_FILES + 1;
int g_staffSize = 27;
const int sz = GetSize();

typedef int *PtrToInt;
using PInt = int *;
int main()
{
    // test for constexpr
    constexpr int mf = 20;
    constexpr int limit = mf + 1;
    constexpr int sz = GetSize();
    int i = 0;

    // const 是底层const， p为指向常量的指针
    const int *p = nullptr;

    // constexpr 修饰的是顶层const，q是常量指针
    constexpr int *q = &g_staffSize;
    *q = 100;
    p = &i;
    cout<<"constexpr: " << *p << ',' << *q << endl;

    // text for typedef, using, decltype and auto
    int &j = i;
    // using 和 typedef的语义是相同的，
    // PtrToInt和PInt都是int*类型，他们前面的const也是顶层const
    // 而不是替换结果 const int * 这种底层const
    const PtrToInt m = &i;
    const PInt n = &i;

    *m = 5;
    *n = 6;
    auto m2 = m; // auto 会忽略顶层const和&
    const int *n2 = n;
    auto m3 = n2;
    // 因为auto不忽略底层const，所以下面的表达式有误
    // *m3 = 4;

    // decltype 不会忽略顶层const，而且还倾向于获得引用
    decltype(n2) m4= n2;
    decltype(n) m5 = n;

    m4 = n;

    m2 = n;
    *m2 = 100;
    cout <<"using and typedef: "<< *m << ',' << *n << endl;
    return 0;
}