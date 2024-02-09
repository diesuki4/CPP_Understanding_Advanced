/*
 * https://velog.io/@enamu/C에서의-다형성Polymorphism
 */
#include <iostream>

using namespace std;

/*
 * 정적 다형성(Static Polymorphism) 과 동적 다형성(Dynamic Polymorphism)
 */

/* <정적 다형성>
 * 컴파일 타임에 결정된다. */
namespace StaticPoly
{
    // 함수 오버로딩
    void print(int num)  { cout << num << endl; }
    void print(double d) { cout << d << endl; }

    // 템플릿
    template <typename T>
    void printT(const T& t) { cout << t << endl; }
}

/* <동적 다형성>
 * 런타임에 결정된다. */
namespace DynamicPoly
{
    class Base
    {
    public:
        virtual void print() { cout << "Base" << endl; }
    };

    class Derived : public Base
    {
    public:
        // 가상 함수 오버라이딩
        virtual void print() override { cout << "Derived" << endl; }
    };
}

int main(int argc, char* argv[])
{
    {
        using namespace StaticPoly;

        // 어떤 함수가 호출될지는 컴파일 타임에 결정
        print(3);
        print(3.5);
        printT("Hello World !!");
    }
    cout << endl;
    {
        using namespace DynamicPoly;

        // 어떤 함수가 호출될지는 런타임에 결정
        Base b = *(new Derived);
        b.print();
    }

    return 0;
}
