/*
 * https://m.blog.naver.com/oidoman/90145719426
 */
#include <iostream>

using namespace std;

/*
 * 정적 다형성을 이용한 복사본 생성
 */

class IDrawable
{
public:
    virtual IDrawable* clone() const = 0;

    virtual void draw() = 0;
    virtual ~IDrawable() {}
};

namespace General
{
    class Widget : public IDrawable
    {
        int* pData;

    public:
        // 구현체에서 clone() 함수를 직접 오버라이드 해줘야 한다.
        virtual IDrawable* clone() const override
        {
            return new Widget(*pData);
        }

        Widget(int data) : pData(new int(data)) {}
        virtual void draw() override {}
    };
}

namespace CRTP
{
    // 중간에 클래스를 하나 끼워 넣어
    template <typename DERIVED>
    class IDrawableT : public IDrawable
    {
    public:
        // 복사 생성자를 통해 복사본을 생성하도록 한다.
        virtual IDrawable* clone() const final
        {
            return new DERIVED(static_cast<const DERIVED&>(*this));
        }

        virtual void draw() override {}
    };

    class Widget : public IDrawableT<Widget>
    {
        int* pData;

    public:
        /* 구현체에서는 clone() 함수를 신경 쓰지 않고
         * 일반적인 복사 생성자만 작성해주면 된다. */
        Widget(const Widget& rhs) : pData(new int(*rhs.pData))
        {
        }

        Widget(int data) : pData(new int(data)) {}
        virtual void draw() override {}
    };
}

int main(int argc, char* argv[])
{
    {
        using namespace General;

        IDrawable* pd = new Widget(3);
        IDrawable* pd2 = pd->clone();
    }

    {
        using namespace CRTP;

        IDrawable* pd = new Widget(3);
        IDrawable* pd2 = pd->clone();
    }

    return 0;
}
