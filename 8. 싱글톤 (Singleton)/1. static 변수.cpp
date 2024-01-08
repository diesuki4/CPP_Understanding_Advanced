#include <iostream>

using namespace std;

/*
 * static 변수
 */

// 외부 파일에서 extern 참조 불가
static int gInt = 0;

namespace AAA
{
    // 마찬가지로, 외부 파일에서 참조 불가
    static int sNum = 10;
}

class Class
{
    int data;

public:
    Class(int data) : data(data) { }
};

void Func()
{
    // 프로그램 실행 시 초기화
    static int sNum = 10;

    /* 처음 이 문장을 만났을 때 초기화
     *
     * 처음인지 확인하는 코드
     * 멀티스레드에서 1번만 초기화하기 위한 락/해제 코드
     * 생성자 호출 시 예외 발생을 처리하기 위한 Unwinding 코드 
     *
     * 등으로 인해 코드 양도 커지고 비용도 발생한다. */
    static Class c(10);
}

int main(int argc, char* argv[])
{

    return 0;
}
