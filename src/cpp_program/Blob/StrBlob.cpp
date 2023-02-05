
#include "StrBlob.h"
using namespace std;

std::string &StrBlob::front()
{
    check(0, "front of empty StrBlob");
    return data->front();
}
std::string &StrBlob::back()
{
    check(0, "back of empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= size())
    {
        throw out_of_range(msg);
    }
}

StrBlob::StrBlob(std::initializer_list<std::string> il) : data(make_shared<vector<string>>(il))
{
}
StrBlob::StrBlob() : data(make_shared<vector<string>>())
{
}

StrBlobPtr::StrBlobPtr(StrBlob &b, std::size_t index) : wptr(b.data), curr(index) {}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const string &msg) const
{
    auto ptr = wptr.lock();
    if (ptr == nullptr)
    {
        throw runtime_error("unbound StrBlobPtr");
    }
    if (i >= ptr->size())
    {
        throw out_of_range(msg);
    }
    return ptr;
}
std::shared_ptr<std::vector<std::string>> StrBlobPtr::get_shared_ptr() const
{
    auto ptr = wptr.lock();
    if (ptr == nullptr)
    {
        throw runtime_error("unbound StrBlobPtr");
    }
    if (curr > ptr->size())
    {
        throw out_of_range("invalid ptr");
    }
    return ptr;
}
std::string &StrBlobPtr::deref() const
{
    auto ptr = check(curr, "index is invalid");
    return (*ptr)[curr];
}
StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment pass end of StrBlobPtr");
    ++curr;
    return *this;
}
