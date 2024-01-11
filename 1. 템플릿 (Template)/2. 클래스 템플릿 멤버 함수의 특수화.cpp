#include <iostream>

using namespace std;

/*
 * 클래스 템플릿 멤버 함수의 특수화
 */

template <typename T>
class AAA
{
public:
    void Print()
    {
        cout << "AAA<T>" << endl;
    }
};

template <>
void AAA<double>::Print()
{
    cout << "AAA<double>" << endl;
}

int main(int argc, char* argv[])
{
    AAA<int> ai;
    AAA<double> ad;

    ai.Print();
    ad.Print();

    return 0;
}
