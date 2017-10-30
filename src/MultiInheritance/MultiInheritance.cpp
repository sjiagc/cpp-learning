#include <iostream>
#include <cwchar>

using std::wcout;
using std::endl;

// Cpp implementation
class B1
{
public:
    B1():_b1(1){}
    virtual void fun(void){wcout << L"B1::fun " << _b1 << endl;}
protected:
    int _b1;
};

class B2
{
public:
    B2():_b2(2){}
    virtual void bar(void){wcout << L"B2::bar " << _b2 << endl;}
protected:
    int _b2;
};

class D: public B1, public B2
{
public:
    D(int arg):_d(arg){wcout << L"D::ctor This: " << this << endl;}
    void bar(void){wcout << L"D::bar " << _b1 << L" This: " << this << endl;}
    virtual void foo(void){wcout << L"D::foo " << _d << endl;}
private:
    int _d;
};
// C implementation
// B1
struct B1_C;

struct B1_C_vtbl_t
{
    void (*fun)(B1_C*);
};

struct B1_C
{
    struct B1_C_vtbl_t  *vptr;
    int _b1;
};

void
fun_B1_C(B1_C *pThis)
{
    wprintf(L"B1::fun %d\n", pThis->_b1);
}

struct B1_C_vtbl_t  B1_C_vtbl =
{
    fun_B1_C
};

void
B1_C_ctor(B1_C* pThis)
{
    pThis->vptr = &B1_C_vtbl;
    pThis->_b1 = 1;
}

// B2
struct B2_C;

struct B2_C_vtbl_t
{
    void (*bar)(B2_C*);
};

struct B2_C
{
    struct B2_C_vtbl_t  *vptr;
    int _b2;
};

void
bar_B2_C(B2_C *pThis)
{
    wprintf(L"B2::bar %d\n", pThis->_b2);
}

struct B2_C_vtbl_t  B2_C_vtbl =
{
    bar_B2_C
};

void
B2_C_ctor(B2_C* pThis)
{
    pThis->vptr = &B2_C_vtbl;
    pThis->_b2 = 2;
}

// D
struct D_C;

struct D_C_vtbl_t
{
    void (*fun)(B1_C*);
    void (*foo)(D_C*);
};

struct D_C
{
    D_C_vtbl_t  *vptr;
    int _b1;
    B2_C_vtbl_t *B2_vptr;
    int _b2;
    int _d;
};

#define OFFSET_B2   ((unsigned long)(unsigned long long)&(((D_C*)0)->B2_vptr))
#define GET_B2_IN_D(p)  ((B2_C*)(((unsigned char*)p) + OFFSET_B2))
#define GET_D_FROM_B2(p)    ((D_C*)(((unsigned char*)p) - OFFSET_B2))
#define GET_B1_IN_D(p)  ((B1_C*)p)
#define GET_D_FROM_B1(p)    ((D_C*)p)

void
bar_D_C(B2_C *pb2)
{
    D_C *pThis = GET_D_FROM_B2(pb2);
    wprintf(L"D::bar %d This: %p\n", pThis->_b1, pThis);
}

void
foo_D_C(D_C *pThis)
{
    wprintf(L"D::foo %d\n", pThis->_d);
}

struct D_C_vtbl_t   D_C_vtbl =
{
    fun_B1_C,
    foo_D_C
};

struct B2_C_vtbl_t  D_C_B2_vtbl =
{
    bar_D_C
};

void
D_C_ctor(D_C *pThis, int arg)
{
    B1_C_ctor(GET_B1_IN_D(pThis));
    B2_C_ctor(GET_B2_IN_D(pThis));
    pThis->vptr = &D_C_vtbl;
    pThis->B2_vptr = &D_C_B2_vtbl;
    pThis->_d = arg;
    wprintf(L"D_C_ctor This: %p\n", pThis);
}

int
main()
{
    // Cpp part
    {
        wcout << L"****** CPP implementation ******" << endl;
        D   d(3);
        B1  *pb1 = &d;
        pb1->fun();
        B2  *pb2 = &d;
        pb2->bar();
        pb2 = (B2*)(pb1);   // error
        pb2->bar();
        pb2 = dynamic_cast<B2*>(pb1);   // correct
        pb2->bar();
        D   *pd = &d;
        pd->foo();
        pd->bar();
    }
    // C part
    {
        wprintf(L"****** C implementation ******\n");   // Associated CPP codes are in the right comment
        struct D_C  d;                      //  D   d(3);
        D_C_ctor(&d, 3);

        B1_C    *pb1 = GET_B1_IN_D(&d);     //  B1  *pb1 = &d;

        pb1->vptr->fun(pb1);                //  pb1->fun();

        B2_C    *pb2 = GET_B2_IN_D(&d);     //  B2  *pb2 = &d;

        pb2->vptr->bar(pb2);                //  pb2->bar();

        pb2 = (B2_C*)pb1;                   //  pb2 = (B2*)(pb1);   // error

        pb2->vptr->bar(pb2);                //  pb2->bar();

        pb2 = GET_B2_IN_D(GET_D_FROM_B1(pb1)); //  pb2 = dynamic_cast<B2*>(pb1);   // correct

        pb2->vptr->bar(pb2);                //  pb2->bar();

        D_C *pd = &d;                       //  D   *pd = &d;

        pd->vptr->foo(pd);                  //  pd->foo();

        B2_C    *pTmpB2 = GET_B2_IN_D(pd);  //  pd->bar();
        pTmpB2->vptr->bar(pTmpB2);
    }
}
