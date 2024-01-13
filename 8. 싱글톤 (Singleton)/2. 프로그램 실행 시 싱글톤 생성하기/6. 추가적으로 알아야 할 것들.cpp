#include <iostream>

using namespace std;

/*
 * 추가적으로 알아야 할 것들
 */

// 복사를 금지하는 매크로
#define UNCOPYABLE(name) \
    name(const name&) = delete; \
    name& operator= (const name&) = delete

template <typename T>
class TWrapper
{
public:
    TWrapper() { }
    UNCOPYABLE(TWrapper);   // 복사 불가

    static T& GetInstance() { return Singleton::Get(); }

    class Singleton
    {
        static Singleton ms_Singleton;

    public:
        Singleton()
        {
            Get();
        }

        // inline 하지 않도록 지정
        __declspec(noinline) static T& Get()
        {
            /* 컴파일러 중에는 함수 내에 static 변수가 있는 경우
             * inline 최적화를 하지 않는 경우가 있는데, 아닌 경우도 있다.
             * 
             * static 변수가 있음에도 inline 최적화를 하게 되면
             * 결과적으로 static 변수가 블록마다 생성돼 여러 개가 된다. */
            static T instance;

            ms_Singleton;

            return instance;
        }
    };
};

template <typename T>
typename TWrapper<T>::Singleton TWrapper<T>::Singleton::ms_Singleton;

/* 이렇게 Is-A 관계는 아니지만
 * Singleton, Uncopyable 처럼 상속을 통해 속성을 추가하는 것을
 * 
 * 믹스인(Mixin) 이라고 한다.
 *
 * 이때는 부모의 인터페이스로 자식을 조작하기 위해
 * 상속한 것이 아니기 때문에
 *
 * 부모를 가상 소멸자로 지정하지 않아도 된다. */
class Derived : public TWrapper<Derived>
{
public:
    void Print() { cout << "Derived::Print()" << endl; }
};

#define _Derived Derived::GetInstance()

int main(int argc, char* argv[])
{
    _Derived.Print();
    
    /* 부모인 TWrapper<T> 의 복사 함수가 삭제됐기 때문에 *
     * 복사할 수 없다.
     * 
     * Derived t = _Derived; */

    return 0;
}
