#include <iostream>

using namespace std;

/*
 * static_cast, dynamic_cast
 */

class Button
{
public:
    void Print() { cout << "Button::Print" << endl; }
};

class Slider
{
public:
    void Print() { cout << "Slider::Print" << endl; }
};

class Base
{
public:
    virtual ~Base() { }
};

class Derived1 : public Base
{
public:
    void Print() { cout << "Derived1::Print" << endl; }
};

class Derived2 : public Base
{
public:
    void Print() { cout << "Derived1::Print" << endl; }
};

int main(int argc, char* argv[])
{
    Button* pb = new Button;
    Slider* ps = (Slider*)pb;

    // 이게 된다..
    ps->Print();

    // 상속 관계가 아니기에 불가
    // ps = static_cast<Slider*>(pb);

    delete pb;

    Base* pbase = new Base;
    // 컴파일 타임에 진행된다.
    Derived1* pd1s = static_cast<Derived1*>(pbase);  // 잘못된 다운캐스팅

    /* Print() 함수 내에서 Derived1 의 멤버를 쓰지 않기 때문에 
     * 문제가 생기지 않은 것 뿐 */
    pd1s->Print();

    /* VTable 을 통해 접근하는 RTTI 정보를 활용해
     * 런타임에 캐스팅을 진행 */
    if (Derived1* pd1d = dynamic_cast<Derived1*>(pbase))  // 잘못된 다운캐스팅
        pd1d->Print();

    delete pbase;

    pd1s = new Derived1;
 
    if (Derived2* pd2d = dynamic_cast<Derived2*>(pd1s))  // 잘못된 크로스캐스팅
        pd2d->Print();

    delete pd1s;

    return 0;
}
