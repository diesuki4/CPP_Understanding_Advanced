#include <iostream>

using namespace std;

/*
 * 싱글톤 2
 */

// T 타입의 싱글톤을 반환하도록 하는 중첩 레퍼 클래스
template <typename T>
class TWrapper
{
public:
    TWrapper() { cout << __FUNCTION__ << endl; }

    static T& GetInstance() { return Singleton::Get(); }

    class Singleton
    {
        static Singleton ms_Singleton;

    public:
        Singleton() { cout << __FUNCTION__ << endl; }

        static T& Get()
        {
            /* Derived instance 는 처음 이 문장을 만났을 때 초기화된다.
             *
             * TWrapper<Derived>::TWrapper() 생성자
             * Derived::Derived() 생성자 */
            static T instance;

            cout << "static Derived instance 직후" << endl;

            return instance;
        }
    };
};
/* 이때도 Singleton::Get() 함수가 사용될 뿐,
 * 템플릿의 특성 때문에 Singleton::ms_Singleton 은 생성되지 않는다. */
template <typename T>
typename TWrapper<T>::Singleton TWrapper<T>::Singleton::ms_Singleton;

class Derived : public TWrapper<Derived>
{
public:
    Derived()    { cout << __FUNCTION__ << endl; }

    void Print() { cout << "Derived::Print() 호출" << endl; }
};

int main(int argc, char* argv[])
{
    cout << "main 시작" << endl;

    /* Derived 객체는 Derived:: 때문에 생기는 것이 아니라,
     *
     * TWrapper<Derived>::Singleton::Get() 함수 내의
     *
     * static Derived instance 때문에 생기는 것이다. */
    Derived::GetInstance().Print();

    return 0;
}
