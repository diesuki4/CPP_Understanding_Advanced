/*
 * https://stackoverflow.com/questions/14391272/does-constexpr-imply-inline#answer-14391320
 */
#include <iostream>
#include <array>

using namespace std;

/*
 * constexpr (상수 표현식)
 * 
 * 자체는 C++11 부터 가능했지만, C++17 부터 몇몇 기능들이 더 추가됐다.
 * 
 * 컴파일 타임에 계산이 가능하면
 * 템플릿 인자, 배열 크기 등에 쓰일 수 있다.
 * 
 * constexpr 함수와 생성자는 암시적으로 inline 화 된다.
 */

// 함수에도 붙일 수 있다.
constexpr int Sum(int n)
{
    if (n == 0)
        return 0;

    return n + Sum(n - 1);
}

constexpr int Pow(int base, int exp)
{
    if (exp == 0)
        return 1;

    return base * Pow(base, exp - 1);
}

/* 컴파일 타임에 계산이 가능하면 미리 하고,
 * 불가능하면 알아서 런타임에 계산된다. */
constexpr int Factorial(int n)
{
    if (n <= 1)
        return 1;

    return n * Factorial(n - 1);
}

class Button
{
    int num;

public:
    /* 생성자에도 붙일 수 있다.
     * 상수 위치에 쓰일 수 있는 클래스가 된다. */
    constexpr Button(int num) : num(num) { }

    // 멤버 함수에도 붙일 수 있다.
    constexpr int getNum() const { return num; }
};

/* 생성자를 포함한 모든 멤버 함수가 constexpr 이면,
 * 컴파일 타임 객체를 이용해 비멤버 constexpr 함수도 만들 수 있다. */
constexpr int GetNumByButton(Button b)
{
    return b.getNum();
}

template <int I>
auto Get()
{
    /* 템플릿 내의 if 조건문에서도 쓸 수 있다.
     * 
     * 하나의 함수에서 다른 타입을 반환하는 것 같지만
     * 실제로는 조건에 따라, 다른 템플릿 함수가 생성되는 것이다.
     * 
     * 따라서, 템플릿 특수화의 좋은 대체재다. */
    if constexpr (I == 0)
        return 'A';   // char
    else if constexpr (I == 1)
        return 100;   // int
    else if constexpr (I == 2)
        return 30.F;  // float
    else if constexpr (I == 3)
        return "Hello World !!";   // string
}

int main(int argc, char* argv[])
{
    const int N = 10;
    int arr1[N];

    // 변수에도 붙일 수 있다.
    constexpr int N2 = 10;
    int arr2[N2];

    int arr3[Sum(3)];               // int[6]
    array<float, Pow(2, 3)> arr4;   // array<float, 8>

    // 상수 표현식이라고 해서 상수로만 쓸 수 있는 건 아니다.
    cout << Sum(10) << endl;
    cout << Pow(10, 3) << endl;
    cout << Factorial(4) << endl;

    char   c = Get<0>();
    int    i = Get<1>();
    float  f = Get<2>();
    string s = Get<3>();

    Button b(10);
    const Button cb(10);
    
    // const 객체여도 쓸 수 없다.
    // int arr5[GetNumByButton(b)];
    // int arr5[GetNumByButton(cb)];

    // 컴파일 타임 객체만 쓸 수 있다.
    int arr5[GetNumByButton(Button(10))];     // int[10]

    int num = 0;
    const int cNum = 3;

    /* 마치 조건부 컴파일처럼 사용할 수도 있다.
     * 컴파일 타임에 알 수 없는 일반 변수는 올 수 없다. */

    // if constexpr (num == 3)
    if constexpr (cNum == 0)
        cout << c << " " << i << endl;
    else if constexpr (cNum == 3)
        cout << f << " " << s << endl;

    return 0;
}
