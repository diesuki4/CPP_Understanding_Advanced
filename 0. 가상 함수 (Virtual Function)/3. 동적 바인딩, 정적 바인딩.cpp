#include <iostream>

using namespace std;

/*
 * 동적 바인딩, 정적 바인딩
 */

class Base
{
public:
    // 컴파일 타임에 진행되는 동적 바인딩
    void Static()          { cout << "Base::Static" << endl; }
    // 런타임에 진행되는 정적 바인딩
    virtual void Dynamic() { cout << "Base::Dynamic" << endl; }

    ~Base() { }
};

class Derived : public Base
{
public:
    void Static()           { cout << "Derived::Static" << endl; }
    void Dynamic() override { cout << "Derived::Dynamic" << endl; }
};

int main(int argc, char* argv[])
{
    Derived derived;
    Base& base = static_cast<Base&>(derived);

    base.Static();
    base.Dynamic();

    /* 동적 바인딩 비용을 줄이기 위해
     * 실제 객체의 타입을 확실히 아는 경우에는
     *
     * 직접 함수를 호출해 정적 바인딩을 하는 것이 효율적이다. */
    derived.Derived::Dynamic();

    return 0;
}
