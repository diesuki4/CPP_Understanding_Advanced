#include <iostream>

using namespace std;

/*
 * 완벽한 전달 (Perfect Forwarding)
 */

int GetTemp() { return 5; }

void Foo(int& i)  { cout << "Foo(int&)" << endl << endl; }
void Foo(int&& i) { cout << "Foo(int&&)" << endl << endl; }

void Bar(int& i)  { cout << "Bar(int&)" << endl; Foo(i); }
void Bar(int&& i) { cout << "Bar(int&&)" << endl; Foo(i); }
/*
 * i 는 r-value 레퍼런스로 전달됐지만,
 * 함수 본문에서 이름을 가지므로 l-value 다.
 *
 * 따라서, move() 함수로 다시 r-value 레퍼런스로 만들어 줘야 한다.
 */
void Car(int&& i) { cout << "Car(int&&)" << endl; Foo(move(i)); }
/*
 * 아래는 일반 함수와 달리, 보편 참조이기 때문에
 * r-value 레퍼런스를 받는 템플릿 매개변수는
 *
 * 참조 생략에 의해
 * l-value 인자에 대해서도 동작한다.
 */
template <typename T>
void Dar(T&& t)   { cout << "Dar(T&&)" << endl; Foo(t); }
/*
 * 그렇다고, 보편 참조에서 매개변수에
 * move() 를 붙여버리면
 *
 * 둘 다 r-value 레퍼런스로 전달되게 된다.
 */
template <typename T>
void Ear(T&& t)   { cout << "Ear(T&&)" << endl; Foo(move(t)); }
/*
 * 이때, forward() 함수를 통해
 * 전달된 인자의 참조성을 그대로 유지한 채 다시 전달할 수 있다.
 * 
 * 이것을 <완벽한 전달> 이라고 한다.
 */
template <typename T>
void Far(T&& t)   { cout << "Far(T&&)" << endl; Foo(forward<T>(t)); }

int main(int argc, char* argv[])
{
    int i = 5;

    Bar(i);
    Bar(GetTemp());
    Car(GetTemp());

    Dar(i);
    Dar(5);

    Ear(i);
    Ear(5);

    Far(i);
    Far(5);

    return 0;
}
