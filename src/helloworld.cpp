#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
class Str
{
private:
public:
    string str;
    Str(string s);
    Str(const Str &sObj);
    ~Str();
};

Str::Str(string s) : str(s)
{
    cout << "Init\n";
}
Str::Str(const Str &sObj)
{
    str = sObj.str;
    cout << "Copy\n";
}

Str::~Str()
{
}

int main()
{
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    Str s = string("hello");
    Str st = s;
    for (const string &word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
    return 0;
}
