#include "StrBlob.h"
#include <iostream>
using namespace std;
int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b1.push_back("about");
        cout << "size:" << b2.size() << endl;
    }
    cout << "size2:" << b1.size() << endl;
    int i = 0;
    for (auto ptr = b1.begin(); ptr < b1.end(); ++ptr, ++i)
    {
        cout << "b1[" << i << "]=" << ptr.deref() << endl;
    }
    return 0;
}