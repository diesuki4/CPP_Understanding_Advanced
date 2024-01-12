#include <iostream>

using namespace std;

/*
 * 싱글톤 5
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
            /* main 이전에 ms_Singleton 이 초기화될 때, 강제로 Get() 을 호출해주면
             * 
             * static Derived instance 도 그때 초기화되도록 할 수 있다.*/
            Get();
        }

        static T& Get()
        {
            static T instance;

            cout << "static Derived instance 직후" << endl;
            
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

int main(int argc, char* argv[])
{
    cout << "main 시작" << endl;

    Derived::GetInstance().Print();

    return 0;
}
