#include "task.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void print_safe_queue(Safe_queue<string> &que)
{
    cout << "safe_queue size: " << que.size() << endl;
    for (size_t i = 0; !que.empty(); i++)
    {
        printf("\telem[%lu] = %s\n", i, que.pop()->c_str());
    }
}
int main()
{
    Safe_queue<string> str_que;
    for (size_t i = 0; i < 10; i++)
    {
        str_que.push("hello");
    }

    Safe_queue<string> str_que_other(std::move(str_que));

    cout << "str_que: " << endl;
    print_safe_queue(str_que);
    cout << "str_que_other: " << endl;
    print_safe_queue(str_que_other);
    return 0;
}
