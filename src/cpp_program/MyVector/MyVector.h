#include "MyBaseVector.h"
#include <new>
template <class T>
T *uninitialized_move(T *srcB, T *srcE, T *dstB)
{

    for (auto b = srcB; b != srcE; ++b, ++dstB)
    {
        std::new (static_cast<void *>(&*dstB)) T{move(*b)};
        b->~T();
    }
    return srcB;
}
template <class T>
class MyVector
{
private:
    MyBaseVector<T> vb;
    void destroy_elements()
    {
        for (auto p = vb.elem; p != vb.space; ++p)
        {
            p->~T();
        }
        vb.space = vb.elem;
    }

public:
    using size_type = unsigned int;
    explicit MyVector(size_type n, const T &val = T()) : vb(n)
    {
        uninitialized_fill(vb.elem, vb.elem + n, val);
        vb.space = vb.elem + n;
    }
    MyVector(const MyVector &other) : vb(other.size())
    {
        uninitialized_copy(other.begin(), other.end(), vb.elem);
        vb.space = vb.elem + other.size();
    }
    MyVector &operator=(const MyVector &other)
    {
        MyVector<T> b(other);
        destroy_elements();
        swap(vb, b);
        return *this;
    }
    MyVector(MyVector &&other) : vb{std::move(other)}
    {
    }
    MyVector &operator=(MyVector &&other)
    {
        destroy_elements();
        std::swap(*this, other);
    }
    ~MyVector()
    {
        destroy_elements();
    }

    size_type size() const { return vb.end() - vb.begin(); }
    size_type capacity() const { return vb.last - vb.elem; }
    void reserve(size_type n)
    {
        if (n <= capacity())
        {
            return;
        }
        MyBaseVector<T> b(n);
        b.space = b.elem + size();
        vb.space = uninitialized_move(begin(), end(), b.elem);
        swap(b, *this);
    }
    void resize(size_type n, const T &val = {})
    {
        reserve(n);
        if (n > size())
        {
            uninitialized_fill_n(end(), n - size(), val);
        }
        else
        {
            for (auto b = begin() + n; b != end(); ++b)
            {
                b->~T();
            }
        }
        vb.space = vb.elem + size();
    }
    void clear() { resize(0); }
    T *begin() const { return vb.elem; }
    T *end() const { return vb.space; }
    void push_back(const T &val)
    {
        auto sz = size();
        if (capacity() == sz)
        {
            reserve(sz ? 2 * sz : 8);
        }
        vb.alloc.construct(elem + sz, val);
        ++vb.space;
    }
    size_type pop()
    {
        --vb.space;
        vb.space->~T();
    }

private:
    void destroy(T *b, T *e)
    {
        for (auto iter = b; iter != e; ++iter)
        {
            iter->~T();
        }
    }
};