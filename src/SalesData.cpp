#include "SalesData.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int read(SalesData &data);
int write(const SalesData &data);
int add(const SalesData &lhs, const SalesData &rhs);

int main()
{
    SalesData data1, data2;
    read(data1);
    read(data2);
    write(data1);
    write(data2);
    add(data1,data2);
    return 0;
}

int read(SalesData &data)
{
    double price = 0;
    cin >> data.bookNo >> data.unitsSold >> price;
    data.revenue = data.unitsSold * price;
    return 0;
}

int write(const SalesData &data)
{
    cout << data.bookNo << ": " << data.unitsSold << ' ' << data.revenue << '\n';
    return 0;
}

int add(const SalesData &lhs, const SalesData &rhs)
{
    if (lhs.bookNo == rhs.bookNo)
    {
        unsigned totalCnt = lhs.unitsSold + rhs.unitsSold;
        double totalRevenue = lhs.revenue + rhs.revenue;
        cout << lhs.bookNo << ' ' << totalCnt << ' ' << totalRevenue << ' ';
        if (totalCnt != 0)
        {
            cout << totalRevenue / totalCnt << endl;
        }
        else
        {
            cout << "(no sales)" << endl;
        }
        return 0;
    }
    else
    {
        std::cerr << "Data must refer to same ISBN" << endl;
        return -1;
    }
}