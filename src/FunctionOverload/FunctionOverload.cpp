#include <cwchar>
#include <iostream>

using std::wcout;
using std::endl;

// Cpp implementation
void
Fun(int i)
{
    wcout << L"Fun_int" << endl;
}

void
Fun(float fl)
{
    wcout << L"Fun_float" << endl;
}

class A
{
public:
    void Bar(int i)
    {
        wcout << L"A::Bar_int" << endl;
    }
    void Bar(float fl)
    {
        wcout << L"A::Bar_float" << endl;
    }
};

// C implementation
void
Fun_C_int(int i)
{
    wprintf(L"Fun_C_int\n");
}

void
Fun_C_float(float fl)
{
    wprintf(L"Fun_C_float\n");
}

struct A_C
{
};

void
A_Bar_C_int(A_C* pThis, int i)
{
    wprintf(L"A::Bar_C_int\n");
}

void
A_Bar_C_float(A_C* pThis, float fl)
{
    wprintf(L"A::Bar_C_float\n");
}

int
main()
{
    // Cpp
    {
        wcout << L"****** CPP implementation ******" << endl;
        Fun(1);
        Fun(1.0f);
        A   a;
        a.Bar(1);
        a.Bar(1.0f);
    }
    // C
    {
        wprintf(L"****** C implementation ******\n");   // Associated CPP codes are in the right comment
        Fun_C_int(1);               // Fun(1);
        Fun_C_float(1.0f);          // Fun(1.0f);
        A_C a;                      // A   a;
        A_Bar_C_int(&a, 1);         // a.Bar(1);
        A_Bar_C_float(&a, 1.0f);    // a.Bar(1.0f);
    }
}
