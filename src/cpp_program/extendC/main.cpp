#include "types.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "sizeof(bool) = " << sizeof(bool) << "; alignof(bool)" << alignof(bool) << '\n';
    cout << "cpp: sizeof(Type_Cpp_t) = " << sizeof(Type_Cpp_t) << "align: " << alignof(Type_Cpp_t) << '\n';
    cout << "cpp: sizeof(Type_C_t) = " << sizeof(Type_C_t) << "align: " << alignof(Type_C_t) << '\n';
    Type_C_t x{true, 2};
    auto p = &x;
    auto pc = reinterpret_cast<char *>(p);
    for (int i = 0; i < sizeof(Type_C_t); ++i)
    {
        cout << static_cast<int>(*(pc + i)) << "; ";
    }
    cout << endl;
    return 0;
}