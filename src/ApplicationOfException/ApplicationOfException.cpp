// Anti-crackers always use exception - especially OS exceptions - to avoid others to trace their binary executable. Here is an very simple example.

#include <iostream>
#include <exception>

using std::wcout;
using std::endl;
using std::exception;

class A
{
public:
    A(int arg = 0):a(arg){}
    int a;
};

class B
{
};

class C
{
};

void
BottomHalf()
{
    wcout << L"Bottom half" << endl;
}

void
BH()
{
    wcout << L"BH" << endl;
}

void
FirstHalf()
{
    wcout << L"First half" << endl;
    throw A(1); // Throw A with value 1
}

void
Inner()
{
    try {
        FirstHalf();
    }
    catch(A &a)
    {
        if (a.a == 1)
            throw B();  // Throw B
        else
            throw C();  // Throw C
    }
}

void
Outer()
{
    try {
        Inner();
    }
    catch(B &)  // Catch B
    {
        BottomHalf();
    }
    catch(C &)  // Catch C
    {
        BH();
    }
}

int
main()
{
    Outer();
    return 0;
}
