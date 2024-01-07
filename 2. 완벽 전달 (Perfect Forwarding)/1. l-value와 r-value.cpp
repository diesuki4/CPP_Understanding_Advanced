#include <iostream>

using namespace std;

/*
 * l-value와 r-value
 */

void Func1(int i)        { return; }
void Func2(const int& i) { return; }

struct Widget { int data; };

// 상수 레퍼런스는 임시 객체를 받을 수 있다.
void Func2(const Widget& w) { return; }
// 이름 없이 값만을 의미하는 임시 객체의 참조를 구한다고 해서
// r-value 레퍼런스라고 한다.
void Func3(Widget&& w)      { return; }

int main(int argc, char* argv[])
{
    int i, j;

    // i 는 주소를 의미하므로 l-value
    // mov    dword ptr [::i], 3
    i = 3;

    // i 가 값을 의미하므로 r-value
    // mov    eax, dword ptr [::i]
    // mov    dword ptr [::j], eax
    j = i;

    // & 는 주소 연산자다.
    // 값을 의미하는 r-value 를, 주소를 의미하는 l-value 로 변환
    // lea    eax, dword ptr [::i]
    // mov    dword ptr [::p], eax
    int* p = &i;

    // * 는 역참조 연산자다.
    // 주소를 의미하는 l-value 를, 값을 의미하는 r-value 로 변환
    // mov    eax, dword ptr [::p]
    // mov    dword ptr [eax], 5
    *p = 5;

    // Call by Value 는 Caller 가 r-value 를 전달하도록 한다.
    // mov    edi, dword ptr [::i]
    Func1(i);

    // Call by Reference 는 Caller 가 r-value 가 아닌, l-value 를 전달하도록 한다.
    // lea    edi, dword ptr [::i]
    Func2(i);
    // mov    edi, dword ptr [::p]
    Func2(*p);

    // 임시 값은 스택에 만들어진다.
    // mov    dword ptr [::임시_1], 3
    // lea    edi, dword ptr [::임시_1]
    Func2(3);
    // 임시 객체도 스택에 만들어진다.
    // mov    dword ptr [::임시_2], 5
    // lea    edi, dword ptr [::임시_2]
    Func2(Widget{5});

    // 상수 레퍼런스와 r-value 레퍼런스 호출의 내부적인 동작은 같다.
    // mov    dword ptr [::임시_3], 8
    // lea    edi, dword ptr [::임시_3]
    Func3(Widget{8});

    return 0;
}
