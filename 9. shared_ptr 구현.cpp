#include <iostream>

using namespace std;

/*
 * shared_ptr 구현
 * 
 * 효율적이지 않고 Thread-safe 하지 않다.
 */

namespace mystd
{
    // 단순히 T 에 대한 레퍼런스 타입을 나타내는 변환
    template <typename T>
    struct my_shared_ptr_traits
    {
        using reference = T&;
    };
    // void 는 레퍼런스를 구할 수 없다.
    template <>
    struct my_shared_ptr_traits<void>
    {
        using reference = void;
    };

    template <typename T>
    class my_shared_ptr
    {
        T* p;
        /*
         * shared_ptr 은 실제로는 Reference count 뿐만 아니라,
         * Weak count 도 관리한다.
         */
        unsigned* pCounter;

    public:
        using reference = typename my_shared_ptr_traits<T>::reference;

        explicit my_shared_ptr(T* p = nullptr) : p(p), pCounter(nullptr)
        {
            if (p != nullptr)
                pCounter = new unsigned(1);
        }

        my_shared_ptr(const my_shared_ptr<T>& rhs): p(rhs.p), pCounter(rhs.pCounter)
        {
            if (p != nullptr)
                ++(*pCounter);
        }

        my_shared_ptr<T>& operator= (const my_shared_ptr<T>& rhs)
        {
            /*
             * copy-and-swap 관용구
             * 
             * rhs 데이터의 카운터 증가, 기존 *this 데이터의 카운터 감소
             * 모두 임시 객체의 복사 생성, 소멸을 통해 일어난다.
             */
            my_shared_ptr<T>(rhs).swap(*this);

            return *this;
        }

        unsigned use_count() const
        {
            return *pCounter;
        }

        reference operator* ()
        {
            return *p;
        }

        T* operator-> ()
        {
            return p;
        }

        /*
         * 정확히 bool 표현식을 원하는 곳에서만 호출
         * 
         * 가능 ==> bool
         * if (sh0)
         * 
         * 불가 ==> bool ==> int
         * if (sh1 < sh2)
         *
         * explicit 키워드가 없었을 때는
         * 멤버 함수에 대한 함수 포인터 형을 선언하고
         * 오버로드해 사용하는 편법을 썼다.
         *
         * 멤버 함수에 대한 포인터끼리는 등호 비교는 가능하지만,
         * 대소 비교는 불가능하기 때문.
         */
        explicit operator bool ()
        {
            return (p != nullptr);
        }

        void swap(my_shared_ptr<T>& rhs)
        {
            using std::swap;
            // swap() 은 내부적으로 이동 시맨틱을 사용한다.
            swap(p, rhs.p);
            swap(pCounter, rhs.pCounter);
        }

        void reset(T* p = nullptr)
        {
            // copy-and-swap 관용구
            my_shared_ptr<T>(p).swap(*this);
        }

        void release()
        {
            if (p == nullptr)
                return;

            if (--(*pCounter) == 0)
            {
                delete pCounter;
                delete p;
                pCounter = nullptr;
                p = nullptr;
            }
        }

        ~my_shared_ptr()
        {
            release();
        }
    };
};

int main(int argc, char* argv[])
{
    using namespace mystd;

    my_shared_ptr<int> sh0;
    sh0.reset(new int(2));

    my_shared_ptr<int> sh1, sh2;
    sh2 = sh1 = sh0;

    if (sh2)
        cout << sh0.use_count() << " " << *sh1 << endl;

    return 0;
}
