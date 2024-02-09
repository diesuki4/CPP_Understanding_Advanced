/*
 * https://stackoverflow.com/questions/669271/what-is-the-difference-between-the-template-method-and-the-strategy-patterns#answer-669366
 */
#include <iostream>

using namespace std;

/*
 * 템플릿 메소드 패턴 (Template Method Pattern)
 *
 * 이름과 달리, C++ 템플릿과는 하등 관련이 없다.
 *
 * 부모에 가상 함수 호출들로 구성된 비가상 함수 인터페이스 뼈대를 만들고,
 * 각 가상 함수의 세부 구현은 자식들에서 오버라이드하는 패턴
 * 
 * 거창한 것 같지만, 그냥 부모에 가상 함수들의 로직으로 구성된
 * 비가상 함수 레퍼를 만든다고 생각하면 된다.
 *
 * <비가상 함수 인터페이스(NVI, Non-Virtual Interface) 관용구> 라고도 한다.
 */

class Person
{
// 사용자 인터페이스만 외부에 공개한다.
public:
    void DoDay() /* Non-virtual */
    {
        Morning();     /* virtual */
        Afternoon();   /* virtual */
        Evening();     /* virtual */
        Night();       /* virtual */
    }

    virtual ~Person() { }

// 세부 구현은 숨긴다.
private:
    virtual void Morning()   = 0;
    virtual void Afternoon() = 0;
    virtual void Evening()   = 0;
    virtual void Night()     = 0;
};

class Student : public Person
{
// 공개 인터페이스를 제외한 세부 구현은 숨긴다.
private:
    void Morning()   override { cout << "학교 가기 싫다."      << endl; }
    void Afternoon() override { cout << "공부하기 싫다."       << endl; }
    void Evening()   override { cout << "오늘 수업 재미없었다." << endl; }
    void Night()     override { cout << "내일 학교 가기 싫다."  << endl << endl; }
};

class Worker : public Person
{
private:
    void Morning()   override { cout << "회사 가기 싫다."     << endl; }
    void Afternoon() override { cout << "일하기 싫다."        << endl; }
    void Evening()   override { cout << "오늘 일 힘들었다."    << endl; }
    void Night()     override { cout << "내일 회사 가기 싫다." << endl << endl; }
};

int main(int argc, char* argv[])
{
    Student().DoDay();
    Worker().DoDay();

    return 0;
}
