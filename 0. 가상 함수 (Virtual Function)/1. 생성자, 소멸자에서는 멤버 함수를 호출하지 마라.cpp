#include <iostream>

using namespace std;

class Base
{
public:
    /* 생성자, 소멸자 내에서는 정적 바인딩만 진행된다.
     * 
     * 즉, 가상(혹은 순수 가상) 함수에 상관 없이
     * 무조건 자신의 함수만 호출한다는 것이다.
     *
     * 생성 시에는 자식 부분이 생성 전이고,
     * 소멸 시에는 자식 부분이 소멸 후이기 때문.*/

    /* 따라서 생성자, 소멸자에서는
     * 의미 있는 멤버 함수를 호출하지 않는 것이 좋다.
     * 
     * 생성자, 소멸자에서 처리하지 말고
     * 별도 Initialize(), Finalize() 같은 별도 인터페이스를 사용할 것. */
    void Initialize() { cout << "초기화" << endl; }
    void Finalize()   { cout << "마무리 정리" << endl; }

    Base()
    {
        // Initialize()
        doPrint();
    }

    ~Base()
    {
        // Finalize();
        doPrint();
    }

    virtual void print()  { cout << "Base::print" << endl; }

    void doPrint()
    {
        print();
    }
};

class Derived : public Base
{
public:
    void print() override { cout << "Derived::print" << endl; }
};

int main(int argc, char* argv[])
{
    unique_ptr<Base> uptr = make_unique<Derived>();

    uptr->Initialize();

    // ...

    uptr->Finalize();

    return 0;
}
