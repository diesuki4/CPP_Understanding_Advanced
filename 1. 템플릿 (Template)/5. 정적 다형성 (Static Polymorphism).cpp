/*
 * https://stackoverflow.com/questions/669271/what-is-the-difference-between-the-template-method-and-the-strategy-patterns#answer-669366
 * https://stackoverflow.com/questions/19062733/what-is-the-motivation-behind-static-polymorphism-in-c
 */
#include <iostream>

using namespace std;

/*
 * 정적 다형성 (Static Polymorphism)
 * 
 * 런타임 동적 바인딩 비용을 줄이기 위해
 * 컴파일 타임에 함수를 정적 바인딩하는 기법
 *
 * 런타임 다형성의 유연성을 조금 희생하고 속도를 높이는 방법이다.
 * 
 * 템플릿 메소드 패턴 등에서 공개 인터페이스에서
 * 가상 멤버 함수를 호출하는 경우
 * 
 * C++ 템플릿을 이용해 자식의 타입을 얻으면
 * 다운캐스팅을 통해 정적 바인딩을 수행할 수 있게 된다.
 */

// 전형적인 템플릿 메소드 패턴
class Base
{
public:
    // Non-virtual 공개 인터페이스
    void PublicInterface()
    {
        // virtual 멤버 함수 호출 (런타임 동적 바인딩)
        FuncImpl();
    }

private:
    virtual void FuncImpl() { cout << "Base" << endl; }
};

class Derived : public Base
{
private:
    // 공개 인터페이스의 실제 구현은 자식에서 오버라이드 가능
    void FuncImpl() override { cout << "Derived" << endl; }
};

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

// 템플릿을 통해 부모에서 자식의 타입을 얻을 수 있다.
template <typename DERIVED>
class BaseT
{
public:
    void PublicInterface()
    {
        /* 자식의 타입으로 다운캐스팅 수행
         * 
         * 실제 객체가 자식 타입인 것이 확실하므로
         * dynamic_cast 를 쓰지 않아도 된다. */
        DERIVED* dThis = static_cast<DERIVED*>(this);

        // 이제 런타임 동적 바인딩이 아닌, 컴파일 타임 정적 바인딩된다.
        dThis->FuncImpl();
    }

    virtual void FuncImpl() { cout << "BaseT" << endl; }
};

class DerivedT : public BaseT<DerivedT>
{
/* 하지만, 이제는 PublicInterface 에서의 호출이
 * 외부에서의 호출로 간주되므로
 *
 * 실제 구현이 외부에 노출되어야만 한다. */
public:
    void FuncImpl() override { cout << "DerivedT" << endl; }
};

int main(int argc, char* argv[])
{
    Derived d;
    DerivedT dt;

    d.PublicInterface();
    dt.PublicInterface();

    return 0;
}
