#include <iostream>

using namespace std;

/*
 * 싱글톤 1
 */

class Singleton
{
    // 클래스 변수이므로, 이것은 선언일 뿐이다.
    static Singleton ms_Singleton;

public:
    Singleton() { cout << __FUNCTION__ << endl; }
};
// 클래스 변수는 밖에 써주지 않으면 초기화되지 않는다.
Singleton Singleton::ms_Singleton;

// ----------------------------

class Wrapper
{
public:
    class Singleton
    {
        static Singleton ms_Singleton;

    public:
        Singleton() { cout << __FUNCTION__ << endl; }
    };
};

Wrapper::Singleton Wrapper::Singleton::ms_Singleton;

// ----------------------------

template <typename T>
class TWrapper
{
public:
    class Singleton
    {
        static Singleton ms_Singleton;

    public:
        Singleton() { cout << __FUNCTION__ << endl; }

        static T& Access()
        {
            // t(Derived) 는 처음 이 문장을 만났을 때 초기화된다.
            static T t;
            return t;
        }
    };

    static T& GetSingletonAccess() { return Singleton::Access(); }
};
/* 템플릿은 틀이기 때문에, 사용하는 코드가 없으면
 * 템플릿 클래스가 생성되지 않는다. */
template <typename T>
typename TWrapper<T>::Singleton TWrapper<T>::Singleton::ms_Singleton;

class Derived : public TWrapper<Derived>
{
public:
    Derived()    { cout << __FUNCTION__ << endl; }
    void Print() { cout << __FUNCTION__ << endl; }
};

int main(int argc, char* argv[])
{
    cout << "main 시작" << endl;

    Derived::GetSingletonAccess().Print();

    return 0;
}
