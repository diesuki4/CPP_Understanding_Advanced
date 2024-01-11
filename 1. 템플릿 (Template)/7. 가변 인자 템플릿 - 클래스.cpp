#include <iostream>
#include <memory>

using namespace std;

/*
 * 가변 인자 템플릿 (Variadic Template) - 클래스
 */

class Mother
{
public:
    Mother(const char* p) { cout << "Mother(" << p << ")" << endl; }
};

class Father
{
public:
    Father(double d) { cout << "Father(" << d << ")" << endl; }
};
// 가변 인자 템플릿을 이용한 클래스 다중 상속
template <typename... BaseClass>
/* ... 의 의미는 앞의 부분이 반복된다는 뜻
 * public Mother, public Father */
class Child : public BaseClass...
{
public:
    // 전달 참조(보편 참조)
    Child(int i, BaseClass&&... baseValues) : BaseClass(baseValues)... // Mother("Hello World !!"), Father(30.0)
    {
        cout << "Child(" << i << ")" << endl;
    }
};

class Button
{
public:
    Button(char c, int i, double d)
    {
        cout << "Button(" << c << ", " << i << ", " << d << ")" << endl;
    }
};

template <typename T, typename... Args>
unique_ptr<T> mymake_unique(Args&&... args)  // 전달 참조
{
    // forward<char>('A'), forward<int>(2), forward<double>(3.0) 
    return unique_ptr<T>(new T( forward<Args>(args)... ));
}

int main(int argc, char* argv[])
{
    Child<Mother, Father> child(100, "Hello World !!", 30.0);

    // rvalue 반환 값의 이동 대입을 통한 소유권 이전
    unique_ptr<Button> uptr = mymake_unique<Button>('A', 2, 3.0);

    return 0;
}
