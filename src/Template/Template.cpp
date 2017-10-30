#include <cwchar>
#include <iostream>

using std::wcout;
using std::endl;

template <typename T>
void
Fun(T v)
{
    wcout << L"Fun - general " << v << endl;
}

template <typename T>
void
Fun(T* p)
{
    wcout << L"Fun - partial specialized for pointer " << *p << endl;
}

void
Fun(int i)
{
    wcout << L"Fun_int " << i << endl;
}

template <typename T>
class A
{
public:
    A():_v(0) {}
    A(const T &v):_v(v) {}
    template <typename U>
    A(const A<U> &u)
    {
        _v = static_cast<T>(u.getVal());
        wcout << L"Member template ctor " << _v << endl;
    }
    T getVal() const
    {
        return _v;
    }
private:
    T   _v;
};

template <typename T>
class A<T*>
{
public:
    A():_v(0) {}
    A(const T* p)
    {
        _v = new T;
        *_v = *p;
        wcout << L"A<T*>::ctor " << *_v << endl;
    }
    A(const A<T> &a)
    {
        _v = new T;
        *_v = a.getVal();
        wcout << L"A<T*>::ctor(A<T>) " << *_v << endl;
    }
    A(const A &a)
    {
        _v = new T;
        *_v = *a._v;
        wcout << L"A<T*>::copy ctor " << *_v << endl;
    }
    template <typename U>
    A(const A<U*> &u)
    {
        _v = new T;
        *_v = static_cast<T>(*(u.getVal()));
        wcout << L"Member template ctor(A<U*>) of A<T*> " << *_v << endl;
    }
    template <typename U>
    A(const A<U> &u)
    {
        _v = new T;
        *_v = static_cast<T>(u.getVal());
        wcout << L"Member template ctor(A<U>) of A<T*> " << *_v << endl;
    }
    T* getVal() const
    {
        return _v;
    }
    ~A()
    {
        delete _v;
    }
private:
    T   *_v;
};

int
main()
{
    // Function template
    {
        char    c = 'c';
        Fun(c);
        Fun(1);
        Fun(&c);
    }
    // Class template
    {
        A<int>  a(1);
        A<char> c(a);
        A<int>  b = a;

        int i = 2;
        A<int*> d(&i);
        A<int*> e(a);
        A<int*> f(d);
        A<int*> g(c);
        A<char*>    h(d);
    }
}
