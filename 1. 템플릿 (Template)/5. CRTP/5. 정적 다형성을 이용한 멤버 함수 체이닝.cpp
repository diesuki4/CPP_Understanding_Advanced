/*
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 */
#include <iostream>

using namespace std;

/*
 * 정적 다형성을 이용한 멤버 함수 체이닝
 */

namespace General
{
    class Printer
    {
    public:
        Printer& print(const string& s)
        {
            cout << s;
            return *this;
        }

        Printer& println(const string& s)
        {
            cout << s << endl;
            return *this;
        }
    };

    class ChildPrinter : public Printer
    {
    public:
        ChildPrinter& printChar(const char c)
        {
            cout << c;
            return *this;
        }
    };
}

namespace CRTP
{
    template <typename DERIVED>
    class Printer
    {
    private:
        DERIVED& derived()             { return static_cast<DERIVED&>(*this); }
        const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

    public:
        DERIVED& print(const string& s)
        {
            cout << s;
            return derived();
        }

        DERIVED& println(const string& s)
        {
            cout << s << endl;
            return derived();
        }
    };

    class ChildPrinter : public Printer<ChildPrinter>
    {
    public:
        ChildPrinter& printChar(const char c)
        {
            cout << c;
            return *this;
        }
    };
}

int main(int argc, char* argv[])
{
    {
        using namespace General;

        /* print("AAA") 는 Printer& 를 반환.
         ChildPrinter().print("AAA").printChar('B'); */
    }

    {
        using namespace CRTP;

        // print("AAA") 는 ChildPrinter& 를 반환.
        ChildPrinter().print("AAA").printChar('B');
    }

    return 0;
}
