/*
 * https://stackoverflow.com/questions/669271/what-is-the-difference-between-the-template-method-and-the-strategy-patterns#answer-669366
 */
 #include <iostream>

using namespace std;

/*
 * 전략 패턴 (Strategy Pattern)
 * 
 * 부모에 가상 함수 호출들로 구성된
 * 비가상 함수 인터페이스 뼈대를 만들고
 * 
 * 각 가상 함수의 세부 구현은 자식들에서 하는 패턴
 */

class Person abstract
{
public:
    void DoDay() /* Non-virtual */
    {
        /* 템플릿 메소드 패턴과 달리 동적 바인딩이다. */
        Morning();   /* virtual */
        Afternoon(); /* virtual */
        Evening();   /* virtual */
        Night();     /* virtual */
    }

    virtual void Morning()   = 0;
    virtual void Afternoon() = 0;
    virtual void Evening()   = 0;
    virtual void Night()     = 0;

    virtual ~Person() { }
};

class Student : public Person
{
public:
    void Morning()   override { cout << "학교 가기 싫다."       << endl; }
    void Afternoon() override { cout << "공부하기 싫다."        << endl; }
    void Evening()   override { cout << "오늘 수업 재미없었다." << endl; }
    void Night()     override { cout << "내일 학교 가기 싫다."  << endl << endl; }
};

class Worker : public Person
{
public:
    void Morning()   override { cout << "회사 가기 싫다."      << endl; }
    void Afternoon() override { cout << "일하기 싫다."         << endl; }
    void Evening()   override { cout << "오늘 일 힘들었다."    << endl; }
    void Night()     override { cout << "내일 회사 가기 싫다." << endl << endl; }
};

int main(int argc, char* argv[])
{
    Student().DoDay();
    Worker().DoDay();

    return 0;
}
