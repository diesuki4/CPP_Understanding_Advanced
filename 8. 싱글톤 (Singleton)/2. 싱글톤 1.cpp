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

/* ---------------------------- */

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

/* ---------------------------- */

/* 템플릿은 틀이기 때문에, 사용하는 코드가 없으면
 * 템플릿 클래스가 생성되지 않는다. */
template <typename T>
class TWrapper
{
public:
    class Singleton
    {
        static Singleton ms_Singleton;

    public:
        Singleton() { cout << __FUNCTION__ << endl; }
    };
};

template <typename T>
typename TWrapper<T>::Singleton TWrapper<T>::Singleton::ms_Singleton;

/* 실제 클래스에서 상속 받아도
 * 템플릿의 특성 때문에 ms_Singleton 은 생성되지 않는다. */
class Derived : public TWrapper<Derived>
{
};

int main(int argc, char* argv[])
{
    cout << "main 시작" << endl;

    return 0;
}
