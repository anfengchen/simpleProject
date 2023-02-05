#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

class StrBlob;
class StrBlobPtr
{
private:
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr; // 当前位置
    std::shared_ptr<std::vector<std::string>> check(std::size_t i, const std::string &msg) const;
    std::shared_ptr<std::vector<std::string>> get_shared_ptr() const;

public:
    StrBlobPtr(StrBlob &b, std::size_t index = 0);
    StrBlobPtr() : curr(0) {}
    ~StrBlobPtr() = default;
    std::size_t get_curr() const
    {
        return curr;
    }
    std::string &deref() const;
    StrBlobPtr &incr();
    StrBlobPtr &operator++() // 前置
    {
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }
    StrBlobPtr &operator--()
    {
        check(curr - 1, "decrement pass begin of StrBlobPtr");
        --curr;
        return *this;
    }
    StrBlobPtr operator++(int) // 后置
    {
        auto ret = *this;
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return ret;
    }
    StrBlobPtr operator--(int)
    {
        auto ret = *this;
        check(curr - 1, "decrement pass begin of StrBlobPtr");
        --curr;
        return ret;
    }
    bool operator<(const StrBlobPtr &rhs)
    {
        auto lptr = get_shared_ptr();
        auto rptr = rhs.get_shared_ptr();
        if (*lptr != *rptr)
        {
            throw std::runtime_error("ptr compared belong to deferent container");
        }
        return get_curr() < rhs.get_curr();
    }
};
class StrBlob
{
public:
    friend class StrBlobPtr;
    using size_type = std::vector<std::string>::size_type;
    StrBlob(std::initializer_list<std::string> il);
    StrBlob();
    ~StrBlob() = default;
    size_type size() const { return data->size(); }
    bool empty() { return data->empty(); }

    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string &front();
    std::string &back();
    StrBlobPtr begin()
    {
        return StrBlobPtr(*this, 0);
    }
    StrBlobPtr end()
    {
        return StrBlobPtr(*this, size());
    }

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};
