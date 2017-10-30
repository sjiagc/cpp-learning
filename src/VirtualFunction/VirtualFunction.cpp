#include <iostream>
#include <cwchar>

using std::wcout;
using std::endl;

// Cpp implementation
class Base
{
public:
    Base():_b(1)
    {
        wcout << L"Base::ctor" << endl;
    }
    virtual void Fun()
    {
        wcout << L"Base::Fun " << _b << endl;
    }
protected:
    int _b;
};

class Derived: public Base
{
public:
    Derived():_d(2)
    {
        wcout << L"Derived::ctor" << endl;
    }
    void Fun()
    {
        wcout << L"Derived::Fun " << _d << endl;
    }
private:
    int _d;
};

// C implementation

// Virtual function table declare
struct vtable
{
    void (*Fun)(void *p);
};
// Definition of Base_C class
struct Base_C
{
    vtable  *vptr;
    int _b;
};

void
Base_C_Fun(void *p)
{
    Base_C  *pBase = (Base_C*)p;
    wprintf(L"Base_C::Fun %d\n", pBase->_b);
}

struct vtable   dase_C_vtable = // Virtual table of Base_C
{
    Base_C_Fun
};


void
Base_C_ctor(Base_C *pBase)
{
    pBase->vptr = &dase_C_vtable;
    pBase->_b = 1;
    wprintf(L"Base_C::ctor\n");
}

// Definition of Derived_C class
struct Derived_C
{
    vtable  *vptr;
    int _b;
    int _d;
};

void
Derived_C_Fun(void *p)
{
    Derived_C   *pDerived = (Derived_C*)p;
    wprintf(L"Derived_C::Fun %d\n", pDerived->_d);
}

struct vtable   derived_C_vtable =  // Virtual table of Derived_C
{
    Derived_C_Fun
};

void
Derived_C_ctor(Derived_C *pDerived)
{
    Base_C_ctor((Base_C*)pDerived);
    pDerived->vptr = &derived_C_vtable;
    pDerived->_d = 2;
    wprintf(L"Derived_C::ctor\n");
}

int
main()
{
    // CPP part
    {
        wcout << L"****** CPP implementation ******" << endl;
        Derived derived;
        Base    *p = &derived;
        p->Fun();
        (*p).Fun();
        Base    &r = derived;
        r.Fun();
    
        p->Base::Fun();
    }

    // C part
    {
        wprintf(L"****** C implementation ******\n");   // Associated CPP codes are in the right comment
        Derived_C   derived;                // Derived derived;
        Derived_C_ctor(&derived);

        Base_C  *p = (Base_C*)&derived;     // Base    *p = &derived;

        p->vptr->Fun(p);                    // p->Fun();

        (*p).vptr->Fun(p);                  // (*p).Fun();

        Base_C  *r = (Base_C*)&derived;     // Base    &r = derived;

        r->vptr->Fun(r);                    // r.Fun();

        Base_C_Fun(p);                      // p->Base::Fun();
    }

    return 0;
}
