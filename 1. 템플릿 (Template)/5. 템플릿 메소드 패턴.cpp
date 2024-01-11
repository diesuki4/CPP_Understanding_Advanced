/*
 * https://stackoverflow.com/questions/669271/what-is-the-difference-between-the-template-method-and-the-strategy-patterns#answer-669366
 * https://stackoverflow.com/questions/19062733/what-is-the-motivation-behind-static-polymorphism-in-c
 */
#include <iostream>

using namespace std;

/*
 * 템플릿 메소드 패턴 (Template Method Pattern)
 * 
 * 전략 패턴과 유사하지만, 템플릿을 활용해
 * 부모 클래스 템플릿에 자신의 타입을 전달할 수 있게 되면서
 * 
 * 컴파일 타임에 정적 바인딩이 가능하다는 점이 다르다.
 */

template <typename DERIVED>
class Person abstract
{
public:
    /* 정적 다형성 (Static Polymorphism)
     *
     * 런타임에 동적 바인딩 비용을 줄이기 위해
     * 컴파일 타임에 함수를 정적 바인딩하는 기법
     *
     * 런타임 다형성의 유연성을 조금 희생하고 속도를 높이는 방법이다. */
    void DoDay() /* Non-virtual */
    {
        // 동적 바인딩 (런타임)
        // Morning();

        // 정적 바인딩 (컴파일 타임)
        DERIVED* drvThis = static_cast<DERIVED*>(this);
        drvThis->Morning();      /* virtual */
        drvThis->Afternoon();    /* virtual */
        drvThis->Evening();      /* virtual */
        drvThis->Night();        /* virtual */
    }

    virtual void Morning() = 0;
    virtual void Afternoon() = 0;
    virtual void Evening() = 0;
    virtual void Night() = 0;

    virtual ~Person() { }
};

class Student : public Person<Student>
{
public:
    void Morning()   override { cout << "학교 가기 싫다." << endl; }
    void Afternoon() override { cout << "공부하기 싫다." << endl; }
    void Evening()   override { cout << "오늘 수업 재미없었다." << endl; }
    void Night()     override { cout << "내일 학교 가기 싫다." << endl << endl; }
};

class Worker : public Person<Worker>
{
public:
    void Morning()   override { cout << "회사 가기 싫다." << endl; }
    void Afternoon() override { cout << "일하기 싫다." << endl; }
    void Evening()   override { cout << "오늘 일 힘들었다." << endl; }
    void Night()     override { cout << "내일 회사 가기 싫다." << endl << endl; }
};

int main(int argc, char* argv[])
{
    Student().DoDay();
    Worker().DoDay();

    return 0;
}
