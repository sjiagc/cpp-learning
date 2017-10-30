#include <iostream>

using std::wcout;
using std::endl;

class true_type
{
};

class false_type
{
};

template<typename T>
struct op_traits
{
    typedef typename T::has_add has_add;
};

template<>
struct op_traits<int>
{
    typedef true_type   has_add;
};

template<>
struct op_traits<float>
{
    typedef true_type   has_add;
};

class object
{
public:
    typedef false_type  has_add;
};

class A: public object
{
public:
    typedef true_type   has_add;
    A operator+(const A& arg) const
    {
        A   res;
        res._a = _a + arg._a;
        return res;
    }
private:
    int _a;
};

class B: public object
{
};

template<typename T>
T
Add_aux(const T& a, const T& b, true_type)
{
    wcout << L"Use operator +" << endl;
    return a + b;
}

template<typename T>
T
Add_aux(const T& a, const T& b, false_type)
{
    wcout << L"Can not add" << endl;
    return T();
}

template<typename T>
T
Add(const T& a, const T& b)
{
    return Add_aux(a, b, op_traits<T>::has_add());
}

int
main()
{
    Add(1, 1);
    A   a, b;
    Add(a, b);
    B   c, d;
    Add(c, d);
}
