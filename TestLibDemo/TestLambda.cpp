#include <iostream>
using namespace std;
#include <functional>
#include <vector>
#include<algorithm>

template <typename T>
class Print
{
public:
    void operator()(T elem) const
    {
        cout << elem << ' ';
    }
};

class IntSequence
{
public:
    IntSequence(int initVal) : value{ initVal } {}

    int operator()() { return ++value; }
private:
    int value;
};

int main()
{
    auto basicLambda = [] { cout << "Hello, world!" << endl; };
    basicLambda();

    auto add1 = [](int a, int b)->int {return a + b; };
    auto multiply1 = [](int a, int b) {return a * b; };

    add1(1, 2);
    multiply1(2, 3);
    int x = 10;
    //����ģ�����x���հ�����ſ���ʹ������ֲ�����
   //add_x�Ը��Ƶ���ʽ��׽����x
    auto add_x = [x](int a) {return a + x; };
    //multiply_x�������õķ�ʽ��׽x
    auto multiply_x = [&x](int a) {return  a * x; };
    //��Ķ���ֵ��ʽ�����ֵ����ô��Ҫʹ��mutable
    auto add_x2 = [x](int a)mutable {x *= 2; return a + x; };

    int value = 3;
    vector<int> v1{ 1, 3, 5, 2, 6, 10 };
    int count = std::count_if(v1.begin(), v1.end(), [value](int x) { return x > value; });

    int init = 0;
    vector<int> v(10);
    std::generate(v.begin(), v.end(), [&init] { return init++; });
    // ʹ��for_each�������Ԫ�أ�����һ��Printʵ����
    std::for_each(v.begin(), v.end(), Print<int>{});
    // ����lambda���ʽ��std::for_each(v.begin(), v.end(), [](int x){ cout << x << ' ';});
    // �����0, 1, 2, 3, 4, 5, 6, 7, 8, 9

    std::generate(v.begin(), v.end(), IntSequence{ 0 });
    /*  lambdaʵ��ͬ��Ч��
        int init = 0;
        std::generate(v.begin(), v.end(), [&init] { return ++init; });
    */
    std::for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
    //�����1, 2, 3, 4, 5, 6, 7, 8, 9, 10


}
