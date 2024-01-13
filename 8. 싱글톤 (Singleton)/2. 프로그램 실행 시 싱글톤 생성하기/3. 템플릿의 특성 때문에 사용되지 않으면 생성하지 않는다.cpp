#include <iostream>

using namespace std;

/*
 * 템플릿의 특성 때문에 사용되지 않으면 생성하지 않는다
 */

template <typename T>
class TWrapper
{
public:
    TWrapper() { cout << __FUNCTION__ << endl; }

    static T& GetInstance() { return Singleton::Get(); }

    class Singleton
    {
        // 1. 컴파일러가 ms_Singleton 을 초기화해야 하는지 확인하기 위해 생성자를 본다.
        static Singleton ms_Singleton;

    public:
        Singleton()
        {
            cout << __FUNCTION__ << endl;
            // 2. 생성자에서 Get() 함수를 호출한다.
            Get();
        }

        static T& Get()
        {
            // 3. Get() 내에서 Derived instance 객체를 초기화해야 한다.
            static T instance;

            cout << "static Derived instance 직후" << endl;

            /* 4. 하지만, 여전히 ms_Singleton 없이도 Get() 을 호출하는데 문제가 없기 때문에
             * ms_Singleton 은 생성되지 않는다. */
            
            return instance;
        }
    };
};

template <typename T>
typename TWrapper<T>::Singleton TWrapper<T>::Singleton::ms_Singleton;

class Derived : public TWrapper<Derived>
{
public:
    Derived()    { cout << __FUNCTION__ << endl; }

    void Print() { cout << "Derived::Print() 호출" << endl; }
};

#define _Derived Derived::GetInstance()

int main(int argc, char* argv[])
{
    cout << "main 시작" << endl;

    _Derived.Print();

    return 0;
}
