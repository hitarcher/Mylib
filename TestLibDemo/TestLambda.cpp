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
    //捕获模块里放x，闭包区域才可以使用这个局部变量
   //add_x以复制的形式捕捉变量x
    auto add_x = [x](int a) {return a + x; };
    //multiply_x是以引用的方式捕捉x
    auto multiply_x = [&x](int a) {return  a * x; };
    //想改动传值方式捕获的值，那么就要使用mutable
    auto add_x2 = [x](int a)mutable {x *= 2; return a + x; };

    int value = 3;
    vector<int> v1{ 1, 3, 5, 2, 6, 10 };
    int count = std::count_if(v1.begin(), v1.end(), [value](int x) { return x > value; });

    int init = 0;
    vector<int> v(10);
    std::generate(v.begin(), v.end(), [&init] { return init++; });
    // 使用for_each输出各个元素（送入一个Print实例）
    std::for_each(v.begin(), v.end(), Print<int>{});
    // 利用lambda表达式：std::for_each(v.begin(), v.end(), [](int x){ cout << x << ' ';});
    // 输出：0, 1, 2, 3, 4, 5, 6, 7, 8, 9

    std::generate(v.begin(), v.end(), IntSequence{ 0 });
    /*  lambda实现同样效果
        int init = 0;
        std::generate(v.begin(), v.end(), [&init] { return ++init; });
    */
    std::for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
    //输出：1, 2, 3, 4, 5, 6, 7, 8, 9, 10


}
