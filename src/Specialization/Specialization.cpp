#include <iostream>

using std::wcout;
using std::endl;

// Class template ///////////////////////////////////////////
template<typename T1, typename T2>
class A
{
public:
    A(){wcout << L"General A ctor" << endl;}
};

template<typename T>
class A<T, int>
{
public:
    A(){wcout << L"A<T, int> ctor" << endl;}
};

template<typename T1, typename T2>
class A<T1*, T2*>
{
public:
    A(){wcout << L"A<T1*, T2*> ctor" << endl;}
};

template<>
class A<void*, void*>
{
public:
    A(){wcout << L"A<void*, void*> ctor" << endl;}
};

// Should put the partial specialization for pointers here

void
Fun()
{
    A<int, float>   a_int_float;
    A<int, int>     a_2_int;
    A<int*, float*> a_int_p_float_p;
    A<void*, void*> a_2_void_p;
    A<int*, int*>   a_2_int_p;
}

// Putting specialization here has no effect. g++ will complain an error
template<typename T>
class A<T*, T*>
{
public:
    A(){wcout << L"A<T*, T*> ctor" << endl;}
};

// Function template /////////////////////////////////////////
template<typename T1, typename T2>
void
fun(T1 a, T2 b)
{
    wcout << L"General fun" << endl;
}
template<typename T>
void
fun(T a, int b)
{
    wcout << L"fun<T, int>" << endl;
}

template<typename T>
void
fun(T a, T b)
{
    wcout << L"fun<T, T>" << endl;
}

template<typename T1, typename T2>
void
fun(T1 *a, T2 *b)
{
    wcout << L"fun<T1*, T2*>" << endl;
}

/*template<>
void
fun(int a, int b)
{
    wcout << L"fun(int, int)" << endl;
}*/

int
main()
{
    Fun();
    A<int*, int*>   a_2_int_p_a;

    int i;
    double dl;
    fun(1, 1.0);
    fun(1.0, 1);
    fun('a', 'b');
    //fun(1, 1);
}
