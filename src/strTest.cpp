#include <cctype>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int main()
{
    string line;
    string artical;
    while (getline(cin, line))
    {
        if (!line.empty())
        {
            artical += line + "\n";
            // cout << line << endl;
        }
    }
    decltype(artical.size()) wordCnt = artical.empty()? 0:1;
    for (auto c : artical)
    {
        if (std::isspace(c))
        {
            wordCnt++;
        }
    }

    cout << "worldNum: " << wordCnt << endl;

    const string s="Hello World!";
    for(auto &c:s){

        cout<< static_cast<char>(std::toupper(c));
    }
    cout << endl;
    return 0;
}