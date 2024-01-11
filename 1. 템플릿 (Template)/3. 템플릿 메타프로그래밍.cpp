#include <iostream>

using namespace std;

/*
 * 템플릿 메타프로그래밍 (Template Metaprogramming)
 * 
 * 템플릿을 이용해 컴파일 타임에 컴파일러가 코드를 작성하도록 하는 기법
 * 
 * 주로 재귀와 상속이 많이 활용된다.
 */

int Factorial(int N)
{
    if (N == 0)
        return 1;

    return N * Factorial(N - 1);
}

template <int N>
struct TMPFactorial
{
    enum { value = N * TMPFactorial<N - 1>::value };
};

// 특수화를 이용한 종료 조건 명시
template <>
struct TMPFactorial<0>
{
    enum { value = 1 };
};

int main(int argc, char* argv[])
{
    cout << Factorial(5) << endl;
    cout << TMPFactorial<5>::value << endl;

    return 0;
}
