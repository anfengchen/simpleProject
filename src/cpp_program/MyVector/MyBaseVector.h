#include <memory>

template <class T>
struct MyBaseVector
{

    T *elem;
    T *space;
    T *last;
    std::allocator<T> alloc;

    using size_type = std::allocator<T>::size_type;
    explicit MyBaseVector(size_type n) : elem(alloc.allocate(n)), space(elem), last(elem + n)
    {
    }
    MyBaseVector(const MyBaseVector &v) = delete;
    MyBaseVector &operator=(const MyBaseVector &v) = delete;
    MyBaseVector(MyBaseVector &&other) : elem(other.elem), space(other.space), last(other.last)
    {
        other.elem = other.space = other.last = nullptr;
    }
    MyBaseVector &operator=(MyBaseVector &&other)
    {
        std::swap(*this, other);
        return *this;
    }
    ~MyBaseVector() { alloc.deallocate(elem, last - elem); }

    // size_type size() const { return space - elem; }
    // size_type capacity() const { return last - elem; }
    // void reserve(size_type n);
    // void resize(size_type n, const T &val = {});

    // void push_back(const T &val);
    // size_type pop();
};