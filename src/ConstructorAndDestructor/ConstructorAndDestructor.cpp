#include <cwchar>
#include <iostream>

using std::wcout;
using std::endl;

// Cpp implementation
class A
{
public:
    A():_a(1)
    {
        wcout << L"A::ctor_v" << endl;
    }
    A(int a):_a(a)
    {
        wcout << L"A::ctor_int " << _a << endl;
    }
    ~A()
    {
        wcout << L"A::dtor " << _a << endl;
    }
private:
    int _a;
};

// C implementation
struct A_C
{
    int _a;
};

void
A_C_ctor_v(A_C *pThis)
{
    pThis->_a = 1;
    wprintf(L"A_C::ctor_v\n");
}

void
A_C_ctor_int(A_C *pThis, int a)
{
    pThis->_a = a;
    wprintf(L"A_C::ctor_int %d\n", pThis->_a);
}

void
A_C_dtor(A_C *pThis)
{
    wprintf(L"A_C::dtor %d\n", pThis->_a);
}

// Example function
void
CppEg()
{
    wcout << L"****** Cpp implementation ******" << endl;
    A   a;
    {
        A   a2(2);
        wcout << L"some other operations in CppEg" << endl;
    }
}

void
CEg()
{
    wprintf(L"****** C implementation ******\n");
    struct A_C  a;
    A_C_ctor_v(&a);
    {
        struct A_C  a2;
        A_C_ctor_int(&a2, 2);
        wprintf(L"some other operations in CEg\n");
        A_C_dtor(&a2);
    }
    A_C_dtor(&a);
}

int
main()
{
    CppEg();
    CEg();
}

