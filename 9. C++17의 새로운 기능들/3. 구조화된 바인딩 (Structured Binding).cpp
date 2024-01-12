#include <iostream>
#include <tuple>
#include <map>

using namespace std;

/*
 * 구조화된 바인딩 (Structured Binding)
 */

// tuple 을 이용한 기존 방식
tuple<int, string, double> GetData()
{
    // initializer_list
    return {100, "Hello World !!", 3.0};
}

struct Vector3
{
    int x;
    float y;
    double z;
};

int main(int argc, char* argv[])
{
    auto data = GetData();

    // 레퍼런스 참조
    int &num = get<0>(data);
    num = 200;

    cout << get<0>(data) << endl;

    int i;
    string s;
    double d;

    data = GetData();

    // 값 복사
    tie(i, s, d) = data;
    i = 200;

    cout << get<0>(data) << endl;

    /* Structured binding */
    auto [i2, s2, d2] = GetData();
    auto [x, y, z] = Vector3{1, 2.F, 3.0};

    map<int, string> mp {
        {1, "Hello"},
        {2, "World"},
        {3, "!!"}
    };

    for (auto [key, value] : mp)
        cout << key << ": " << value << endl;

    return 0;
}
