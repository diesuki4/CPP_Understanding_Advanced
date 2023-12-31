/*
 * https://openmynotepad.tistory.com/20
 */
#include <iostream>

using namespace std;

/*
 * 참조 생략 (Reference Collapsing)
 */

/*
 * 레퍼런스의 레퍼런스 같은 건 없다.
 * int& (&ref) = num;
 *
 * 그런데, 템플릿의 타입 추론 과정 중에는
 * 이런 표현이 생길 수 있다.
 *
 * 이때, 아래처럼 규칙에 따라 참조자의 개수를 줄이는 것을
 * <참조 생략> 이라고 한다.
 *
 * L: l-value 레퍼런스
 * R: r-value 레퍼런스
 *
 * int&  (&t)   ==>  int&  t      L L  ==>  L
 * int&  (&&t)  ==>  int&  t      L R  ==>  L
 * int&& (&t)   ==>  int&  t      R L  ==>  L
 * int&& (&&t)  ==>  int&& t      R R  ==>  R
 *
 * 둘 모두 r-value 레퍼런스인 경우에만,
 * 최종 ParamType 도 r-value 레퍼런스가 된다.
 */

                                // int       int&       int&&      1
template <typename T>           // int&      int&       int        int
void Func(/*ParamType*/T&& t)   // int&      int&       int&&      int&&
{
    /*
     * 템플릿의 매개변수가 T&& 인 보편 참조이므로,
     * r-value 레퍼런스가 전달된 경우에만
     *
     * 최종 ParamType 도 r-value 레퍼런스가 된다.
     */
    return;
}

int main(int argc, char* argv[])
{
    int n = 1;
    int& r = n;
    int&& rr = 2;

    Func(n);        // Func<int&>(int&)
    /*
     * 아래에서 int&, int&& 에서 레퍼런스가 제거되어
     * int 와 동일하게 전달된 것을
     * 
     * 참조성 무시(Referenceness Stripping) 라고 한다.
     */
    Func(r);        // Func<int&>(int&)
    Func(rr);       // Func<int&>(int&)

    Func(move(r));  // Func<int>(int&&)
    Func(1);        // Func<int>(int&&)

    return 0;
}
