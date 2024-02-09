#include <iostream>

using namespace std;

/*
 * 템플릿 메소드 패턴에서의 정적 바인딩
 *
 * 템플릿을 활용해 부모 클래스 템플릿에 자식의 타입을 전달할 수 있게 되면서
 * 런타임이 아니라, 컴파일 타임에 자식의 함수를 정적 바인딩할 수 있다.
 * 
 * 템플릿을 이용한 정적 다형성(Static Polymorphism) 의 활용이다.
 */

template <typename DERIVED>
class Person
{
private:
    // 자식 객체로 변환하는 함수
    DERIVED& derived()             { return static_cast<DERIVED&>(*this); }
    const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

public:
    // 사용자 인터페이스
    void DoDay() /* Non-virtual */
    {
        // 런타임 다형성의 유연성을 희생하고 정적 다형성을 통해 속도를 높인다.
        derived().Morning();     /* Non-virtual */
        derived().Afternoon();   /* Non-virtual */
        derived().Evening();     /* Non-virtual */
        derived().Night();       /* Non-virtual */
    }

// 세부 구현이 외부에 노출된다.
public:
    // 동적 바인딩 비용을 줄이기 위해, 비가상 함수로 정의
    void Morning()   {}
    void Afternoon() {}
    void Evening()   {}
    void Night()     {}
};

class Student : public Person<Student>
{
public:
    // 비가상 함수 재정의
    void Morning()   { cout << "학교 가기 싫다."      << endl; }
    void Afternoon() { cout << "공부하기 싫다."       << endl; }
    void Evening()   { cout << "오늘 수업 재미없었다." << endl; }
    void Night()     { cout << "내일 학교 가기 싫다."  << endl << endl; }
};

class Worker : public Person<Student>
{
/* 부모에서 외부 객체로 참조되어 호출되므로
 * private 으로 지정할 수 없다. */
public:
    void Morning()   { cout << "회사 가기 싫다."     << endl; }
    void Afternoon() { cout << "일하기 싫다."        << endl; }
    void Evening()   { cout << "오늘 일 힘들었다."    << endl; }
    void Night()     { cout << "내일 회사 가기 싫다." << endl << endl; }
};

int main(int argc, char* argv[])
{
    Student().DoDay();
    Worker().DoDay();

    return 0;
}
