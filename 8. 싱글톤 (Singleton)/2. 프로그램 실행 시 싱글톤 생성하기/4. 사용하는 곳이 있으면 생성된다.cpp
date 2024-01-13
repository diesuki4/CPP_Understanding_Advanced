#include <iostream>

using namespace std;

/*
 * 사용하는 곳이 있으면 생성된다
 */

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
        Singleton()
        {
            cout << __FUNCTION__ << endl;
        }

        static T& Get()
        {
            static T instance;

            cout << "static Derived instance 직후" << endl;
            
            /* 이번에는 ms_Singleton 에 접근하는 코드를 임의로 추가해보면
             * 
             * 드디어 ms_Singleton 은 생성되지만,
             * 
             * static Derived instance 객체는 main 이후에 생성된다. */
            ms_Singleton;

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
